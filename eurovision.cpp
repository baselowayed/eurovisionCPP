//
// Created by Caroline Jubran on 2019-06-04.
//
#include "eurovision.h"

#define TEN 10
using std::string;
/**
     * we use this func as helper to get the score for every state that
     * the judge votes to.
     * @param i : is the index in the array of states of the judge.
     * @return  the score for this i.
     */
static int convert(int i);

ostream &operator<<(ostream &os, Participant &participant) {
    os << "[" << participant.state() << "/" << participant
            .song() << "/" << participant.timeLength() << "/"
       << participant.singer() << "]";
    return os;
}

ostream &operator<<(ostream &os, Voter &voter) {
    os << "<" << voter.state() << "/";
    if (voter.voterType() == Regular)
        os << "Regular>";
    else os << "Judge>";
    return os;
}

ostream &operator<<(ostream &os, MainControl &eurovision) {
    if (eurovision.status == Registration) {
        os << "{\nRegistration\n";
        for (int i = 0; i < eurovision.counter; i++) {
            os << "[" << eurovision.participants[i]->state() << "/" <<
               eurovision.participants[i]->song() << "/"
               << eurovision.participants[i]->timeLength()
               << "/" << eurovision.participants[i]->singer() << "]\n";
        }
        os << "}\n";
    }
    if (eurovision.status == Contest) {
        os << "{\nContest\n}\n";
    }
    if (eurovision.status == Voting) {
        os << "{\nVoting\n";
        for (int i = 0; i < eurovision.counter; i++) {
            os << eurovision.participants[i]->state() << " : "
               << "Regular(" << eurovision.RegularVotes[i] << ") Judge("
               << eurovision.JudgeVotes[i] << ")\n";
        }
        os << "}\n";
    }
    return os;
}

Participant::Participant(const char *state_name,
                         string const &song_name, int song_time_length,
                         string const &singer_name)
        : song_name(song_name), singer_name(singer_name) {
    this->state_name = strcpy(new char[strlen(state_name) + 1], state_name);
    this->song_time_length = song_time_length;
    this->registered = 0;
}


Participant::~Participant() {

    delete[] state_name;

}


const char *Participant::state() {
    return this->state_name;
}


string Participant::song() {
    return this->song_name;
}


int Participant::timeLength() {
    return this->song_time_length;
}


string Participant::singer() {
    return this->singer_name;
}


int Participant::isRegistered() {
    return registered;
}


void Participant::update(string const &song_name, int song_time_length,
                         string const &singer_name) {
    if (this->registered == 1)
        return;
    if (song_name.length() != 0)
        this->song_name = song_name;
    if (singer_name.length() != 0)
        this->singer_name = singer_name;
    if (song_time_length != 0)
        this->song_time_length = song_time_length;
}


void Participant::updateRegistered(bool registered) {
    if (registered)
        this->registered = 1;
    else this->registered = 0;
}


Voter::Voter(const char *voter_state_name, VoterType type) {
    if (type != Regular && type != Judge)
        type = Regular;
    this->voter_state_name = strcpy(new char[strlen(voter_state_name) + 1],
                                    voter_state_name);
    this->votes = 0;
    this->type = type;
}


Voter::~Voter() {
    delete[] voter_state_name;
}

VoterType Voter::voterType() {
    return this->type;
}

const char *Voter::state() {
    return this->voter_state_name;
}


int Voter::timesOfVotes() {
    return votes;
}

void Voter::operator++() {
    int i = votes;
    i++;
    votes = i;


}

Vote::Vote(Voter &voter, const char *name1, const char *name2,
           const char *name3,
           const char *name4, const char *name5, const char *name6,
           const char *name7, const char *name8, const char *name9,
           const char *name10) : voter(&voter) {
    states = new const char *[TEN];
    for (int i = 0; i < TEN; i++)
        states[i] = nullptr;
    if (name1 != nullptr)
        states[0] = strcpy(new char[strlen(name1) + 1], name1);
    if (name2 != nullptr)
        states[1] = strcpy(new char[strlen(name2) + 1], name2);
    if (name3 != nullptr)
        states[2] = strcpy(new char[strlen(name3) + 1], name3);
    if (name4 != nullptr)
        states[3] = strcpy(new char[strlen(name4) + 1], name4);
    if (name5 != nullptr)
        states[4] = strcpy(new char[strlen(name5) + 1], name5);
    if (name6 != nullptr)
        states[5] = strcpy(new char[strlen(name6) + 1], name6);
    if (name7 != nullptr)
        states[6] = strcpy(new char[strlen(name7) + 1], name7);
    if (name8 != nullptr)
        states[7] = strcpy(new char[strlen(name8) + 1], name8);
    if (name9 != nullptr)
        states[8] = strcpy(new char[strlen(name9) + 1], name9);
    if (name10 != nullptr)
        states[9] = strcpy(new char[strlen(name10) + 1], name10);
}


