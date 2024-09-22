# include <string>
# include "Node.h"

using std::string;

Node::Node() : data(TemperatureData()), next(nullptr) {

}

Node::Node(string id, int year, int month, double temperature) : data(TemperatureData(id, year, month, temperature)) , next(nullptr) {
	
}

bool Node::operator<(const Node& b) {	
	return data < b.data;
}
