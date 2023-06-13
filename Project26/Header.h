#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct Property {
public:
    string area;
    string property_type;
    string property_age;
    string property_age_range;
    string property_condition;
    string city;
    string city_demographic;
    int bedroom_count;
    int bathroom_count;
    long price;
    string availability_fluctuation;
    string market_trend;
    string* amenities_list;
    int amenities_list_length;
public:

    Property() {
        area = "";
        property_type = "";
        property_age = "";
        property_age_range = "";
        property_condition = "";
        city = "";
        city_demographic = "";
        bedroom_count = 0;
        bathroom_count = 0;
        price = 0;
        availability_fluctuation = "";
        market_trend = "";
        amenities_list = NULL;
        amenities_list_length = 0;
    }

    void writeData(string line) {
        stringstream lineStream(line);
        string temp;
        getline(lineStream, area, ',');
        getline(lineStream, property_type, ',');
        getline(lineStream, property_age, ',');
        getline(lineStream, property_age_range, ',');
        getline(lineStream, property_condition, ',');
        getline(lineStream, city, ',');
        getline(lineStream, city_demographic, ',');
        getline(lineStream, temp, ',');
        bedroom_count = stoi(temp);
        getline(lineStream, temp, ',');
        bathroom_count = stoi(temp);
        getline(lineStream, temp, ',');
        price = stoi(temp);
        getline(lineStream, availability_fluctuation, ',');
        getline(lineStream, market_trend, ',');
        int count = 0;
        string array[50];
        while (getline(lineStream, temp, ',')) {
            array[count] = "";
            for (int i = 0; i < temp.length(); i++) {
                if (temp[i] != '[' && temp[i] != ']' && temp[i] != '\'' && temp[i]!='\"') {
                    array[count] += temp[i];
                }
            }
            count++;
        }
        amenities_list_length = count;
        amenities_list = new string[count];
        for (int i = 0; i < count; i++) {
            amenities_list[i] = array[i];
        }
    }

    void print() {
        cout << "\nArea: " << area <<
            "\nProperty Type: " << property_type <<
            "\nProperty Age: " << property_age <<
            "\nProperty Age Range: " << property_age_range <<
            "\nProperty Condition: " << property_condition <<
            "\nCity: " << city <<
            "\nCity Demographic: " << city_demographic <<
            "\nBedroom Count: " << bedroom_count <<
            "\nBathroom Count: " << bathroom_count <<
            "\nPrice: " << price <<
            "\nAvailability: " << availability_fluctuation <<
            "\nMarket Trend: " << market_trend <<
            "\nAmenities List:\n";
        for (int i = 0; i < amenities_list_length; i++) {
            cout << "\t-  " << amenities_list[i] << endl;
        }
    }

    bool findAminity(string amenityName) {
        for (int i = 0; i < amenities_list_length; i++) {
            if (amenities_list[i] == amenityName) {
                return true;
            }
        }
        return false;
    }
};


struct Properties {
private:
    Property* properties;
    int totalProperties;
public:
    Properties() {
        properties = NULL;
        totalProperties = 0;
    }
    Properties(string fileName) {

        ifstream inputFile(fileName);
        if (!inputFile.is_open()) {
            cout << "Failed to open file!" << endl;
            return;
        }
        cout << "Finding Total Records ...\n";
        string line;
        int count = 0;
        while (getline(inputFile, line)) {
            count++;
        }
        inputFile.close();
        totalProperties = count;
        cout << "Total Entries Count: " << count << endl;
        cout << "Fetching Records...\n";
        properties = new Property[count-1];
        ifstream inputFile1(fileName);
        getline(inputFile1, line);
        for (int i = 0; getline(inputFile1, line); i++) {
            properties[i].writeData(line);
        }
        inputFile1.close();
        cout << "Data Records Readed Successfully...\n";
    }

    Property& getProperty(int index) { return properties[index]; }


