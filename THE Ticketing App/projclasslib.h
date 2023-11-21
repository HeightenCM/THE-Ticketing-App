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
		if (source < '0' || source>'9')return false;
		return true;
	}
};

struct Event {
	string getName() const {
		return this->nameOfEvent;
	}
	string setName(string nameOfEvent) {
		if (nameOfEvent.size() < MIN_NAME_SIZE || nameOfEvent.size() > MAX_NAME_SIZE)throw exception("");
		return nameOfEvent;
	}

	string getLocation() const {
		return this->locationOfEvent;
	}
	void setLocation(string locationOfEvent) {
		if (locationOfEvent.size() < MIN_NAME_SIZE || locationOfEvent.size() > MAX_NAME_SIZE) throw exception("");
		this->locationOfEvent = locationOfEvent;
	}

	string getDate() const {
		return this->dateOfEvent;
	}
	void setDate(string dateOfEvent) {
		if (dateOfEvent.size() == 10) {
			if (dateOfEvent[4] == '/' || dateOfEvent[7] == '/') {
				if (Utility::isNumeric(dateOfEvent[0]) && Utility::isNumeric(dateOfEvent[1]) && Utility::isNumeric(dateOfEvent[2]) && Utility::isNumeric(dateOfEvent[3])) {
					if (Utility::isNumeric(dateOfEvent[5]) && Utility::isNumeric(dateOfEvent[6])) {
						if (Utility::isNumeric(dateOfEvent[8]) && Utility::isNumeric(dateOfEvent[9])) {
							this->dateOfEvent = dateOfEvent;
						}
					}
				}
			}
		}
		throw exception("");
	}

	string getTime() const {
		return this->openingTime;
	}
	void setTime(string openingTime) {
		if (openingTime.length() == 5) {
			if (openingTime[2] == ':') {
				if (Utility::isNumeric(openingTime[0]) && Utility::isNumeric(openingTime[1])) {
					if (Utility::isNumeric(openingTime[3]) && Utility::isNumeric(openingTime[4])) {
						this->openingTime = openingTime;
					}
				}
			}
		}
		throw exception("");
	}

	int getNoOfZones() const {
		return this->noOfZones;
	}
	void setNoOfZones(int noOfZones) {
		if (noOfZones<MIN_ZONE_NO || noOfZones>MAX_ZONE_NO)throw exception("");
	}

	Event(string nameOfEvent, string locationOfEvent, string dateOfEvent, string openingTime, int noOfZones, int eventID) :nameOfEvent(this->setName(nameOfEvent)), eventID(eventID) {
		this->setLocation(locationOfEvent);
		this->setDate(dateOfEvent);
		this->setTime(openingTime);
		this->setNoOfZones(noOfZones);
	}

	Event(string nameOfEvent, string locationOfEvent, int noOfZones, int eventID) : nameOfEvent(this->setName(nameOfEvent)), eventID(eventID) {
		this->setLocation(locationOfEvent);
		this->setNoOfZones(noOfZones);
	}

	Event(const Event& event):nameOfEvent(this->setName(event.nameOfEvent)), eventID(event.eventID) {
		this->setDate(event.getDate());
		this->setTime(event.getTime());
		this->setLocation(event.getLocation());
		this->setNoOfZones(event.getNoOfZones());
		/*this->zone = new Zone[this->noOfZones];*/
	}

	/*~Event() {
		delete zone;
	}*/

	void operator=(const Event& event) {
		this->setDate(event.getDate());
		this->setTime(event.getTime());
		this->setLocation(event.getLocation());
		this->setNoOfZones(event.getNoOfZones());
		/*this->zone = new Zone[this->noOfZones];*/
	}



	static const int MIN_NAME_SIZE{ 3 };
	static const int MAX_NAME_SIZE{ 50 };
	static const int MIN_ZONE_NO{ 1 };
	static const int MAX_ZONE_NO{ 10 };
	static const int MIN_ZONE_PRICE{ 5 };
	static const int MIN_ROW_SEAT_NO{ 1 };
	static const int MAX_ROW_SEAT_NO{ 50 };

private:
	const string nameOfEvent;
	string locationOfEvent{}, dateOfEvent{}, openingTime{};
	const int eventID;
	int noOfZones{};
	Zone* zone{};
};

