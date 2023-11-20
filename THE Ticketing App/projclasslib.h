#pragma once

#include <iostream>
#include <string>

using namespace std;

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
		if (!(strlen(nameOfEvent.c_str()) < 5 || strlen(nameOfEvent.c_str()) > 30)) {
			this->nameOfEvent = nameOfEvent;
			return true;
		}
		return false;
	}

	string getLocation() const{
		return locationOfEvent;
	}
	bool setLocation(string locationOfEvent) {
		if (!(strlen(locationOfEvent.c_str()) < 5 || strlen(locationOfEvent.c_str()) > 30)) {
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

private:
	string nameOfEvent{}, locationOfEvent{}, dateOfEvent{}, openingTime{};
	int MAX_NO_OF_SEATS{}, noOfZones{};
	const int eventID;
	Zone* zone{};
};

struct Zone {

private:
	string nameOfZone{};
	int noOfRows{};
	Row* row{};
	Zone* nextZone{};
};

struct Row {

private:
	char rowLetter{};
	int noOfSeats{};
	Seat* seat{};
	Row* nextRow{};
};

struct Seat {

private:
	bool isAccesible{}, isTaken{};
	Seat* nextSeat{};
};

struct Ticket {

private:
	const int eventID;
	const int ticketID;
	int seatNo{};
};