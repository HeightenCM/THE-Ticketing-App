#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Ticket;
struct Seat;
struct Row;
struct Zone;
struct Event;

struct Utility {
	static char* copyArray(const char* sourceArray) {
		size_t sizeOfSourceArray = strlen(sourceArray) + 1;
		char* copy = new char[sizeOfSourceArray];
		strcpy_s(copy, sizeOfSourceArray, sourceArray);
		return copy;
	}
	static bool isNumeric(const char source) {
		if (!(source < '0' || source>'9'))return true;
		else return false;
	}
};

struct Event {
	string getName() const{
		return nameOfEvent;
	}
	bool setName(string nameOfEvent) {
		if (!(nameOfEvent.size() < 5 || nameOfEvent.size() > 30)) {
			this->nameOfEvent = nameOfEvent;
			return true;
		}
		return false;
	}

	string getLocation() const{
		return locationOfEvent;
	}
	bool setLocation(string locationOfEvent) {
		if (!(locationOfEvent.size()<5 || locationOfEvent.size() > 30)) {
			this->locationOfEvent = locationOfEvent;
			return true;
		}
		return false;

	}

	string getDate() const{
		return this->dateOfEvent;
	}
	bool setDate(string dateOfEvent) {
		if (dateOfEvent.size() == 10) {
			if (dateOfEvent[4] == '/' || dateOfEvent[7] == '/') {
				if (Utility::isNumeric(dateOfEvent[0]) && Utility::isNumeric(dateOfEvent[1]) && Utility::isNumeric(dateOfEvent[2]) && Utility::isNumeric(dateOfEvent[3])) {
					if (Utility::isNumeric(dateOfEvent[5]) && Utility::isNumeric(dateOfEvent[6])) {
						if (Utility::isNumeric(dateOfEvent[8]) && Utility::isNumeric(dateOfEvent[9])) {
							this->dateOfEvent = dateOfEvent;
						}
						else cout << "\nInvalid format! Day specifier is wrong!\n";
					}
					else cout << "\nInvalid format! Month specifier is wrong!\n";
				}
				else cout << "\nInvalid format! Year specifier is wrong!\n";
			}
			else cout << "\nInvalid format! You forgot the slashes!";
		}
		else cout << "\nInvalid or misspelled date format! Size doesn't match format type!\n";
		return false;
	}

	string getTime() const{
		return this->openingTime;
	}
	bool setTime(string openingTime) {
		if (openingTime.length() == 5) {
			if (openingTime[2] == ':') {
				if (Utility::isNumeric(openingTime[0]) && Utility::isNumeric(openingTime[1])) {
					if (Utility::isNumeric(openingTime[3]) && Utility::isNumeric(openingTime[4])) {
						this->openingTime = openingTime;
					}
					else cout << "\nInvalid format! Minute specifier isn't numeric!\n";
				}
				else cout << "\nInvalid format! Hour specifier isn't numeric!\n";
			}
			else cout << "\nInvalid time format! Missing the : !\n";
		}
		else cout << "\nInvalid time format! Size doesn't match format type!\n";
		return false;
	}
	
	int getMaxSeats() const{
		return this->MAX_NO_OF_SEATS;
	}
	bool setMaxSeats(int MaxSeats) {
		if (MaxSeats < this->MAX_NO_OF_SEATS) return false;
		this->MAX_NO_OF_SEATS = MaxSeats;
		return true;
	}

	int getNoOfZones() const{
		return this->noOfZones;
	}

private:
	string nameOfEvent{}, locationOfEvent{}, dateOfEvent{}, openingTime{};
	int MAX_NO_OF_SEATS{}, noOfZones{};
	const int eventID;
	Zone* zone{};
};

struct Zone {
	string getNameOfZone() const{
		return this->nameOfZone;
	}
	bool setNameOfZone(string nameOfZone) {
		if (nameOfZone.size() < 3)return false;
		this->nameOfZone = nameOfZone;
		return true;
	}

	int getNoOfRows() const{
		return this->noOfRows;
	}
	bool setNoOfRows(int noOfRows) {
		if (noOfRows < 1 || noOfRows > 50)return false;
		this->noOfRows = noOfRows;
	}

	void addNewZone(Zone* newZone) {
		newZone->nextZone = this->nextZone;
		this->nextZone = newZone;
	}

private:
	string nameOfZone{};
	int noOfRows{};
	Row* row{};
	Zone* nextZone{};
};

struct Row {
	char getRowLetter() const{
		return this->rowLetter;
	}
	bool setRowLetter(char rowLetter) {
		if (rowLetter < 'A' || rowLetter>'Z')return false;
		this->rowLetter = rowLetter;
		return true;
	}

	int getNoOfSeats() const{
		return this->noOfSeats;
	}
	bool setNoOfRows(int noOfSeats) {
		if (noOfSeats < 1 || noOfSeats > 50)return false;
		this->noOfSeats = noOfSeats;
	}

	void addNewRow(Row* newRow) {
		newRow->nextRow = this->nextRow;
		this->nextRow = newRow;
	}

private:
	char rowLetter{};
	int noOfSeats{};
	Seat* seat{};
	Row* nextRow{};
};

struct Seat {
	bool getAccesibility() const{
		return this->isAccesible;
	}
	bool setAccesibility() {
		this->isAccesible = true;
	}
	
	bool isSeatTaken() const{
		return this->isTaken;
	}
	bool sellSeat() {
		this->isTaken = true;
	}

	void addNewSeat(Seat* newSeat) {
		newSeat->nextSeat = this->nextSeat;
		this->nextSeat = newSeat;
	}

private:
	bool isAccesible{}, isTaken{};
	Ticket* ticket{};
	Seat* nextSeat{};
};

struct Ticket {

private:
	const int ticketID;
};