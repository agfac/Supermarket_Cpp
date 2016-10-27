#include "Product.h"


Product::Product(ifstream & in){ // nome ; custo

	string line, garbage;
	
	getline(in, line);

	stringstream iss(line);

	iss >> id;
	getline(iss, garbage, ';');
	getline(iss >> ws, name, ';');
	name.pop_back();
	iss >> price;

}

Product::Product(int id, string name, float price) {
	this->id = id;
	this->name = name;
	this->price = price;
}

int Product::getId() const{

	return id;
}

string Product::getName() const {
	
	return name;
}

void Product::setName(string name){
	
	this->name = name;
}

float Product::getPrice() const {

	return price;

}

void Product::setPrice(float price){
	
	this->price = price;
}

void Product::save(ofstream &out) {
	
	string line;

	stringstream ss;

	ss << id << " ; " << name << " ; " << price;

	line = ss.str();

	out << line;

}

ostream& operator<<(ostream& out, const Product & prod){

	out << " *** PRODUCT " << prod.id << " ***" << endl;
	out << " Name: " << prod.name << endl;
	out << " Price: " << prod.price << endl << endl;

	return out;
}


bool operator<(const Product &product1, const Product &product2){
	
	return (product1.name < product2.name);
}

bool operator==(const Product & product, string name){

	return (product.name == name);
}

bool operator==(const Product & product, int id){

	return (product.id == id);
}
