#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range

	return (10 <= a && a <= b && b < 10000);
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise

	char prev;
	if (number % 10 > ((number / 10) % 10)) {
		prev = '/';
	}
	else if (number % 10 < ((number / 10) % 10)) {
		prev = '\\';
	}
	else if (number % 10 == ((number / 10) % 10)) {
			return 'N';
	}

	while (true) {

		number /= 10;
		if (number < 10) {
			if (prev == '/') {
				return 'M';
			}
			else if (prev == '\\') {
				return 'V';
			}
		}

		if (number % 10 > ((number / 10) % 10)) {
			if (prev == '/') {
				break;
			}
			prev = '/';
		}
		else if (number % 10 < ((number / 10) % 10)) {
			if (prev == '\\') {
				break;
			}
			prev = '\\';
		}
		else if (number % 10 == ((number / 10) % 10)) {
			break;
		}
	}
	return 'N';
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt

	int mountains = 0;
	int valleys = 0;
	for (int i = a; i <= b; i++) {
		if(classify_mv_range_type(i) == 'M') {
			mountains++;
		}
		else if(classify_mv_range_type(i) == 'V') {
			valleys++;
		}
	}
	cout << "There are " << mountains << " mountain ranges and " << valleys << " valley ranges between " << a << " and " << b << "." << endl;
}