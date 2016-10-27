#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Product {
	/* DATA MEMBERS */
 private:
	int id;
	string name;
	float price;
	
 public:
	Product(ifstream & in);
	Product(int id, string name, float price);
	int getId() const;
	string getName() const;
	void setName(string name);
	float getPrice() const;
	void setPrice(float price);
	void save(ofstream & out);
	friend ostream& operator<<(ostream& out, const Product & prod); // mostra um produto
	friend bool operator<(const Product &product1, const Product &product2); // compara dois produtos (1 produto e mais pequeno que outro se o seu nome for "alfabeticamente inferior"
	friend bool operator==(const Product &product, string name);
	friend bool operator==(const Product &product, int id);
};

#endif