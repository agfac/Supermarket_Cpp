#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <fstream>
#include <string>

#include "Date.h"

using namespace std;

class Client {
	/* DATA MEMBERS */
 private:
	unsigned int id;
	string name;
	Date inscriptionDate;
	float spentAmount;

 public:
	Client() { };
	Client(ifstream & in);
	Client(int id, string name, Date inscriptionDate, float spentAmount);
	string getName() const;
	void setName(string newName);
	unsigned int getId() const;
	Date getInscriptionDate() const;
	float getSpentAmount() const;
	void setSpentAmount(float n);
	void save(ofstream & out);
	friend ostream& operator<<(ostream& out, const Client & client);  // mostra informacao do cliente no ecra
	friend bool operator<(const Client &client1, const Client &client2); // compara 2 clientes (1 cliente e menor que outro se o seu nome for "alfabeticamente" inferior)
	friend bool operator==(const Client &client, string name);
	friend bool operator==(const Client &client, int id);
	friend bool operator==(const Client & client1, const Client & client2);
};

#endif