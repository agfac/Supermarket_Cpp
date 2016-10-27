#include "Date.h"

Date::Date() {

	time_t rawtime;
	struct tm timeinfo;  

	time(&rawtime);

	localtime_s(&timeinfo, &rawtime); 

	this->day = timeinfo.tm_mday;
	this->month = timeinfo.tm_mon+1;
	this->year = timeinfo.tm_year+1900;

}

Date::Date(string dateStr){ // data na forma DD/MM/AAA
	int day, month, year;
	char trash;

	stringstream iss(dateStr);

	iss >> day >> trash >> month >> trash >> year;

	if ((iss.fail()) || (day < 1 || day>31 || month < 1 || month>12 || year < 0 || trash != '/')) {
		cout << " You entered a not valid date!" << endl;
	}

	else {
		this->day = day;
		this->month = month;
		this->year = year;
	}
}

Date::Date(int day, int month, int year) {
	if (day < 1 || day>31 || month < 1 || month>12 || year < 0) {
		cout << " You entered a not valid date!" << endl;
	}

	else {
		this->day = day;
		this->month = month;
		this->year = year;
	}
}


int Date::getDay() const{
  return day;
}

int Date::getMonth() const{
  return month;
}

int Date::getYear() const{
  return year;
}

void Date::setDay(int day){
	this->day = day;
}

void Date::setMonth(int month){
	this->month = month;
}

void Date::setYear(int year){
	this->year = year;
}

void Date::save(ofstream & out) const{

	out << day << "/" << month << "/" << year;
}

bool Date::operator==(const Date & date) {

	return (this->day == date.day && this->month == date.month && this->year == date.year);

}

bool Date::operator<(const Date & date) {

	return (!(operator>=(date)));
}

bool Date::operator<=(const Date & date) {

	if (this->year < date.year)
		return true;
	else if (this->year == date.year)
	{
		if (this->month < date.month)
			return true;
		else if (this->day <= date.day)
			return true;
		else
			return false;
	}
	return false;
}

bool Date::operator>=(const Date & date) {

	if (this->year > date.year)
		return true;
	else if (this->year == date.year)
	{
		if (this->month > date.month)
			return true;
		else if (this->day >= date.day)
			return true;
		else
			return false;
	}
	return false;

}

ostream& operator<<(ostream& out, const Date & date){
	out << date.day << "/" << date.month << "/" << date.year;
	return out;
}

istream& operator>>(istream& in, Date & date) {
	
	int day, month, year;
	char slash;
	string stringDate;

	getline(in, stringDate);

	istringstream iss(stringDate);

	iss >> day >> slash >> month >> slash >> year;

	assert(slash == '/');
	assert(day >= 1 || day <= 31); 
	assert(month >= 1 || month <= 12); 
	assert(year > 0);
	
	date = Date(day, month, year);

	return in;
}