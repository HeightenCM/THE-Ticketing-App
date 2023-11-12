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

//class listsOfStuff {
//
//};

struct Event {
	string getName() {
		return nameOfEvent;
	}
	bool setName(string nameOfEvent) {
		cout << "(max character limit set at 30, min set at 5) ";
		if (!(strlen(nameOfEvent.c_str())<5||strlen(nameOfEvent.c_str())>30)) {
			this->nameOfEvent = nameOfEvent;
			return true;
		}
		return false;
	}

	string getLocation() {
		return locationOfEvent;
	}
	bool setLocation(string locationOfEvent) {
		cout << "(max character limit set at 80, min at 5) ";
		if (!(strlen(locationOfEvent.c_str()) < 5 || strlen(locationOfEvent.c_str()) > 30)) {
			this->locationOfEvent = locationOfEvent;
			return true;
		}
		return false;
			
	}

	char* getDate() {
		return Utility::copyArray(this->dateOfEvent);
	}
	bool setDate(const char* dateOfEvent) {
		cout << "(date is of the type YYYY/MM/DD) ";
		if (strlen(dateOfEvent) == 10) {
			if (dateOfEvent[4] == '/' || dateOfEvent[7] == '/') {
				if (Utility::isNumeric(dateOfEvent[0])&&Utility::isNumeric(dateOfEvent[1])&&Utility::isNumeric(dateOfEvent[2])&&Utility::isNumeric(dateOfEvent[3])){
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
	
	char* getTime() {
		return Utility::copyArray(this->openingTime);
	}
	bool setTime(const char* openingTime) {
		cout << "(time is of the type HH:MM)";
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

	int getRows() {
		return noOfRows;
	}
	bool setRows(int noOfRows) {
		cout << "(max value set at 10000, min set at 10) ";
		if (!(noOfRows < 10 || noOfRows>10000)) {
			this->noOfRows = noOfRows;
			return true;
		}
		return false;
	}
	
	int getSeats() {
		return noOfSeats;
	}
	bool setSeats(int noOfSeats) {
		cout << "(max value set at 100, min set at 1) ";
		if (!(noOfRows < 1 || noOfRows>100)) {
			this->noOfSeats = noOfSeats;
			return true;
		}
		return false;
	}
	
	int getZones() {
		return noOfZones;
	}
	bool setZones(int noOfZones) {
		cout << "(max value set at 1, min set at 5) ";
		if (!(noOfRows < 1 || noOfRows>5)) {
			this->noOfZones = noOfZones;
			return true;
		}
		return false;
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