#include "Transaction.h"

Transaction::Transaction(unsigned int id, unsigned int idClient, Date date, vector<string> products){
	this->id = id;
	this->idClient = idClient;
	this->date = date;
	this->products = products;
}

unsigned int Transaction::getId() const {
	return id;
}

unsigned int Transaction::getIdClient() const{
	return idClient;
}

Date Transaction::getDate() const
{
	return date;
}

vector<string> Transaction::getProducts() const{
	return products;
}

void Transaction::addProduct(string product){
	products.push_back(product);
}

Transaction::Transaction(ifstream & in){ // le uma transacao na forma de  idcliente ; data ; lista produtos
	
	string productName, line, stringDate;

	string garbage; // A string that will extract the semicolons and any leading spaces.
	char trash;

	getline(in, line);

	stringstream iss(line);

	iss >> id >> garbage >> idClient >> garbage;
	getline(iss >> ws, stringDate, ';');
	stringDate.pop_back();
	date = Date(stringDate);

	while (getline(iss >> ws, productName, ','))

		products.push_back(productName);

}

void Transaction::save(ofstream &out){ // transacao guardada como na forma de  idcliente ; data ; lista produtos

	string line;

	stringstream ss;

	ss << id << " ; " << idClient << " ; " << date << " ; ";

		for (auto& p : products) {
			if (p != products.back())
				ss << p << ", ";
			else
				ss << p;
			}

	line = ss.str();

	out << line;
}

ostream& operator<<(ostream& out, const Transaction & transaction){

	out << endl;
	out << setw(60) << "***** Transaction ID. " << transaction.getId() << " *****" << endl << endl;
	out << " _____________________________" << endl << endl;
	out << setw(12) << "CLIENT ID. " << transaction.getIdClient() << endl;	
	out << setw(7) << " DATE: ";
	out << transaction.getDate();
	out << endl << " _____________________________" << endl;
	out << endl << endl;

	for (int i = 0; i < transaction.getProducts().size(); i++) {

		cout << " *** PRODUCT " << i+1 << " ***" << endl;
		cout << " Name: " << transaction.getProducts().at(i) << endl;
	}
  
	return out;
}