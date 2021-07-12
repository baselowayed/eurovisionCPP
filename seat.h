#ifndef SEAT_H_
#define SEAT_H_

#include <iostream>
#include <string>

using std::string;
using std::exception;
using std::ostream;

// ---------------------------------------------
class NoPrice : public exception {
    char const *what() const noexcept override;

};

// ---------------------------------------------
class Seat {
protected:
    int base_price;
    int line;
    int chair;

public:
    /**
     * constructor of the Seat,builds(allocates) a new Seat with
     * the given params.
     * @param line is the line of the seat.
     * @param chair is the chair of the seat.
     * @param base_price is the base price of the seat.
     */
    Seat(int line, int chair, int base_price);

    /**
     * destructor of Seat deletes all the allocations.
     */
    virtual ~Seat() = default;

    /**
     * @return the seat itself.
     */
    virtual Seat &location() {
        return *this;
    }

    /**
     * @return the seat price.
     */
    virtual int price() const = 0;

    /**
     * this operator is used to print a Seat.
     * @param os : is the file we want to print the Seat to.
     * @param seat : is the Seat we want to print.
     * @return the file with the Seat printed in it.
     */
    friend ostream &operator<<(ostream &os, Seat &seat);

    /**
     * prints the seat.
     * @param os:  is the file we want to print the Seat to.
     */
    virtual void print(ostream &os) {
    }
};

// ---------------------------------------------
class GreenRoomSeat : public Seat {
public:
    /**
    * constructor of the GreenRoomSeat,builds(allocates) a new Seat
     * with the given params.
    * @param line line is the line of the GreenRoomseat.
    * @param chair chair is the chair of the GreenRoomseat.
    * @param base_price base_price is the base price of the GreenRoomseat.
    */
    GreenRoomSeat(int line, int chair, int base_price = 0);

    /**
     * destructor of GreenRoomSeat deletes all the allocations.
     */
    ~GreenRoomSeat() = default;

    /**
     * @return the GreenRoomSeat price.
     */
    int price() const override;

    /**
     * prints the GreenRoomSeat.
     * @param os  :  is the file we want to print the Seat to.
     */
    void print(ostream &os) override;

};

// ---------------------------------------------
class MainHallSeat : public Seat {
public:
    /**
     * constructor of the MainHallSeat,builds(allocates) a new Seat
     * ith the given params.
     * @param line line line is the line of the MainHallSeat.
     * @param chair chair is the chair of the MainHallSeat.
     * @param basic_price base_price is the base price of the MainHallSeat.
     */
    MainHallSeat(int line, int chair, int basic_price);

    /**
     * destructor of MainHallSeat deletes all the allocations.
     */
    ~MainHallSeat() = default;
};

// ---------------------------------------------
class SpecialSeat : public MainHallSeat {
public:
    /**
     * constructor of the SpecialSeat,builds(allocates) a new Seat with
     * the given params.
     * @param line line line line is the line of the SpecialSeat.
     * @param chair chair chair is the chair of the SpecialSeat.
     * @param base_price base_price is the base price of the SpecialSeat.
     */
    SpecialSeat(int line, int chair, int base_price);

    /**
     * destructor of SpecialSeat deletes all the allocations.
     */
    ~SpecialSeat() = default;

};

// ---------------------------------------------
class GoldenCircleSeat : public SpecialSeat {
public:
    /**
     * constructor of the GoldenCircleSeat,builds(allocates) a new Seat
     * with the given params.
     * @param line line line line is the line of the GoldenCircleSeat.
     * @param chair chair chair is the chair of the GoldenCircleSeat.
     * @param base_price base_price is the base price of the GoldenCircleSeat.
     */
    GoldenCircleSeat(int line, int chair, int base_price);

    /**
     * destructor of GoldenCircleSeat deletes all the allocations.
     */
    ~GoldenCircleSeat() = default;

    /**
     * @return the GoldenCircleSeat price.
     */
    int price() const override;

