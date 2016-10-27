#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <utility>

#include "defs.h"

using namespace std;


void clearScreen();

unsigned short int readUnsignedShortInt(unsigned short int min, unsigned short int max);

int readInteger(int min, int max);

bool fileExists(string filename);

bool is_number(const string & s);

void verifyCorrectId(int &id, string type);

void verifyCorrectPrice(float & price, string type);

void verifyIdExists(int &id, string type, string operation);

void verifyNameExists(string &name, string type);

void verifyStringIsNotEmptyAndNotANumber(string &name, string type);

multimap<int, int> flip_map(const map<int, int> &src);

#endif