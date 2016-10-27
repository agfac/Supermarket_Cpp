#ifndef TRANSACTON_H
#define TRANSACTON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

#include "Date.h"
#include "Product.h"

using namespace std;

class Transaction {
	/* DATA MEMBERS */
 private:
	unsigned int id;
	unsigned int idClient;
	Date date; // na forma DD/MM/AAAAA
	vector<string> products;

 public:
	Transaction(ifstream & in); // transacao na forma de  idCliente ; data ; lista de produtos
	Transaction(unsigned int id, unsigned int idClient, Date date, vector<string> products);
	unsigned int getId() const;
	unsigned int getIdClient() const;
	Date getDate() const;
	vector<string> getProducts() const;
	void addProduct(string product);
	void save(ofstream & out); // guarda a transacao
	friend ostream& operator<<(ostream& out, const Transaction & transaction); // mostra a transacao
};

#endif