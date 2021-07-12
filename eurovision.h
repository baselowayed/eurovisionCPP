#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>
#include <cstdbool>
#include <cstring>

using std::ostream;
using std::string;
// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;

//---------------------------------------------------

enum VoterType {
    All, Regular, Judge
};
enum Phase {
    Registration, Contest, Voting
};

//----------------------------c-----------------------

class Participant {
    const char *state_name;
    string song_name;
    int song_time_length;
    string singer_name;
    int registered;

public :
    /**
     * constructor of the Participant,builds(allocates) a new Participant with
     * the given params.
     * @param state_name : name of the state in this participant.
     * @param song_name : song name of the participant.
     * @param song_time_length : song length with seconds of the participant.
     * @param singer_name : name of the singer of the participant.
     */
    Participant(const char *state_name, string const &song_name,
                int song_time_length, string const &singer_name);

    /**
     * destructor of the participant deletes the allocations.
     */
    ~Participant();

    /**
     * @return the state of this participant.
     */
    const char *state();

    /**
     * @return the song name of this participant.
     */
    string song();

    /**
     * @return the song length in seconds of this participant.
     */
    int timeLength();

    /**
     * @return the singer name of this participant.
     */
    string singer();

    /**
     * @return if this participant is registered to the competition(eurovision).
     */
    int isRegistered();

    /**
        * @param song_name :a new song name of the participant to update ,
        * if it’s “” then we dont change the previous song name.
        * @param song_time_length :a new song length with seconds
        * of the participant to update,if its not 0 we dont change the
        * previous song time length.
        * @param singer_name : a new singer name of the participant to update ,
        * if it’s “” then we dont change the previous singer name.
        */
    void update(string const &song_name, int song_time_length,
                string const &singer_name);

    /**
     * updates the regiestered field with the given value(true or false).
     * @param registered : is a boolean param and it is the next regeistered
     * value.
     */
    void updateRegistered(bool registered);
};

/**
 * this operator is used to print a Participant.
 * @param os : is the file we want to print the Participant to.
 * @param participant : is the Participant we want to print.
 * @return the file with the Participant printed in it.
 */
ostream &operator<<(ostream &os, Participant &participant);


class Voter {
    const char *voter_state_name;
    VoterType type;
    int votes;

public :
    /**
     * constructor of the Voter, builds(allocates) a new Voter with
     * the given params.
     * @param voter_state_name : name of the state in this Voter.
     * @param type : type of the voter(Regular or Judge).
     */
    explicit Voter(const char *voter_state_name, VoterType type = Regular);

    /**
     * destructor of the Voter deletes all the allocations.
     */
    ~Voter();

    /**
     * this operator adds 1 to the votes (means the Voter voted one more)
     */
    void operator++();

    /**
     * @return the state of this Voter.
     */
    const char *state();

    /**
     * @return the VoterType of this Voter
     */
    VoterType voterType();

    /**
     * @return the value of the Votes field(the times that this Voter has
     * voted).
     */
    int timesOfVotes();

};


struct Vote {
public:
    Voter *voter;
    const char **states;

    /**
     * constructor of the Vote, builds(allocates) a new Vote with the
     * given elements.
     * the default of the names is nullptr.
     * @param voter : this is the Voter that wants to vote.
     * @param name1 : the name of the first state that recieves a vote.
     * @param name2 : the name of the second state that recieves a vote.
     * @param name3 : the name of the third state that recieves a vote.
     * @param name4 : the name of the fourth state that recieves a vote.
     * @param name5 : the name of the fifth state that recieves a vote.
     * @param name6 : the name of the 6th state that recieves a vote.
     * @param name7 : the name of the 7th state that recieves a vote.
     * @param name8 : the name of the 8th state that recieves a vote.
     * @param name9 : the name of the 9th state that recieves a vote.
     * @param name10 : the name of the 10 state that recieves a vote.
     */
    explicit Vote(Voter &voter, const char *name1 = nullptr,
                  const char *name2 = nullptr, const char *name3 = nullptr,
                  const char *name4 = nullptr, const char *name5 = nullptr,
                  const char *name6 = nullptr, const char *name7 = nullptr,
                  const char *name8 = nullptr, const char *name9 = nullptr,
                  const char *name10 = nullptr);

    /**
     * destructor of the Vote, deletes all the allocations.
     */
    ~Vote();
};

/**
 * this operator is used to print a Voter.
 * @param os : is the file we want to print the Voter to.
 * @param voter : is the Voter we want to print.
 * @return the file with the Participant printed in it.
 */
ostream &operator<<(ostream &os, Voter &voter);
// -----------------------------------------------------------


class MainControl {
    int max_song_time;
    int max_participants;
    int max_votes;
    Phase status;
    int counter;
    Participant **participants;
    int *RegularVotes;
    int *JudgeVotes;


public:

    /**
     * constructor of the MainControl, builds a new MainControl with the
     * given params.
     * @param max_song_time : is the max length of the songs allowed
     * to participate in the competetion.
     * @param max_participants : is the max number of participant
     * allowed in the competetion.
     * @param max_votes : is the max time that is allowed to a
     * regular Voter to vote.
     */
    explicit MainControl(int max_song_time = 180,
                         int max_participants = 26, int max_votes = 5);

    /**
     * destructor of the MainControl, deletes all the allocations.
     */
    ~MainControl();

