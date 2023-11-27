#pragma once

#include <iostream>
#include <string>

using namespace std;

enum class AccesibilityGrade { NONE = 0, MINOR_DISABILITIES = 1, MAJOR_DISABILITIES = 2 };

struct Utility {
	static const int MIN_NAME_SIZE{ 3 };
	static const int MAX_NAME_SIZE{ 50 };
	static const int MIN_ZONE_NO{ 1 };
	static const int MAX_ZONE_NO{ 10 };
	static const int MIN_ZONE_PRICE{ 5 };
	static const int MIN_ROW_SEAT_NO{ 1 };
	static const int MAX_ROW_SEAT_NO{ 50 };
	static const int MAX_SPONSORS{ 5 };
	static const int MAX_ZONE_FEATURE{ 3 };
	static const int MAX_COLORS{ 3 };

	static char* copyCharArray(const char* sourceArray) {
		size_t sizeOfSourceArray = strlen(sourceArray) + 1;
		char* copy = new char[sizeOfSourceArray];
		strcpy_s(copy, sizeOfSourceArray, sourceArray);
		return copy;
	}
	static string* copyStringArray(string* sourceArray, int size) {
		string* copy = new string[size];
		for (int i = 0; i < size; i++) {
			copy[i] = sourceArray[i];
		}
		return copy;
	}
	static bool isNumeric(const char source) {
		if (source < '0' || source>'9')return false;
		return true;
	}
	static string AccesibilityToString(AccesibilityGrade accesible) {
		switch (accesible) {
		case AccesibilityGrade::NONE:
			return "Seat isn't destined for people with disabilities.";
			break;
		case AccesibilityGrade::MINOR_DISABILITIES:
			return "Seat is destined for people with minor disabilities.";
			break;
		case AccesibilityGrade::MAJOR_DISABILITIES:
			return "Seat is destined for people with major disabilities.";
			break;
		default:
			throw exception("Type not covered");
		}

	}
	static AccesibilityGrade intToAccesibility(int grade) {
		switch (grade) {
		case 0:
			return AccesibilityGrade::NONE;
			break;
		case 1:
			return AccesibilityGrade::MINOR_DISABILITIES;
			break;
		case 2:
			return AccesibilityGrade::MAJOR_DISABILITIES;
			break;
		default:
			throw exception("Index outside boundaries!");
		}
	}
};

struct Ticket {
	int getTicketID() const {
		return this->ticketID;
	}

	string* getAttributes() const {
		return Utility::copyStringArray(this->attributes, this->noOfAttributes);
	}
	int getNumberOfAttributes() const {
		return this->noOfAttributes;
	}
	void addAttribute(string newAttribute) {
		this->noOfAttributes++;
		string* copy = new string[this->noOfAttributes];
		for (int i = 0; i < this->noOfAttributes - 2; i++) {
			copy[i] = this->attributes[i];
		}
		copy[this->noOfAttributes - 1] = newAttribute;
		delete[] this->attributes;
		this->attributes = copy;
	}

	Ticket(string* attributes, int noOfAttributes) :ticketID(Ticket::id_no--) {
		for (int i = 0; i < noOfAttributes; i++) {
			this->addAttribute(attributes[i]);
		}
	}

	Ticket() :ticketID(Ticket::id_no--) {

	}

	Ticket(Ticket& ticket) : ticketID(Ticket::id_no--) {
		this->noOfAttributes = ticket.noOfAttributes;
		if (ticket.noOfAttributes != 0) {
			string* attributes = new string[ticket.noOfAttributes];
			for (int i = 0; i < ticket.noOfAttributes; i++) {
				attributes[i] = ticket.attributes[i];
			}
		}
		this->attributes = attributes;
	}

	~Ticket() {
		if (this->attributes != nullptr)delete[] this->attributes;
	}

	Ticket& operator=(Ticket& ticket) {
		this->noOfAttributes = ticket.noOfAttributes;
		if (ticket.noOfAttributes != 0) {
			string* attributes = new string[ticket.noOfAttributes];
			for (int i = 0; i < ticket.noOfAttributes; i++) {
				attributes[i] = ticket.attributes[i];
			}
		}
		this->attributes = attributes;
		return *this;
	}

