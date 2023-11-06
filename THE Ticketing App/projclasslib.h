#pragma once

#include <iostream>
#include <string>

using namespace std;

enum class EventType{Movie, Play, Match};

struct Event {

private:
	string nameOfEvent{};
	char* date{};
	char* openingTime{};
};