    void swimmingPoolAmenitiesComparision() {  // in terms of price
        long long swimming = 0;
        long long non_swimming = 0;
        int swimmingCount = 0;
        int nonSwimmingCount = 0;
        for (int i = 0; i < totalProperties; i++) {
            if (properties[i].findAminity("Swimming Pool")) {
                swimming += properties[i].price;
                swimmingCount++;
            }
            else {
                non_swimming += properties[i].price;
                nonSwimmingCount++;
            }
        }
        
        cout << "  Comparision of properties with and without Swimming Pool aminity in terms of price\n";
        cout << "--------------------------------------------------------------------------------------\n";
        cout << "Properties with Swimming Pool Aminity: " << swimmingCount << endl;
        cout << "Properties without Swimming Pool Aminity: " << nonSwimmingCount << endl;
        cout << "Average Price of Properties with Swimming Pool Aminity: " << float(swimming)/float(swimmingCount) << endl;
        cout << "Average price of Properties without Swimming Pool Aminity: " << float(non_swimming)/float(nonSwimmingCount) << endl;
    }


    void conditionCamparision() {
        int goodCount = 0, fairCount = 0, poorCount = 0;
        long long good = 0, fair = 0, poor = 0;
        for (int i = 0; i < totalProperties; i++) {
            if (properties[i].property_condition == "Good") {
                good += properties[i].price;
                goodCount++;
            }
            else if (properties[i].property_condition == "Poor") {
                poor += properties[i].price;
                poorCount++;
            }
            else if (properties[i].property_condition == "Fair") {
                fair += properties[i].price;
                fairCount++;
            }
        }
        cout << "\n\n  Comparision of Good, Fair and Poor properties in terms of price\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "Properties with Good Condition: " << goodCount << "\t having aveage price of: " << float(good)/float( goodCount) << endl;
        cout << "Properties with Fair Condition: " << fairCount << "\t having aveage price of: " << float(fair)/float( fairCount) << endl;
        cout << "Properties with Poor Condition: " << poorCount << "\t having aveage price of: " << float(poor)/float( poorCount) << endl;
    }

    void typeCamparision() {
        int apartmentCount = 0, townhouseCount = 0, houseCount = 0;
        long long apartment = 0, townhouse = 0, house = 0;
        for (int i = 0; i < totalProperties; i++) {
            if (properties[i].property_type == "House") {
                house += properties[i].price;
                houseCount++;
            }
            else if (properties[i].property_condition == "Townhouse") {
                townhouse += properties[i].price;
                townhouseCount++;
            }
            else if (properties[i].property_condition == "Apartment") {
                apartment += properties[i].price;
                apartmentCount++;
            }
        }
        cout << "\n\n      Comparision of types of  properties in terms of price\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "Properties of type House: " << houseCount << "\t having aveage price of: " << float(house)/float( houseCount) << endl;
        cout << "Properties of type Townhouse: " << townhouseCount << "\t having aveage price of: " << float(townhouse)/float( townhouseCount) << endl;
        cout << "Properties of type Apartment: " << apartmentCount << "\t having aveage price of: " <<float(apartment)/float( apartmentCount) << endl;
    }



    void commonPropertyAgeRangewith3bedn4bath() {
        int lessThanFive = 0, fiveToTen = 0, tenToTwenty = 0, twentyPlus = 0;
        for (int i = 0; i < totalProperties; i++) {
            if (properties[i].bathroom_count == 4 && properties[i].bedroom_count == 3) {
                if (properties[i].property_age_range == "Less than 5 years old") {
                    lessThanFive++;
                }
                else if (properties[i].property_age_range == "5-10 years old") {
                    fiveToTen++;
                }
                else if (properties[i].property_age_range == "10-20 years old") {
                    tenToTwenty++;
                }
                else {
                    twentyPlus++;
                }
            }
        }
        cout << "\n\n         Common Property Age Range with 3 bed and 4 Bath\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "Properties Having Less than Five years Age Range: " << lessThanFive << endl;
        cout << "Properties Having Five To Ten years Age Range: " << fiveToTen << endl;
        cout << "Properties Having Ten to Twenty years Age Range: " << tenToTwenty << endl;
        cout << "Properties Having More than Twenty years Age Range: " << twentyPlus << endl;
        cout << "\n So, the most common property age range is the property with max Counnt\n";
    }