	string& operator[](int index) {
		if (index < 0 || index >= this->noOfAttributes) {
			throw exception("Invalid attribute index!");
		}
		return this->attributes[index];
	}

	Ticket operator+(Ticket& ticket) {
		Ticket newTicket(*this);
		for (int i = 0; i < ticket.noOfAttributes; i++) {
			newTicket.addAttribute(ticket.attributes[i]);
		}
		return newTicket;
	}

	Ticket operator++() {
		string newAttribute;
		cout << "\nNew attribute is: ";
		cin >> newAttribute;
		this->addAttribute(newAttribute);
	}

	operator int() const {
		return this->ticketID;
	}

	bool operator>(Ticket& ticket) {
		if (this->noOfAttributes > ticket.noOfAttributes)return true;
		return false;
	}

	bool operator==(Ticket& ticket) {
		if (this->noOfAttributes == ticket.noOfAttributes) {
			for (int i = 0; i < this->noOfAttributes; i++) {
				if (this->attributes[i] != ticket.attributes[i])return false;
			}
		}
		else return false;
		return true;
	}

private:
	const int ticketID;
	string* attributes{};
	int noOfAttributes{};

	static int id_no;
};

int Ticket::id_no = UINT64_MAX;

void operator<<(ostream os, Ticket& ticket) {
	os << "\nTicket ID is " << ticket.getTicketID();
	os << "\nTicket attributes are ";
	string* featureArray = ticket.getAttributes();
	for (int i = 0; i < ticket.getNumberOfAttributes(); i++) {
		os << featureArray[i] << " ";
	}
}

//istream& operator>>(istream is, Ticket& ticket) {
//	string newAttribute{};
//	cout << "\nNew attribute is ";
//	is >> newAttribute;
//	ticket.addAttribute(newAttribute);
//}

struct Seat {
	int getSeatNo() const {
		return this->seatNo;
	}
	void setSeatNumber(int seatNo) {
		if (seatNo > Utility::MAX_ROW_SEAT_NO)throw exception("Row number too high!");
		this->seatNo = seatNo;
	}

	string getAccesibility() const {
		return Utility::AccesibilityToString(this->accesible);
	}
	void setAccesibility(AccesibilityGrade grade) {
		this->accesible = grade;
	}

	int getNoOfColors() const {
		return this->noOfColors;
	}

	void addColor(string newColor) {
		if (this->noOfColors >= Utility::MAX_COLORS)throw exception("Too many colors!");
		this->colors[this->noOfColors++] = newColor;
	}

	string* getColors() {
		return Utility::copyStringArray(this->colors, this->noOfColors);
	}

	bool isSold() {
		if (this->ticket == nullptr)return false;
		return true;
	}

	void sellTicket() {
		this->ticket = new Ticket();
	}

	Ticket* getTicket() {
		return this->ticket;
	}

	Seat(int seatNo, AccesibilityGrade grade, string* colors, int noOfColors) {
		this->setAccesibility(grade);
		this->setSeatNumber(seatNo);
		if (noOfColors > Utility::MAX_COLORS)throw exception("Too many colors!");
		for (int i = 0; i < noOfColors; i++) {
			this->colors[i] = colors[i];
		}
	}

	Seat(int seatNo, string* colors, int noOfColors) {
		if (noOfColors > Utility::MAX_COLORS)throw exception("Too many colors!");
		for (int i = 0; i < noOfColors; i++) {
			this->colors[i] = colors[i];
		}
		this->setSeatNumber(seatNo);
	}

	Seat(int seatNo) {
		this->setSeatNumber(seatNo);
	}

	Seat(Seat& seat) {
		this->setAccesibility(seat.accesible);
		this->seatNo = seat.seatNo + 1;
		this->noOfColors = seat.noOfColors;
		for (int i = 0; i < seat.noOfColors; i++) {
			this->colors[i] = seat.colors[i];
		}
	}

	~Seat() {
		if (this->ticket != nullptr)delete[] this->ticket;
	}

	Seat& operator=(Seat& seat) {
		this->setAccesibility(seat.accesible);
		this->seatNo = seat.seatNo + 1;
		this->noOfColors = seat.noOfColors;
		for (int i = 0; i < seat.noOfColors; i++) {
			this->colors[i] = seat.colors[i];
		}
		return *this;
	}

