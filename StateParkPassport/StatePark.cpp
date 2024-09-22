# include "Passport.h"

using std::string, std::vector;

StatePark::StatePark(string parkName, double entranceFee, double trailMiles) : parkName(parkName), entranceFee(entranceFee), trailMiles(trailMiles), camperLog({}) {}


string StatePark::getParkName() {
	return parkName;
}

double StatePark::getEntranceFee() {
	return entranceFee;
}

double StatePark::getTrailMiles() {	
	return trailMiles;
}

void StatePark::addCamper(Passport* camper) {
	INFO(camper)
	camperLog.push_back(camper);
}

double StatePark::getRevenue() {
	// TODO: (optional) implement function

	return 0.0;
}