struct Zone {
	string getNameOfZone() const {
		return this->nameOfZone;
	}
	void setNameOfZone(string nameOfZone) {
		if (nameOfZone.size() < Event::MIN_NAME_SIZE || nameOfZone.size() > Event::MAX_NAME_SIZE)throw exception("");
		this->nameOfZone = nameOfZone;
	}

	int getNoOfRows() const {
		return this->noOfRows;
	}
	bool setNoOfRows(int noOfRows) {
		if (noOfRows < Event::MIN_ROW_SEAT_NO || noOfRows > Event::MAX_ROW_SEAT_NO)return false;
		this->noOfRows = noOfRows;
	}

	float getPriceOfZone() const {
		return this->priceOfZone;
	}
	void setPriceOfZone(float priceOfZone) {
		if (priceOfZone < Event::MIN_ZONE_PRICE)throw exception("");
		this->priceOfZone = priceOfZone;
	}

	void addNewZone(Zone* newZone) {
		newZone->nextZone = this->nextZone;
		this->nextZone = newZone;
	}

	Zone(string nameOfZone, float priceOfZone, int noOfRows) {
		this->setNameOfZone(nameOfZone);
		this->setNoOfRows(noOfRows);
	}

	Zone(string nameOfZone) : priceOfZone(Event::MIN_ZONE_PRICE), noOfRows(Event::MIN_ROW_SEAT_NO) {
		this->setNameOfZone(nameOfZone);
	}

	Zone(Zone& zone) {
		this->setNameOfZone(zone.getNameOfZone());
		this->setPriceOfZone(zone.getPriceOfZone());
		this->setNoOfRows(zone.getNoOfRows());
		/*zone.addNewZone(this);*/
		/*Row* rowList = new Row[this->noOfRows];*/
	}

	void operator=(Zone& zone) {
		this->setNameOfZone(zone.getNameOfZone());
		this->setPriceOfZone(zone.getPriceOfZone());
		this->setNoOfRows(zone.getNoOfRows());
		/*zone.addNewZone(this);*/
		/*Row* rowList = new Row[this->noOfRows];*/
	}

private:
	string nameOfZone{};
	float priceOfZone{};
	int noOfRows{};
	Row* row{};
	Zone* nextZone{};
};

struct Row {
	string getRowLetters() const {
		string rowLetter = to_string(this->rowLetter[0]) + to_string(this->rowLetter[1]);
		return rowLetter;
	}

	int getNoOfSeats() const {
		return this->noOfSeats;
	}
	void setNoOfSeats(int noOfSeats) {
		if (noOfSeats < Event::MIN_ROW_SEAT_NO || noOfSeats > Event::MAX_ROW_SEAT_NO)throw exception("");
		this->noOfSeats = noOfSeats;
	}

	void addNewRow(Row* newRow) {
		newRow->nextRow = this->nextRow;
		this->nextRow = newRow;
		if (this->rowLetter[1] < 'Z') {
			newRow->rowLetter[0] = this->rowLetter[0];
			newRow->rowLetter[1] = this->rowLetter[1] + 1;
			return;
		}
		if (this->rowLetter[1] == 'Z') {
			newRow->rowLetter[1] = 'A';
			newRow->rowLetter[0] = this->rowLetter[0] + 1;
			return;
		}
	}

	Row(int noOfSeats) {
		this->setNoOfSeats(noOfSeats);
	}

	Row() : noOfSeats(Event::MIN_ROW_SEAT_NO){

	}

private:
	char rowLetter[2] = {'A', 'A'};
	int noOfSeats{};
	Seat* seat{};
	Row* nextRow{};
};

struct Seat {
	int getSeatNo() const {
		return this->seatNo;
	}
	void setSeatNo(int seatNo) {

	}

	bool getAccesibility() const {
		return this->isAccesible;
	}
	bool setAccesibility() {
		this->isAccesible = true;
	}

	void addNewSeat(Seat* newSeat) {
		newSeat->nextSeat = this->nextSeat;
		this->nextSeat = newSeat;
		newSeat->seatNo = this->seatNo + 1;
	}

private:
	int seatNo{};
	bool isAccesible{};
	Ticket* ticket{};
	Seat* nextSeat{};
};

struct Ticket {

private:
	const int ticketID;
	string* attributes{};
};