	string& operator[](int index) {
		if (index < 0 || index >= noOfColors)throw exception("Invalid color index!");
		return this->colors[index];
	}

	Seat operator+(Seat& ticket) {
		Seat newSeat(*this);
		for (int i = 0; i < ticket.noOfColors; i++) {
			newSeat.addColor(ticket.colors[i]);
		}
		return newSeat;
	}

	Seat operator++() {
		string newColor;
		cout << "\nNew color is: ";
		cin >> newColor;
		this->addColor(newColor);
	}

	void operator!() {
		this->setAccesibility(AccesibilityGrade::NONE);
	}

	operator int() const {
		return this->seatNo;
	}

	bool operator>(Seat& seat) {
		if (this->noOfColors > seat.noOfColors)return true;
		return false;
	}

	bool operator==(Seat& seat) {
		if (this->noOfColors == seat.noOfColors) {
			for (int i = 0; i < this->noOfColors; i++) {
				if (this->colors[i] != seat.colors[i])return false;
			}
		}
		else return false;
		return true;
	}

private:
	int seatNo{};
	AccesibilityGrade accesible{};
	string colors[Utility::MAX_COLORS] = {};
	int noOfColors{};
	Ticket* ticket{};
};

void operator<<(ostream os, Seat& seat) {
	os << "\nSeat accesibility state: " << seat.getAccesibility();
	os << "\nSeat number is " << seat.getSeatNo();
	os << "\nSeat colors are ";
	string* colorArray = seat.getColors();
	for (int i = 0; i < seat.getNoOfColors(); i++) {
		os << colorArray[i] << " ";
	}
}

struct Row {
	string getRowLetters() const {
		string rowLetters = string(1, this->rowLetter[0]) + string(1, this->rowLetter[1]);
		return rowLetters;
	}
	void setRowLetters(const char* letters) {
		if (strlen(letters) > 2)throw exception("Too many letters!");
		this->rowLetter[0] = letters[0];
		this->rowLetter[1] = letters[1];
	}

	int getNoOfSeats() const {
		return this->noOfSeats;
	}
	void setNoOfSeats(int noOfSeats) {
		if (noOfSeats < Utility::MIN_ROW_SEAT_NO || noOfSeats > Utility::MAX_ROW_SEAT_NO)throw exception("Too many or not enough seats!");
		this->noOfSeats = noOfSeats;
	}

	Seat* getSeat(int index) {
		if (index<0 || index>this->noOfSeats)throw exception("Seat index outside boundaries!");
		return this->seat[index];
	}

	Row(int noOfSeats, const char* rowLetters) {
		this->setNoOfSeats(noOfSeats);
		this->setRowLetters(rowLetters);
		int seatNo{ 1 };
		this->seat = new Seat * [noOfSeats];
		for (int i = 0; i < noOfSeats; i++) {
			this->seat[i] = new Seat(seatNo);
			seatNo++;
		}
	}

	Row(const char* rowLetters) : noOfSeats(Utility::MIN_ROW_SEAT_NO) {
		this->setRowLetters(rowLetters);
		int seatNo{ 1 };
		this->seat = new Seat * [noOfSeats];
		for (int i = 0; i < noOfSeats; i++) {
			this->seat[i] = new Seat(seatNo);
			seatNo++;
		}
	}

	Row(Row& row) {
		this->setNoOfSeats(row.getNoOfSeats());
		if (row.rowLetter[1] == 'Z') {
			this->rowLetter[0]++;
		}
		else this->rowLetter[1]++;
		this->seat = new Seat * [noOfSeats];
		for (int i = 0; i < noOfSeats; i++) {
			this->seat[i] = row.seat[i];
		}
	}

	~Row() {
		if (this->seat != nullptr)delete[] this->seat;
	}

	Row& operator=(Row& row) {
		this->setNoOfSeats(row.noOfSeats);
		if (row.rowLetter[1] == 'Z') {
			this->rowLetter[0]++;
		}
		else this->rowLetter[1]++;
		this->seat = new Seat * [noOfSeats];
		for (int i = 0; i < noOfSeats; i++) {
			this->seat[i] = row.seat[i];
		}
		return *this;
	}

