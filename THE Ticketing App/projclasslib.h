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
};

//class listsOfStuff {
//
//};

struct Event {
	string getName() {
		return nameOfEvent;
	}
	bool setName(string nameOfEvent) {
		this->nameOfEvent = nameOfEvent;
	}

	string getLocation() {
		return locationOfEvent;
	}
	bool setLocation(string locationOfEvent) {
		this->locationOfEvent = locationOfEvent;
	}

	char* getDate() {
		return Utility::copyArray(this->dateOfEvent);
	}
	bool setDate(const char* dateOfEvent) {
		size_t lengthOfString = strlen(dateOfEvent) + 1;
		this->dateOfEvent = new char[lengthOfString];
		strcpy_s(this->dateOfEvent, lengthOfString, dateOfEvent);
	}
	
	char* getTime() {
		return Utility::copyArray(this->openingTime);
	}
	bool setTime(const char* openingTime) {
		size_t lengthOfString = strlen(openingTime) + 1;
		this->openingTime = new char[lengthOfString];
		strcpy_s(this->openingTime, lengthOfString, openingTime);
	}

	int getRows() {
		return noOfRows;
	}
	bool setRows(int noOfRows) {
		this->noOfRows = noOfRows;
	}
	
	int getSeats() {
		return noOfSeats;
	}
	bool setSeats(int noOfSeats) {
		this->noOfSeats = noOfSeats;
	}
	
	int getZones() {
		return noOfZones;
	}
	bool setZones(int noOfZones) {
		this->noOfZones = noOfZones;
	}

private:
	string nameOfEvent{}, locationOfEvent{};
	char* dateOfEvent{};
	char* openingTime{};
	int noOfRows{}, noOfSeats{}, noOfZones{};
};

//struct Ticket {
//	
//};