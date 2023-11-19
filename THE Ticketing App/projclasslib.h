#pragma once

#include <iostream>
#include <string>

using namespace std;

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

	char* getDate() const{
		return Utility::copyArray(this->dateOfEvent);
	}
	bool setDate(const char* dateOfEvent) {
		if (strlen(dateOfEvent) == 10) {
			if (dateOfEvent[4] == '/' || dateOfEvent[7] == '/') {
				if (Utility::isNumeric(dateOfEvent[0]) && Utility::isNumeric(dateOfEvent[1]) && Utility::isNumeric(dateOfEvent[2]) && Utility::isNumeric(dateOfEvent[3])) {
					if (Utility::isNumeric(dateOfEvent[5]) && Utility::isNumeric(dateOfEvent[6])) {
						if (Utility::isNumeric(dateOfEvent[8]) && Utility::isNumeric(dateOfEvent[9])) {
							size_t lengthOfString = strlen(dateOfEvent) + 1;
							this->dateOfEvent = new char[lengthOfString];
							strcpy_s(this->dateOfEvent, lengthOfString, dateOfEvent);
							return true;
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

	char* getTime() const{
		return Utility::copyArray(this->openingTime);
	}
	bool setTime(const char* openingTime) {
		if (strlen(openingTime) == 5) {
			if (openingTime[2] == ':') {
				if (Utility::isNumeric(openingTime[0]) && Utility::isNumeric(openingTime[1])) {
					if (Utility::isNumeric(openingTime[3]) && Utility::isNumeric(openingTime[4])) {
						size_t lengthOfString = strlen(openingTime) + 1;
						this->openingTime = new char[lengthOfString];
						strcpy_s(this->openingTime, lengthOfString, openingTime);
						return true;
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

	string* getZones() const{
		string* copy = new string[this->noOfZones];
		for (int i = 0; i < this->noOfZones; i++) {
			copy[i] = this->zones[i];
		}
		return copy;
	}
	bool setZones(string* zones, int noOfZones) {
		if (noOfZones > 5 || zones == nullptr)return false;
		this->noOfZones = noOfZones;
		delete[] this->zones;
		this->zones = new string[noOfZones];
		for (int i = 0; i < noOfZones; i++) {
			this->zones[i] = zones[i];
		}
		return true;
	}

	int* getSeatsPerZone() const{
		int* copy = new int[this->noOfZones];
		for (int i = 0; i < this->noOfZones; i++) {
			copy[i] = this->seatsPerZone[i];
		}
		return copy;
	}
	bool setSeatsPerZone(int* seatsPerZone, int noOfZones) {
		if (noOfZones != this->noOfZones)return false;
		delete[] this->seatsPerZone;
		this->seatsPerZone = new int[this->noOfZones];
		for (int i = 0; i < this->noOfZones; i++) {
			this->seatsPerZone[i] = seatsPerZone[i];
		}
		return true;
	}

private:
	string* zones{};
	string nameOfEvent{}, locationOfEvent{};
	char* dateOfEvent{};
	char* openingTime{};
	int MAX_NO_OF_SEATS{}, noOfZones{};
	int* seatsPerZone{};
	const int eventID;
};

struct Ticket {

private:
	const int eventID;
	const int ticketID;
	int seatNo{};
};

class Manager {
	Event* eventList{};
	Ticket* ticketList{};
	int noOfEvents{};

public:
	string* getEvents() {
		if (noOfEvents == 0)return nullptr;
		string* listOfEvents = new string[noOfEvents];
		for (int i = 0; i < noOfEvents; i++) {
			listOfEvents[i] = this->eventList[i].getName();
		}
	}
};