	char& operator[](int index) {
		if (index < 0 || index>1)throw exception("Invalid row letter index!");
		return this->rowLetter[index];
	}

	bool operator>(Row& row) {
		if (this->rowLetter[0] > row.rowLetter[0])return true;
		if (this->rowLetter[0] == row.rowLetter[0]) {
			if (this->rowLetter[1] > row.rowLetter[1])return true;
		}
		return false;
	}

	bool operator==(Row& row) {
		for (int i = 0; i < 2; i++) {
			if (this->rowLetter[i] != row.rowLetter[i])return false;
		}
		return true;
	}

private:
	char rowLetter[2] = { 'A', 'A' };
	int noOfSeats{};
	Seat** seat{};
};

void operator<<(ostream os, Row& row) {
	os << "\nRow seats number is " << row.getNoOfSeats();
	os << "\nRow letters are " << row.getRowLetters();
}

struct Zone {
	string getNameOfZone() const {
		return this->nameOfZone;
	}
	void setNameOfZone(string nameOfZone) {
		if (nameOfZone.size() < Utility::MIN_NAME_SIZE || nameOfZone.size() > Utility::MAX_NAME_SIZE)throw exception("Name outside of boundaries!");
		this->nameOfZone = nameOfZone;
	}

	int getNoOfRows() const {
		return this->noOfRows;
	}
	bool setNoOfRows(int noOfRows) {
		if (noOfRows < Utility::MIN_ROW_SEAT_NO || noOfRows > Utility::MAX_ROW_SEAT_NO)return false;
		this->noOfRows = noOfRows;
	}

	float getPriceOfZone() const {
		return this->priceOfZone;
	}
	void setPriceOfZone(float priceOfZone) {
		if (priceOfZone < Utility::MIN_ZONE_PRICE)throw exception("Price too low!");
		this->priceOfZone = priceOfZone;
	}

	int getNoOfFeatures() const {
		return this->noOfFeatures;
	}

	void addFeature(string newFeature) {
		if (this->noOfFeatures >= Utility::MAX_ZONE_FEATURE)throw exception("Too many features!");
		this->features[this->noOfFeatures++] = newFeature;
	}

	string* getFeatures() {
		return Utility::copyStringArray(this->features, this->noOfFeatures);
	}

	Row* getRow(int index) {
		if (index<0 || index>this->noOfRows)throw exception("Row index outside boundaries!");
		return this->row[index];
	}

	Zone(string nameOfZone, float priceOfZone, int noOfRows, string* features, int noOfFeatures) {
		this->setNameOfZone(nameOfZone);
		this->setNoOfRows(noOfRows);
		this->setPriceOfZone(priceOfZone);
		this->noOfFeatures = noOfFeatures;
		if (noOfFeatures >= Utility::MAX_ZONE_FEATURE)throw exception("Too many features!");
		for (int i = 0; i < noOfFeatures; i++) {
			this->features[i] = features[i];
		}
		string rowLetters = { "AA" };
		this->row = new Row * [noOfRows];
		for (int i = 0; i < noOfRows; i++) {
			this->row[i] = new Row(rowLetters.c_str());
			if (rowLetters[1] == 'Z') {
				rowLetters[1] = 'A';
				rowLetters[0]++;
			}
			else rowLetters[1]++;
		}
	}

	Zone(string nameOfZone) : priceOfZone(Utility::MIN_ZONE_PRICE), noOfRows(Utility::MIN_ROW_SEAT_NO) {
		this->setNameOfZone(nameOfZone);
		string rowLetters = { "AA" };
		this->row = new Row * [noOfRows];
		for (int i = 0; i < noOfRows; i++) {
			this->row[i] = new Row(rowLetters.c_str());
			if (rowLetters[1] == 'Z') {
				rowLetters[1] = 'A';
				rowLetters[0]++;
			}
			else rowLetters[1]++;
		}
	}

