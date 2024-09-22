# include "TemperatureData.h"
# include <iostream>
using std::string;

TemperatureData::TemperatureData() : id(""), year(0), month(0), temperature(0.0) {

}

TemperatureData::TemperatureData(string id, int year, int month, double temperature) : id(id), year(year), month(month), temperature(temperature) {
	
}

TemperatureData::~TemperatureData() {}

bool TemperatureData::operator<(const TemperatureData& b) {
	if (id < b.id) {
		return true;
	}
	else if (id > b.id) {
		return false;
	}
	else {
		if (year < b.year) {
			return true;
		}
		else if (year > b.year) {
			return false;
		}
		else {
			if (month < b.month) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}