    /**
     * prints the GoldenCircleSeat.
     * @param os  :  is the file we want to print the Seat to.
     */
    void print(ostream &os) override;
};

// ---------------------------------------------
class DisablePodiumSeat : public SpecialSeat {
public:
    /**
     * constructor of the DisablePodiumSeat,builds(allocates) a new Seat
     * with the given params.
     * @param line line line line is the line of the DisablePodiumSeat.
     * @param chair chair chair is the chair of the DisablePodiumSeat.
     * @param base_price base_price is the base price of the DisablePodiumSeat.
     */
    DisablePodiumSeat(int line, int chair, int base_price = 0);

    /**
     * destructor of DisablePodiumSeat deletes all the allocations.
     */
    ~DisablePodiumSeat() = default;

    /**
     * @return the DisablePodiumSeat price.
     */
    int price() const override;

    /**
     * prints the DisablePodiumSeat.
     * @param os  :  is the file we want to print the Seat to.
     */
    void print(ostream &os) override;
};

// ---------------------------------------------
class RegularSeat : public MainHallSeat {
protected:
    char area;
public:
    /**
     * constructor of the RegularSeat,builds(allocates) a new Seat with
     * the given params.
     * @param line line line line is the line of the RegularSeat.
     * @param chair chair chair is the chair of the RegularSeat.
     * @param base_price base_price is the base price of the RegularSeat.
     */
    RegularSeat(char area, int line, int chair, int basic_price);

    /**
     * destructor of RegularSeat deletes all the allocations.
     */
    ~RegularSeat() = default;

};

// ---------------------------------------------
class FrontRegularSeat : public RegularSeat {
public:
    /**
     * constructor of the FrontRegularSeat,builds(allocates) a new Seat
     * with the given params.
     * @param line line line line is the line of the FrontRegularSeat.
     * @param chair chair chair is the chair of the FrontRegularSeat.
     * @param base_price base_price is the base price of the FrontRegularSeat.
     */
    FrontRegularSeat(char area, int line, int chair, int basic_price);

    /**
     * destructor of FrontRegularSeat deletes all the allocations.
     */
    ~FrontRegularSeat() = default;

    /**
     * @return the FrontRegularSeat price.
     */
    int price() const override;

    /**
     * prints the FrontRegularSeat.
     * @param os  :  is the file we want to print the Seat to.
     */
    void print(ostream &os) override;
};

// ---------------------------------------------
class MiddleRegularSeat : public RegularSeat {
public:
    /**
     * constructor of the MiddleRegularSeat,builds(allocates) a new Seat
     * with the given params.
     * @param line line line line is the line of the MiddleRegularSeat.
     * @param chair chair chair is the chair of the MiddleRegularSeat.
     * @param base_price base_price is the base price of the MiddleRegularSeat.
     */
    MiddleRegularSeat(char area, int line, int chair, int basic_price);

    /**
     * destructor of MiddleRegularSeat deletes all the allocations.
     */
    ~MiddleRegularSeat() = default;

    /**
     * @return the MiddleRegularSeat price.
     */
    int price() const override;

    /**
     * prints the MiddleRegularSeat.
     * @param os  :  is the file we want to print the Seat to.
     */
    void print(ostream &os) override;

};

// ---------------------------------------------
class RearRegularSeat : public RegularSeat {
public:
    /**
     * constructor of the RearRegularSeat,builds(allocates) a new Seat
     * with the given params.
     * @param line line line line is the line of the RearRegularSeat.
     * @param chair chair chair is the chair of the RearRegularSeat.
     * @param base_price base_price is the base price of the RearRegularSeat.
     */
    RearRegularSeat(char area, int line, int chair, int basic_price);

    /**
     * destructor of RearRegularSeat deletes all the allocations.
     */
    ~RearRegularSeat() = default;

    /**
     * @return the RearRegularSeat price.
     */
    int price() const override;

    /**
     * prints the RearRegularSeat.
     * @param os  :  is the file we want to print the Seat to.
     */
    void print(ostream &os) override;

};

// ---------------------------------------------
#endif