Vote::~Vote() {
    for (int i = 0; i < TEN; ++i) {
        if (states[i] != nullptr)
            delete[] states[i];
    }
    delete[] states;
}


MainControl::MainControl(int max_song_time, int max_participants,
                         int max_votes) {
    this->participants = new Participant *[max_participants];
    for (int i = 0; i < max_participants; i++) {
        participants[i] = nullptr;
    }
    this->RegularVotes = new int[max_participants];
    this->JudgeVotes = new int[max_participants];
    for (int i = 0; i < max_participants; ++i) {
        RegularVotes[i] = 0;
        JudgeVotes[i] = 0;
    }
    this->max_song_time = max_song_time;
    this->max_participants = max_participants;
    this->max_votes = max_votes;
    this->status = Registration;
    this->counter = 0;
}

MainControl::~MainControl() {
    for(int i=0;i<counter;i++){
        participants[i]->updateRegistered(false);
    }
    delete[] participants;
    delete[] RegularVotes;
    delete[] JudgeVotes;
}


void swapParticipants(Participant **participant1, Participant **participant2) {
    Participant *tmp = *participant1;
    *participant1 = *participant2;
    *participant2 = tmp;

}

void sortingParticipants(Participant **participants, int counter) {
    for (int i = 0; i < counter; i++) {
        for (int j = 0; j < counter - i; j++) {
            if (participants[j]->state() && participants[j + 1]->state()) {
                if (strcmp(participants[j]->state(),
                           participants[j + 1]->state()) > 0) {
                    swapParticipants(&participants[j], &participants[j + 1]);
                }
            }
        }
    }
}

MainControl &MainControl::operator+=(Participant &participant) {
    if (participant.isRegistered() == 1)
        return *this;
    int j = 0;
    if ((this->status == Registration) && (this->legalParticipant(participant))
        && (counter != this->max_participants)) {
        while (j < counter) {
            if (participants[j]->state() && participant.state()) {
                if (strcmp(participant.state(), participants[j]->state()) == 0)
                    return *this;
                j++;
            }
        }
        participant.updateRegistered(true);
        participants[counter] = &participant;
        sortingParticipants(participants, counter);
        counter++;

    }
    return *this;
}


void MainControl::setPhase(Phase new_status) {
    if (this->status == Registration && new_status == Contest)
        this->status = new_status;
    if (this->status == Contest && new_status == Voting)
        this->status = new_status;
}


int MainControl::participate(const char *state_name) {
    int j = 0;
    while (j < counter) {
        if (state_name != nullptr) {
            if (participants[j]->state() != nullptr) {
                if (strcmp(state_name, participants[j]->state()) == 0)
                    return 1;
                j++;
            }
        }
    }
    return 0;
}


MainControl &MainControl::operator-=(Participant &participant) {
    if (!participant.isRegistered())
        return *this;
    if (this->status == Registration) {
        for (int k = 0; k < counter; ++k) {
            if (participant.state() && participants[k]->state()) {
                if (strcmp(participant.state(), participants[k]->state()) ==
                    0) {
                    for (int i = k; i < counter - 1; ++i) {
                        participants[i] = participants[i + 1];
                    }
                    participants[counter - 1] = nullptr;
                    break;
                }
            }
        }
        counter--;
        participant.updateRegistered(false);
        sortingParticipants(participants, counter - 1);
    }
    return *this;
}

 int convert(int i) {
    if (i == 0)
        return 12;
    if (i == 1)
        return 10;
    for(int l=2;l<TEN;l++) {
        if (i == l){
            return TEN-l;
        }
    }
    return 0;
}


