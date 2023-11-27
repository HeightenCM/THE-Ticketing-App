#include <iostream>
#include "projclasslib.h"

using namespace std;

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
	bool option{};
	cout << "\nDo you wish to buy tickets for the created event? 0 for no, 1 for yes." << endl;
	cin >> option;
	if (option == 0)return 0;
	string selectedZone{}, selectedRow{};
	int selectedSeat{};
	cout << "In which zone do you wish to buy the ticket?" << endl;
	cin >> selectedZone;
	for (int i = 0; i < event.getNoOfZones(); i++) {
		if (event.getZone(i)->getNameOfZone() == selectedZone) {
			cout << "On which row do you wish to stay?" << endl;
			cin >> selectedRow;
			for (int j = 0; j < event.getZone(i)->getNoOfRows(); i++) {
				if (event.getZone(i)->getRow(j)->getRowLetters() == selectedRow) {
					cout << "Which seat do you want?" << endl;
					cin >> selectedSeat;
					for (int k = 0; k < event.getZone(i)->getRow(j)->getNoOfSeats(); k++) {
						if (event.getZone(i)->getRow(j)->getSeat(k)->getSeatNo() == selectedSeat) {
							if (event.getZone(i)->getRow(j)->getSeat(k)->isSold())throw exception("Seat is sold!");
							event.getZone(i)->getRow(j)->getSeat(k)->sellTicket();
							cout << "Ticket bought succesfully! Your ID is " << event.getZone(i)->getRow(j)->getSeat(k)->getTicket()->getTicketID() << endl;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
}