	Zone(Zone& zone) {
		this->setNameOfZone(zone.getNameOfZone());
		this->setPriceOfZone(zone.getPriceOfZone());
		this->setNoOfRows(zone.getNoOfRows());
		this->row = new Row * [noOfRows];
		for (int i = 0; i < noOfRows; i++) {
			this->row[i] = zone.row[i];
		}
	}

	~Zone() {
		if (this->row != nullptr)delete[] this->row;
	}

	Zone& operator=(Zone& zone) {
		this->setNameOfZone(zone.getNameOfZone());
		this->setPriceOfZone(zone.getPriceOfZone());
		this->setNoOfRows(zone.getNoOfRows());
		this->row = new Row * [noOfRows];
		for (int i = 0; i < noOfRows; i++) {
			this->row[i] = zone.row[i];
		}
		return *this;
	}

	string& operator[](int index) {
		if (index<0 || index>this->noOfFeatures)throw exception("Features index out of boundaries!");
		return this->features[index];
	}

	Zone operator+(Zone& zone) {
		Zone newZone(*this);
		for (int i = 0; i < zone.noOfFeatures; i++) {
			newZone.addFeature(zone.features[i]);
		}
		return newZone;
	}

	Zone operator++() {
		string newFeature;
		cout << "\nNew feature is: ";
		cin >> newFeature;
		this->addFeature(newFeature);
	}

	void operator!() {
		this->priceOfZone = Utility::MIN_ZONE_PRICE;
	}

	operator string() const {
		return this->getNameOfZone();
	}

	bool operator>(Zone& zone) {
		if (this->noOfFeatures > zone.noOfFeatures)return true;
		return false;
	}

	bool operator==(Zone& zone) {
		if (this->noOfFeatures == zone.noOfFeatures) {
			for (int i = 0; i < this->noOfFeatures; i++) {
				if (this->features[i] != zone.features[i])return false;
			}
		}
		else return false;
		return true;
	}

private:
	string nameOfZone{};
	float priceOfZone{};
	int noOfRows{};
	string features[Utility::MAX_ZONE_FEATURE];
	int noOfFeatures{};
	Row** row{};
};

void operator<<(ostream os, Zone& zone) {
	os << "\nZone name is " << zone.getNameOfZone();
	os << "\nZone price is " << zone.getPriceOfZone();
	os << "\nZone rows number is " << zone.getNoOfRows();
	os << "\nZone features are ";
	string* featureArray = zone.getFeatures();
	for (int i = 0; i < zone.getNoOfFeatures(); i++) {
		os << featureArray[i] << " ";
	}
}

struct Event {
	string getName() const {
		return this->nameOfEvent;
	}
	string checkName(string nameOfEvent) {
		if (nameOfEvent.size() < Utility::MIN_NAME_SIZE || nameOfEvent.size() > Utility::MAX_NAME_SIZE) throw exception("Name size out of boundaries!");
		return nameOfEvent;
	}