    void twoBedtwoBathVSthreeBedTwoBath() {
        int twoBedTwoBathCount = 0, threeBedtwoBathCount = 0;
        long long twoBedTwoBath = 0, threeBedtwoBath = 0;
        for (int i = 0; i < totalProperties; i++) {
            if (properties[i].bathroom_count == 2 && properties[i].bedroom_count == 2) {
                twoBedTwoBath += properties[i].price;
                twoBedTwoBathCount++;
            }
            else if (properties[i].bathroom_count == 2 && properties[i].bedroom_count == 3) {
                threeBedtwoBath += properties[i].price;
                threeBedtwoBathCount++;
            }
            
        }
        cout << "\n\n      Comparision of types of  properties in terms of price\n";
        cout << "-----------------------------------------------------------------------\n";
        cout << "Properties having 2 Bed & 2 Bath: " << twoBedTwoBathCount << "\t having aveage price of: " << float(twoBedTwoBath)/float( twoBedTwoBathCount) << endl;
        cout << "Properties having 3 Bed & 2 Bath:" << threeBedtwoBathCount << "\t having aveage price of: " << float(threeBedtwoBath)/float( threeBedtwoBathCount) << endl;
        float temp = (float(twoBedTwoBath) / float(twoBedTwoBathCount)) - (float(threeBedtwoBath) / float(threeBedtwoBathCount));
        temp < 0 ? temp*=(-1) : temp;
        cout << "The difference between both Types in terms of price is: " << temp;
    }


    void mostCommonPropertyAgeRangeVSCityDemographic() {
        string demographs[5][2] = { {"Families With Children", ""},{"Ethnic Enclaves", ""}, {"Young Professionals", ""}, {"Students", ""}, {"Retirees", ""} };
        int lessThanFive = 0, fiveToTen = 0, tenToTwenty = 0, twentyPlus = 0;
        for (int j = 0; j < 5; j++) {
            lessThanFive = 0, fiveToTen = 0, tenToTwenty = 0, twentyPlus = 0; 
            for (int i = 0; i < totalProperties; i++) {
                if (properties[i].city_demographic == demographs[j][0]) {
                    if (properties[i].property_age_range == "Less than 5 years old") {
                        lessThanFive++;
                    }
                    else if (properties[i].property_age_range == "5-10 years old") {
                        fiveToTen++;
                    }
                    else if (properties[i].property_age_range == "10-20 years old") {
                        tenToTwenty++;
                    }
                    else {
                        twentyPlus++;
                    }
                }
            }
            int maximun = max(max(max(lessThanFive, fiveToTen), tenToTwenty),twentyPlus);
            if (maximun == lessThanFive) { demographs[j][1] = "Less than 5 years old"; }
            else if (maximun == fiveToTen) { demographs[j][1] = "5-10 years old"; }
            else if (maximun == tenToTwenty) { demographs[j][1] = "10-20 years old"; }
            else { demographs[j][1] = "20+ years old"; }
        }

        cout << "\n\n   Common Property Age Range with respect to City Demgraphics\n";
        cout << "-----------------------------------------------------------------------\n";
        for (int i = 0; i < 5; i++) {
            cout << demographs[i][0] << " : " << demographs[i][1] << endl;
        }
    }

    void commonPropertyAgeRangeVSCityDemographic() {
        string demographs[5][2] = { {"Families With Children", ""},{"Ethnic Enclaves", ""}, {"Young Professionals", ""}, {"Students", ""}, {"Retirees", ""} };
        int lessThanFive = 0, fiveToTen = 0, tenToTwenty = 0, twentyPlus = 0;
        for (int j = 0; j < 5; j++) {
            lessThanFive = 0, fiveToTen = 0, tenToTwenty = 0, twentyPlus = 0;
            for (int i = 0; i < totalProperties; i++) {
                if (properties[i].city_demographic == demographs[j][0]) {
                    if (properties[i].property_age_range == "Less than 5 years old") {
                        lessThanFive++;
                    }
                    else if (properties[i].property_age_range == "5-10 years old") {
                        fiveToTen++;
                    }
                    else if (properties[i].property_age_range == "10-20 years old") {
                        tenToTwenty++;
                    }
                    else {
                        twentyPlus++;
                    }
                }
            }
            int maximun = max(max(max(lessThanFive, fiveToTen), tenToTwenty), twentyPlus);
            if (maximun == lessThanFive) { demographs[j][1] = "Less than 5 years old"; }
            else if (maximun == fiveToTen) { demographs[j][1] = "5-10 years old"; }
            else if (maximun == tenToTwenty) { demographs[j][1] = "10-20 years old"; }
            else { demographs[j][1] = "20+ years old"; }
        }

        cout << "\n\n   Common Property Age Range with respect to City Demgraphics\n";
        cout << "-----------------------------------------------------------------------\n";
        for (int i = 0; i < 5; i++) {
            cout << demographs[i][0] << " : " << demographs[i][1] << endl;
        }
    }

};