    /**
     * first checks if the participant is legal then adds it to the competetion.
     * @param participant : the participant we want to add
     * @return the MainControl but updated(might be unchanged).
     */
    MainControl &operator+=(Participant &participant);

    /**
     * removes a participant from the MainControl.
     * @param participant : the participant we want to remove
     *
     * @return the Main Control but updated.
     */
    MainControl &operator-=(Participant &participant);

    /**
     * adds a Vote to right place in the MainControl.
     * @param vote : the Vote we want to add.
     * @return the MainControl but updated(might be unchanged).
     */
    MainControl &operator+=(Vote vote);

    /**
     * sets a new phase in the status field in the MainControl
     * @param new_status : is the new phase(part) of the competition.
     */
    void setPhase(Phase new_status);

    /**
     * checks if the state participating in this MainControl.
     * @param state_name : the name of the state of the participant
     * we want to check if it participates.
     * @return 1 : if this participant(with the given state name)
     * is participating.
     *         0 : if this participant(with the given state name)
     *         is not participating.
     */
    int participate(const char *state_name);

    /**
     *  checks if the participant is legal.
     * @param participant : the participant we want to check if it is legal.
     * @return : 1 if the participant is legal.
     *         : 0 if the participant is not legal.
     */
    int legalParticipant(Participant &participant);

    /**
     * this operator is used to print a MainControl.
     * @param os : is the file we want to print the MainControl to.
     * @param participant : is the MainControl we want to print.
     * @return the file with the MainControl printed in it.
     */
    friend ostream &operator<<(ostream &os, MainControl &eurovision);

/**
     * this function is used to add a regular vote for MainControl.
     * @param vote : is the vote we want to add to the MainControl.
     * @param mainControl : the main control that we want to add for a vote.
     */

    friend void regular_votes(Vote &vote, MainControl &mainControl);

/**
     * this function is used to add a judge vote for MainControl.
     * @param vote : is the vote we want to add to the MainControl.
     * @param mainControl : the main control that we want to add for a vote.
     */
    friend void judge_votes(Vote &vote, MainControl &mainControl);

    /**
     * this operator prints the winner state name according to the type votes
     * @param i : is the rank of the winner we are searching for
     * @param type : is the type of votes we are serching in.
     * @return the state name with this rank according to the type votes.
     */
    const char *operator()(int i, VoterType type);

    class Iterator {
        MainControl *m;
        int index;
    public:
        /**
         * constructor of the Iterator, builds a new Iterator.
         */
        Iterator() {}

        /**
         * constructor of the Iterator, builds a new Iterator with
         * the given param.
         * @param m : is the MainControl that is given.
         */
        explicit Iterator(MainControl *m) : m(m), index(0) {
        }

        /**
         * constructor of the Iterator, builds a new Iterator with
         * the given param.
         * @param m :  is the MainControl that is given.
         * @param index : is the value of the index we want to update.
         */
        Iterator(MainControl *m, int index) : m(m), index(index) {}

        /**
         * it allows us to get the participant in MainControl in
         * the place index.
         * @return the content of the participant in the place index.
         */
        Participant &operator*();

        /**
         * adds 1 to the index of the iterator and returns it
         * @return the iterator but with an added index
         */
        Iterator &operator++();

        /**
         * checks if the index of this equals the index of a.
         * @param a : is the given iterator.
         * @return true : if the condition above is true.
         *         false : if the condition above is false.
         */
        bool operator==(Iterator a);

        /**
         * updates this iterator to the given iterator.
         * @param a : is the give iterator.
         * @return this iterator but updated with the details of a.
         */
        Iterator &operator=(Iterator a);

        /**
         * checks if the index of this is less than the index of a.
         * @param a : is the iterator given.
         * @return true : if the condition above is true.
         *         false : if the condition above is false.
         */
        bool operator<(Iterator a);

    };

    /**
      * @returns Iteartor with the beginig of the first participant.
      */
    Iterator begin();

    /**
      * @returns Iteartor with the end of the last participant.
      */
    Iterator end();

    /**
     * we use this func as helper in operator () it finds the iterator
     * of the element in the "i" rank,
     * in the array that is given by a first and an end element in it.
     * @tparam Iterator : is the type of the array we are searching in.
     * @param i : is the rank we are searching for.
     * @param first : is the first element in the array.
     * @param end : is the element after the last element in the array.
     * @return  the iterator of the element with the rank "i".
     */
    template<typename Iterator>
    Iterator get(int i, Iterator first, Iterator end) {
        bool ex = false;
        Iterator *histogram = new Iterator[i];
        Iterator min = first;
        for (Iterator l = first; l < end; ++l) {
            if (*l < *min) min = l;
        }
        for (int j = 0; j < i; ++j) {
            histogram[j] = min;
        }
        Iterator max = min;
        for (int index = 0; index < i; index++) {
            for (Iterator l = first; l < end; ++l) {
                if ((*max) <= (*l)) {
                    for (int j = 0; j < i; ++j) {
                        if ((histogram[j])) {
                            if (l == (histogram[j])) ex = true;
                        }
                    }
                    if (!ex) max = l;
                    ex = false;
                }
            }
            histogram[index] = max;
            max = min;
        }
        Iterator topI = histogram[i - 1];
        delete[] histogram;
        return topI;
    }
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// Also it's allowed here to define friend.

};



// -----------------------------------------------------------

#endif
