#include <iostream>
#include "projclasslib.h"

using namespace std;

void buyTicket(Event& event) {
	Zone* currentZone{};
	Row* currentRow{};
	Seat* currentSeat{};

	string selectedZone{}, selectedRow{};
	int selectedSeat{};
	cout << "In which zone do you wish to buy the ticket?" << endl;
	cin >> selectedZone;

	for (int i = 0; i < event.getNoOfZones(); i++) {
		if (event.getZone(i)->getNameOfZone() == selectedZone) {
			currentZone = event.getZone(i);
			break;
		}
	}

	if (currentZone != nullptr) {
		cout << "On which row do you wish to stay? Row format is XX where X is a letter of the English alphabet." << endl;
		cin >> selectedRow;
		for (int i = 0; i < currentZone->getNoOfRows(); i++) {
			if (currentZone->getRow(i)->getRowLetters() == selectedRow) {
				currentRow = currentZone->getRow(i);
				break;
			}
		}
	}

	if (currentRow != nullptr) {
		cout << "Which seat do you want?" << endl;
		cin >> selectedSeat;
		for (int i = 0; i < currentRow->getNoOfSeats(); i++) {
			if (currentRow->getSeat(i)->getSeatNo() == selectedSeat) {
				currentSeat = currentRow->getSeat(i);
				break;
			}
		}
	}

	if (currentSeat != nullptr) {
		if (currentSeat->isSold())throw exception("Seat is sold!");
		currentSeat->sellTicket();
		cout << "Ticket bought succesfully! Your ID is " << currentSeat->getTicket()->getTicketID() << endl;
	}

	bool anotherTicket{};
	cout << endl << "Do you wish to buy another ticket? 1 for yes, 0 for no." << endl;
	cin >> anotherTicket;
	if (anotherTicket)buyTicket(event);
}

int main() {
	string name{}, location{}, time{}, date{};
	int noOfSponsors{}, noOfZones{};
	string* sponsors{};
	cout << "Welcome! Let's begin by creating an event." << endl;
	cout << "What's the name of the event? This cannot be changed later." << endl;
	cin >> name;
	cout << "What's the location of the event?" << endl;
	cin >> location;
	cout << "What's the date of the event? Accepted format is YYYY/MM/DD." << endl;
	cin >> date;
	cout << "What's the oppening time of the event? Accepted format is HH:MM." << endl;
	cin >> time;
	cout << "How many sponsors does the event have?" << endl;
	cin >> noOfSponsors;
	sponsors = new string[noOfSponsors];
	for (int i = 0; i < noOfSponsors; i++) {
		cout << "\nSponsor number " << i << " is ";
		cin >> sponsors[i];
	}
	cout << "How many zones are there?" << endl;
	cin >> noOfZones;
	Event event(name, location, date, time, sponsors, noOfSponsors, noOfZones);


	bool wannaBuyTicket{};
	cout << "\nDo you wish to buy tickets for the created event? 0 for no, 1 for yes." << endl;
	cin >> wannaBuyTicket;
	if (wannaBuyTicket)buyTicket(event);
}