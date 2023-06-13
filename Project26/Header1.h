#pragma once
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
                if (temp[i] != '[' && temp[i] != ']' && temp[i] != '\'' && temp[i] != '\"') {
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
        properties = new Property[count - 1];
        ifstream inputFile1(fileName);
        getline(inputFile1, line);
        for (int i = 0; getline(inputFile1, line); i++) {
            properties[i].writeData(line);
        }
        inputFile1.close();
        cout << "Data Records Readed Successfully...\n";
    }

    Property& getProperty(int index) { return properties[index]; }

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
        cout << "Properties with Good Condition: " << goodCount << "\t having aveage price of: " << float(good) / float(goodCount) << endl;
        cout << "Properties with Fair Condition: " << fairCount << "\t having aveage price of: " << float(fair) / float(fairCount) << endl;
        cout << "Properties with Poor Condition: " << poorCount << "\t having aveage price of: " << float(poor) / float(poorCount) << endl;
    }
};