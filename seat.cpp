
// Created by Caroline Jubran on 2019-06-21.
//
#include "seat.h"

#define DIASABLE_PRICE 200
#define GREEN_ROOM_PRICE 1000
#define MAIN_HALL_SEAT_PRICE 100
#define SPEAICL_SEAT_PRICE  300
#define FRONT_SEAT_PRICE 500
#define MIDDLE_SEAT_PRICE 250

Seat::Seat(int line, int chair, int base_price) {
    this->line = line;
    this->chair = chair;
    this->base_price = base_price;
}

GreenRoomSeat::GreenRoomSeat(int line, int chair, int base_price)
        : Seat(line, chair, base_price) {}

MainHallSeat::MainHallSeat(int line, int chair, int basic_price)
        : Seat(line, chair, basic_price) {}

RegularSeat::RegularSeat(char area, int line, int chair, int basic_price)
        : MainHallSeat(line, chair, basic_price) {
    this->area = area;
}

FrontRegularSeat::FrontRegularSeat(char area, int line, int chair,
                                   int basic_price)
        : RegularSeat(area, line, chair, basic_price) {

}

MiddleRegularSeat::MiddleRegularSeat(char area, int line, int chair,
                                     int basic_price)
        : RegularSeat(area, line, chair, basic_price) {
}

RearRegularSeat::RearRegularSeat(char area, int line, int chair,
                                 int basic_price)
        : RegularSeat(area, line, chair, basic_price) {
}

SpecialSeat::SpecialSeat(int line, int chair, int base_price)
        : MainHallSeat(line, chair, base_price) {}

GoldenCircleSeat::GoldenCircleSeat(int line, int chair, int base_price)
        : SpecialSeat(line, chair, base_price) {}

DisablePodiumSeat::DisablePodiumSeat(int line, int chair, int base_price)
        : SpecialSeat(line, chair, base_price) {}


/////priiiiccccceeeeeeeeeee
int FrontRegularSeat::price() const {
    return base_price + MAIN_HALL_SEAT_PRICE + FRONT_SEAT_PRICE;
}

int MiddleRegularSeat::price() const {
    return base_price + MAIN_HALL_SEAT_PRICE + MIDDLE_SEAT_PRICE;
}

int RearRegularSeat::price() const {
    return base_price + MAIN_HALL_SEAT_PRICE;
}

int GreenRoomSeat::price() const {
    throw NoPrice();
}

int GoldenCircleSeat::price() const {
    return base_price + MAIN_HALL_SEAT_PRICE + SPEAICL_SEAT_PRICE +
           GREEN_ROOM_PRICE;
}

int DisablePodiumSeat::price() const {
    return DIASABLE_PRICE;
}


ostream &operator<<(ostream &os, Seat &seat) {
    seat.print(os);
    return os;
}

void GreenRoomSeat::print(ostream &os) {
    os << "Green Room" << "-> line: " << this->line << ", chair: "
       << this->chair;
}

void FrontRegularSeat::print(ostream &os) {
    os << "Front" << "-> area: " << this->area << ", line: " << this->line
       << ", chair: " << this->chair;
}

void MiddleRegularSeat::print(ostream &os) {
    os << "Middle" << "-> area: " << this->area << ", line: " << this->line
       << ", chair: " << this->chair;
}

void RearRegularSeat::print(ostream &os) {
    os << "Rear" << "-> area: " << this->area << ", line: " << this->line
       << ", chair: " << this->chair;
}

void GoldenCircleSeat::print(ostream &os) {
    os << "Golden Circle" << "-> line: " << this->line << ", chair: "
       << this->chair;
}

void DisablePodiumSeat::print(ostream &os) {
    os << "Disable Podium" << "-> line: " << this->line << ", chair: "
       << this->chair;
}

char const *NoPrice::what() const noexcept {
    return "Not For Sale !";
}
