# include "TemperatureDatabase.h"
# include <fstream>
# include <sstream>

using std::cout, std::endl, std::string, std::ofstream;

TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	string inputLine;
	std::ifstream file(filename);
	string inputID;
	int inputYear;
	int inputMonth;
	double inputTemp;

	if (!file.is_open()) {
		throw std::runtime_error("File failed to open");
	}
	while (std::getline(file, inputLine)) {
		std::stringstream dataLine(inputLine);
		dataLine >> inputID >> inputYear >> inputMonth >> inputTemp;

		if (dataLine.fail()) {
			cout << "Error: Other invalid input" << endl;
			continue;
		}
		if (inputYear < 1800 || inputYear > 2024) {
			cout << "Error: Invalid year " << inputYear << endl;
			continue;
		}
		if (inputMonth < 1 || inputMonth > 12) {
			cout << "Error: Invalid month " << inputMonth << endl;
			continue;
		}
		if (inputTemp < -50.0 || inputTemp > 50.0) {
			cout << "Error: Invalid temperature " << inputTemp << endl;
			continue;
		}
		records.insert(inputID, inputYear, inputMonth, inputTemp);
	}
	file.close();
}

void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}

	dataout << records.print();
}

void TemperatureDatabase::performQuery(const string& filename) {
	string inputLine;
	std::ifstream file(filename);
	ofstream result("result.dat");
	string queryID;
	string query;
	int lowYearBound;
	int highYearBound;
	
	if (!result.is_open()) {
		throw std::runtime_error("Unable to open result.dat");
	}
	if (!file.is_open()) {
		throw std::runtime_error("File failed to open");
	}

	while (std::getline(file, inputLine)) {
		std::stringstream dataLine(inputLine);
		dataLine >> queryID >> query >> lowYearBound >> highYearBound;

		if (dataLine.fail()) {
			cout << "Error: Other invalid query" << endl;
			continue;
		}
		if (query != "AVG" && query != "MODE") {
			cout << "Error: Unsupported query " << query << endl;
			continue;
		}
		if (highYearBound < lowYearBound || highYearBound > 2024 || highYearBound < 1800 || lowYearBound > 2024 || lowYearBound < 1800) {
			cout << "Error: Invalid range " << lowYearBound << "-" << highYearBound << endl;
			continue;
		}

		if (query == "AVG") {
			double total = 0;
			int count = 0;
			double average;
			Node* current = records.getHead();

			while (current) {
				if (current->data.id == queryID && (current->data.year >= lowYearBound && current->data.year <= highYearBound)) {
					total += current->data.temperature;
					++count;
				}
				current = current->next;
			}

			if (count == 0) {
				result << queryID << " " << lowYearBound << " " << highYearBound << " " << query << " unknown" << endl;
			}
			else {
				average = total / count;
				result << queryID << " " << lowYearBound << " " << highYearBound << " " << query << " " << average << endl;
			}	
		}

		else if (query == "MODE") {
			int currTemp = -50;
			int tempCount = 0;
			int currCount;
			int roundedTemp;

			for (int temp = -50; temp <= 50; ++temp) {
				Node* current = records.getHead();
				currCount = 0;

				while (current) {
					if (current->data.id == queryID && (current->data.year >= lowYearBound && current->data.year <= highYearBound)) {
						roundedTemp = static_cast<int>(current->data.temperature);
						if (roundedTemp >= 0 && current->data.temperature - roundedTemp >= 0.5) {
							++roundedTemp;
						}
						if (roundedTemp < 0 && current->data.temperature - roundedTemp <= -0.5) {
							--roundedTemp;
						}
						if (roundedTemp == temp) {
							++currCount;
						}
					}
					current = current->next;
				}
				if ((currCount == tempCount && temp > currTemp) || currCount > tempCount) {
					tempCount = currCount;
					currTemp = temp;
				}
			}

			if (tempCount == 0) {
				result << queryID << " " << lowYearBound << " " << highYearBound << " " << query << " unknown" << endl;
			}
			else {
				result << queryID << " " << lowYearBound << " " << highYearBound << " " << query << " " << currTemp << endl;
			}	
		}
	}
	file.close();
	result.close();
}
