#include "Header.h"

int main() {
	Properties p("data.csv");
	cout << "\n\n\n";
	p.commonPropertyAgeRangeVSCityDemographic();
	cout << "\n\n\n";
	p.commonPropertyAgeRangewith3bedn4bath();
	cout << "\n\n\n";
	p.mostCommonPropertyAgeRangeVSCityDemographic();
	cout << "\n\n\n";
	p.swimmingPoolAmenitiesComparision();
	cout << "\n\n\n";
	p.twoBedtwoBathVSthreeBedTwoBath();
	cout << "\n\n\n";
	p.typeCamparision();
	cout << "\n\n\n";
	p.conditionCamparision();
	return 0;
}