#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

#include "defs.h"
#include "utils.h"
#include "Supermarket.h"

using namespace std;

bool readInitialInformation(string & storeName, string & clientsFilename, string & productsFilename, string & transactionsFilename);

void mainMenuOptions(Supermarket & supermarket);

void clientsManagerOptions(Supermarket & supermarket);

void productsManagerOptions(Supermarket & supermarket);

void transactionsManagerOptions(Supermarket & supermarket);

void recommendationOptions(Supermarket & supermarket);

void showWelcome();

#endif