	string getLocation() const {
		return this->locationOfEvent;
	}
	void setLocation(string locationOfEvent) {
		if (locationOfEvent.size() < Utility::MIN_NAME_SIZE || locationOfEvent.size() > Utility::MAX_NAME_SIZE) throw exception("Location size out of boundaries!");
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
							return;
						}
					}
				}
			}
		}
		throw exception("Date is of invalid format!");
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
						return;
					}
				}
			}
		}
		throw exception("Time is of invalid format!");
	}

	int getNoOfZones() const {
		return this->noOfZones;
	}
	void setNoOfZones(int noOfZones) {
		if (noOfZones<Utility::MIN_ZONE_NO || noOfZones>Utility::MAX_ZONE_NO)throw exception("Number of zones outside of boundaries!");
	}

	int getNoOfSponsors() const {
		return this->noOfSponsors;
	}
	string* getSponsors() {
		return Utility::copyStringArray(this->sponsors, this->noOfSponsors);
	}
	
	void addSponsor(string newSponsor) {
		if (this->noOfSponsors >= Utility::MAX_SPONSORS)throw exception("Too many sponsors!");
		this->sponsors[this->noOfSponsors++] = newSponsor;
	}

	Zone* getZone(int index) {
		if (index<0 || index>this->noOfZones)throw exception("Zone index outside boundaries!");
		return this->zone[index];
	}

	Event(string nameOfEvent, string locationOfEvent, string dateOfEvent, string openingTime, string* sponsors, int noOfSponsors, int noOfZones) :nameOfEvent(this->checkName(nameOfEvent)) {
		this->setLocation(locationOfEvent);
		this->setDate(dateOfEvent);
		this->setTime(openingTime);
		if (noOfSponsors > Utility::MAX_SPONSORS)throw exception("Too many sponsors!");
		for (int i = 0; i < noOfSponsors; i++) {
			this->sponsors[i] = sponsors[i];
		}
		this->setNoOfZones(noOfZones);
		this->zone = new Zone * [noOfZones];
		string name{};
		for (int i = 0; i < noOfZones; i++) {
			cout << "Name of zone " << i << " is ";
			cin >> name;
			this->zone[i] = new Zone(name);
		}
	}

	Event(string nameOfEvent, int noOfZones) : nameOfEvent(this->checkName(nameOfEvent)) {
		this->setNoOfZones(noOfZones);
		this->zone = new Zone * [noOfZones];
		string name{};
		for (int i = 0; i < noOfZones; i++) {
			cin >> name;
			this->zone[i] = new Zone(name);
		}
	}

	Event(const Event& event) :nameOfEvent(this->checkName(event.nameOfEvent)) {
		this->setDate(event.getDate());
		this->setTime(event.getTime());
		this->setLocation(event.getLocation());
		this->noOfSponsors = event.getNoOfSponsors();
		for (int i = 0; i < event.getNoOfSponsors(); i++) {
			this->sponsors[i] = event.sponsors[i];
		}
		this->setNoOfZones(event.getNoOfZones());
		this->zone = new Zone * [noOfZones];
		for (int i = 0; i < noOfZones; i++) {
			this->zone[i] = event.zone[i];
		}
	}

	~Event() {
		if(this->zone!=nullptr)delete[] zone;
	}

	Event& operator=(Event& event) {
		this->setDate(event.getDate());
		this->setTime(event.getTime());
		this->setLocation(event.getLocation());
		this->setNoOfZones(event.getNoOfZones());
		this->zone = new Zone * [noOfZones];
		for (int i = 0; i < noOfZones; i++) {
			this->zone[i] = event.zone[i];
		}
		return *this;
	}

	string& operator[](int index) {
		if (index<0 || index>this->noOfSponsors)throw exception("Sponsors index out of boundaries!");
		return this->sponsors[index];
	}

	Event operator+(Event& event) {
		Event newEvent(*this);
		for (int i = 0; i < event.noOfSponsors; i++) {
			newEvent.addSponsor(event.sponsors[i]);
		}
		return newEvent;
	}

	Event operator++() {
		string newSponsor;
		cout << "\nNew sponsor is: ";
		cin >> newSponsor;
		this->addSponsor(newSponsor);
	}

	void operator!() {
		for (int i = 0; i < this->noOfSponsors; i++) {
			this->sponsors[i] = "";
		}
	}

	operator string() const {
		return this->getName();
	}

	bool operator>(Event& event) {
		if (this->noOfSponsors > event.noOfSponsors)return true;
		return false;
	}

	bool operator==(Event& event) {
		if (this->noOfSponsors == event.noOfSponsors) {
			for (int i = 0; i < this->noOfSponsors; i++) {
				if (this->sponsors[i] != event.sponsors[i])return false;
			}
		}
		else return false;
		return true;
	}

private:
	const string nameOfEvent;
	string locationOfEvent{}, dateOfEvent{}, openingTime{};
	int noOfZones{};
	string sponsors[Utility::MAX_SPONSORS] = {};
	int noOfSponsors{};
	Zone** zone{};
};

void operator<<(ostream os, Event& event) {
	os << "\nEvent name is " << event.getName();
	os << "\nEvent location is " << event.getLocation();
	os << "\nEvent date is " << event.getDate();
	os << "\nEvent opening time is " << event.getTime();
	os << "\nEvent zones number is " << event.getNoOfZones();
	os << "\nEvent sponsors are ";
	string* sponsors = event.getSponsors();
	for (int i = 0; i < event.getNoOfSponsors(); i++) {
		os << sponsors[i] << " ";
	}
}