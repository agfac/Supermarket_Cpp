#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>
#include <ctime>

using namespace std;

class Date {
	/* DATA MEMBERS */
 private:
	int day;
	int month;
	int year;

 public:
	Date();
	Date(string date); // data na forma DD/MM/AAA
	Date(int day, int month, int year);
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);
	void save(ofstream & out) const;
	bool operator==(const Date & date);
	bool operator<(const Date & date);
	bool operator<=(const Date & date);
	bool operator>=(const Date & date);
	friend ostream& operator<<(ostream& out, const Date & data);
};

#endif