int MainControl::legalParticipant(Participant &participant) {
    if (participant.timeLength() > this->max_song_time)
        return 0;
    if (strcmp(participant.state(), "") == 0 ||
        (participant.singer().length() == 0) ||
        (participant.song().length()) == 0)
        return 0;
    return 1;
}

void regular_votes(Vote &vote, MainControl &mainControl) {
    if (vote.voter->state() && vote.states[0]) {
        if (strcmp(vote.voter->state(), vote.states[0]) != 0) {
            for (int i = 0; i < mainControl.counter; ++i) {
                if (mainControl.participants[i]->state() != nullptr) {
                    if (strcmp(mainControl.participants[i]->state(),
                               vote.states[0]) == 0) {
                        mainControl.RegularVotes[i]++;
                        ++*(vote.voter);
                        break;
                    }
                }
            }
        }
    }

}

void judge_votes(Vote &vote, MainControl &mainControl) {
    bool voted = false;
    if (vote.voter->state()) {
        for (int i = 0; i < TEN; i++) {
            if (vote.states[i] != nullptr) {
                if (strcmp(vote.voter->state(), vote.states[i]) != 0) {
                    for (int j = 0; j < mainControl.counter; ++j) {
                        if (vote.states[i] != nullptr) {
                            if (mainControl.participants[j]->state()) {
                                if (strcmp(mainControl.participants[j]->state(),
                                           vote.states[i]) == 0) {
                                    mainControl.JudgeVotes[j] += convert(i);
                                    voted = true;
                                }
                            }
                        }
                    }

                }
            }
        }
        if (voted)++*(vote.voter);
    }
}


MainControl &MainControl::operator+=(Vote vote) {
    bool is_regisitered = false;
    if (status != Voting) return *this;
    if ((vote.voter)->voterType() == Regular &&
        vote.voter->timesOfVotes() < max_votes) {
        for (int j = 0; j < counter; ++j) {
            if (participants[j]->state() && vote.voter->state()) {
                if (strcmp(participants[j]->state(), vote.voter->state()) == 0)
                    is_regisitered = true;
            }
        }
        if (is_regisitered) regular_votes(vote, *this);
    }
    if (vote.voter->voterType() == Judge && vote.voter->timesOfVotes() == 0) {
        for (int j = 0; j < counter; ++j) {
            if (participants[j]->state() && vote.voter->state()) {
                if (strcmp(participants[j]->state(), vote.voter->state()) == 0)
                    is_regisitered = true;
            }
        }
        if (is_regisitered) judge_votes(vote, *this);
    }
    return *this;
}


const char *MainControl::operator()(int i, VoterType type) {
    int index = -1;
    if (i > counter)return "";
    if (type == Regular) {
        int *j = get<int *>(i, &RegularVotes[0], &RegularVotes[counter]);
        for (int k = 0; k < counter; k++) {
            if (&RegularVotes[k] == j)
                index = k;
        }
    }
    if (type == Judge) {
        int *j = get<int *>(i, &JudgeVotes[0], &JudgeVotes[counter]);
        for (int k = 0; k < counter; ++k) {
            if (&JudgeVotes[k] == j)
                index = k;
        }
    }
    if (type == All) {
        int *Votes = new int[counter];
        for (int k = 0; k < counter; ++k) {
            Votes[k] = RegularVotes[k] + JudgeVotes[k];
        }
        int *j = get<int *>(i, &Votes[0], &Votes[counter]);
        for (int k = 0; k < counter; ++k) {
            if (&Votes[k] == j)
                index = k;
        }
        delete[] Votes;
    }
    return participants[index]->state();
}

bool MainControl::Iterator::operator<(Iterator a) {
    return (this->index < a.index);

}

bool MainControl::Iterator::operator==(Iterator a) {
    return (this->index == a.index);

}

MainControl::Iterator &MainControl::Iterator::operator=(Iterator a) {
    this->index = a.index;
    this->m = a.m;
    return *this;
}

MainControl::Iterator &MainControl::Iterator::operator++() {
    Iterator *temp = this;
    index++;
    return *temp;
}

Participant &MainControl::Iterator::operator*() {
    return *(m->participants[index]);
}

MainControl::Iterator MainControl::begin() {
    return Iterator(this);
}


MainControl::Iterator MainControl::end() {

    return Iterator(this, counter);
}
