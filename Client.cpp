#include "Client.h"


Client::Client(ifstream & in){

	string line, stringDate, garbage;

	getline(in, line);

	stringstream iss(line);

	iss >> id;
	getline(iss, garbage, ';');
	getline(iss >> ws, name, ';');
	name.pop_back();
	getline(iss >> ws, stringDate, ';');
	stringDate.pop_back();
	inscriptionDate = Date(stringDate);
	iss >> spentAmount;

}

Client::Client(int id, string name, Date inscriptionDate, float spentAmount) {
	this->id = id;
	this->name = name;
	this->inscriptionDate = inscriptionDate;
	this->spentAmount = spentAmount;
}

string Client::getName() const{
  return name;
}

void Client::setName(string newName){

	this->name = newName;
}

unsigned int Client::getId() const{
  return id;
}

Date Client::getInscriptionDate() const
{
	return inscriptionDate;
}

float Client::getSpentAmount() const{
  return spentAmount;
}

void Client::setSpentAmount(float n){

	spentAmount += n;
}

void Client::save(ofstream &out){
	
	string line;

	stringstream ss;

		ss << id << " ; " << name << " ; " << inscriptionDate << " ; " << spentAmount;

		line = ss.str();

		out << line;
}

ostream& operator<<(ostream& out, const Client & client){

	out << " *** Client ID. " << client.id << " ***" << endl;
	out << " Name: " << client.name << endl;
	out << " Inscription Date: " << client.inscriptionDate << endl;
	out << " Spent amount: " << client.spentAmount << endl << endl;

	return out;
}


bool operator<(const Client &client1, const Client &client2){
	
	return (client1.name < client2.name);
}

bool operator==(const Client & client, string name){

	return (client.name == name);
}

bool operator==(const Client & client, int id){

	return (client.id == id);
}

bool operator==(const Client & client1, const Client & client2) {

	return (client1.getId() == client2.getId());
}