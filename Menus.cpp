#include "Menus.h"

bool readInitialInformation(string & storeName, string & clientsFilename, string & productsFilename, string & transactionsFilename){
	/*storeName = "abc";
	clientsFilename = "clients.txt";
	productsFilename = "products.txt";
	transactionsFilename = "transactions.txt";
	return true;
	*/
	bool validClientsFilename = false;
	bool validProductsFilename = false;
	bool validTransactionsFilename = false;

	cout << " Please enter the store name: ";
	cin >> storeName;

	cout << " Please enter the clients filename: ";

	do {

		cin >> clientsFilename;

		if (fileExists(clientsFilename))

			validClientsFilename = true;

		else

			cout << " File doesn't exists." << endl << " Please enter a valid clients filename: ";

	} while (!fileExists(clientsFilename));

	cout << " Please enter the products filename: ";

	do {

		cin >> productsFilename;

		if (fileExists(productsFilename))

			validProductsFilename = true;

		else

			cout << " File doesn't exists." << endl << " Please enter a valid products filename: ";

	} while (!fileExists(productsFilename));
	
	cout << " Please enter the transactions filename: ";

	do {

		cin >> transactionsFilename;

		if (fileExists(transactionsFilename)) {

			validTransactionsFilename = true;

		}

		else

			cout << " File doesn't exists." << endl << " Please enter a valid transactions filename: ";

	} while (!fileExists(transactionsFilename));
	
	cout << endl << " Files loaded correctly!";
	Sleep(2000);

	clearScreen();

	if (validClientsFilename&&validProductsFilename&&validTransactionsFilename)
		return true;
	else
		return false;
}

/******************************************
 * CLIENTS MANAGER
 ******************************************/
unsigned short int clientsManagerMenu(){
  unsigned short int option;

  clearScreen();

  cout << endl;
  cout << TAB_BIG << TAB_BIG << TAB << TAB << "======================== CLIENTS MANAGER ========================" << endl;
  cout << endl;
  cout << TAB << "1 - Create client" << endl;
  cout << TAB << "2 - Modify client" << endl;
  cout << TAB << "3 - Remove client" << endl;
  cout << TAB << "4 - Show clients database" << endl;
  cout << TAB << "5 - Show clients database by alfabetic order" << endl;
  cout << TAB << "6 - Search client by ID" << endl;
  cout << TAB << "7 - Search client by Name" << endl;
  cout << TAB << "8 - Show Bottom clients" << endl;
  cout << TAB << "9 - Back to main menu" << endl << endl;
  cout << TAB << "Please choose an option> ";
  option = readUnsignedShortInt(1, 9);

  if(option == 9)
    return 0;

  return option;
}


void clientsManagerOptions(Supermarket & supermarket){
  unsigned int option;
  string name;

  while((option = clientsManagerMenu()))
	  switch (option) {
	  case 1:
		  clearScreen();
		  supermarket.createClient();
		  break;
	  case 2:
		  clearScreen();
		  supermarket.modifyClient();
		  break;
	  case 3:
		  clearScreen();
		  supermarket.removeClient();
		  break;
	  case 4:
		  clearScreen();
		  supermarket.showClientsDatabaseCab();
		  supermarket.showClients();
		  cin.get();
		  break;
	  case 5:
		  clearScreen();
		  supermarket.showClientByOrder();
		  cin.get();
		  break;
	  case 6:
		  clearScreen();
		  supermarket.searchClientByID();
		  break;
	  case 7:
		  clearScreen();
		  supermarket.searchClientByName();
		  break;
	  case 8:
		  clearScreen();
		  supermarket.runClientsBottom("see");
		  cin.get();
		  break;
	  }
}

/******************************************
* PRODUCTS MANAGER
******************************************/

unsigned short int productsManagerMenu() {
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "======================== PRODUCT MANAGER ========================" << endl;
	cout << endl;
	cout << TAB << "1 - Create product" << endl;
	cout << TAB << "2 - Modify product" << endl;
	cout << TAB << "3 - Remove product" << endl;
	cout << TAB << "4 - Show product database" << endl;
	cout << TAB << "5 - Show product database by alfabetic order" << endl;
	cout << TAB << "6 - Search product by ID" << endl;
	cout << TAB << "7 - Search product by Name" << endl;
	cout << TAB << "8 - Back to main menu" << endl << endl;
	cout << TAB << "Please choose an option> ";

	option = readUnsignedShortInt(1, 8);

	if (option == 8)
		return 0;

	return option;
}


void productsManagerOptions(Supermarket & supermarket) {

	unsigned int option;
	string name;

	while ((option = productsManagerMenu()))
		switch (option) {
		case 1: 
			clearScreen();
			supermarket.createProduct();
			break;
		case 2: 
			clearScreen();
			supermarket.modifyProduct();
			break;
		case 3:
			clearScreen();
			supermarket.removeProduct();
			break;
		case 4:
			clearScreen();
			supermarket.showProducts();
			cin.get();
			break;
		case 5:
			clearScreen();
			supermarket.showProductsByOrder();
			cin.get();
			break;
		case 6:
			clearScreen();
			supermarket.searchProductByID();
			break;
		case 7:
			clearScreen();
			supermarket.searchProductByName();
			break;
		}
}

/******************************************
 * TRANSACTIONS MANAGER
 ******************************************/
unsigned short int transactionsManagerMenu(){
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "======================== TRANSACTION MANAGER ========================" << endl;
	cout << endl;
	cout << TAB << "1 - Create transaction" << endl;
	cout << TAB << "2 - Show transaction database" << endl;
	cout << TAB << "3 - Search transaction by ID" << endl;
	cout << TAB << "4 - Search transaction by Client" << endl;
	cout << TAB << "5 - Search transaction by day" << endl;
	cout << TAB << "6 - Search transactions between 2 dates" << endl;
	cout << TAB << "7 - Back to main menu" << endl << endl;
	cout << TAB << "Please choose an option> ";

	option = readUnsignedShortInt(1, 7);

	if (option == 7)
		return 0;

	return option;
}

void transactionsManagerOptions(Supermarket & supermarket){
  unsigned int option;

  while((option = transactionsManagerMenu()))
    switch (option){
    case 1:
		clearScreen();
		supermarket.createTransaction();
      break;
    case 2:
		clearScreen();
		supermarket.showAllTransactions();
      break;
    case 3:
		clearScreen();
		supermarket.searchTransactionsByID();
      break;
    case 4:
		clearScreen();
		supermarket.searchTransactionsByClientName();
      break;
	case 5:
		clearScreen();
		supermarket.searchTransactionsByDate();
		break;
	case 6:
		clearScreen();
		supermarket.searchTransactionsBetweenDates();
		break;
    }
}

/******************************************
 * RECOMMENDATION MANAGER
 ******************************************/
unsigned short int recomendatioMenu(){
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB <<  "======================== RECOMMENDATION SYSTEM ========================" << endl;
	cout << endl;
	cout << TAB << "1 - Select a client" << endl;
	cout << TAB << "2 - Use recommendation system with bottom clients" << endl;
	cout << TAB << "3 - Back to main menu" << endl << endl;
	cout << TAB << "Please choose an option> ";

	option = readUnsignedShortInt(1, 3);

	if (option == 3)
		return 0;

	return option;

}

void recomendationOptions(Supermarket & supermarket){
  unsigned int option;

  while((option = recomendatioMenu()))
    switch (option){
    case 1:
		clearScreen();
		supermarket.showRecommendationSystem();
		cin.get();
      break;
    case 2:
		clearScreen();
		supermarket.showRecommendationSystemBottom();
		cin.get();
      break;
    case 3:
      break;
    case 4:
      break;
    }

}

/******************************************
 * MAIN MENU
 ******************************************/
unsigned short int mainMenu(){
  unsigned short int option;

  clearScreen();
  cout << endl;
  cout << TAB_BIG << TAB_BIG << TAB_BIG << "======================== MAIN MENU ========================";
  cout << endl << endl;
  cout << TAB << "1 - Clients Manager" << endl;
  cout << TAB << "2 - Products Manager" << endl;
  cout << TAB << "3 - Transactions Manager" << endl;
  cout << TAB << "4 - Recommendation System" << endl;
  cout << TAB << "5 - Exit" << endl << endl;
  cout << TAB << "Please choose an option> ";
  option = readUnsignedShortInt(1, 5);

  if(option == 5)
    return 0;

  return option;
}

void mainMenuOptions(Supermarket & supermarket){
  unsigned int option;


  while((option = mainMenu()))
    switch (option){
    case 1: clientsManagerOptions(supermarket);
      break;
	case 2: productsManagerOptions(supermarket);
      break;
    case 3: transactionsManagerOptions(supermarket);
      break;
    case 4: recomendationOptions(supermarket);
      break;
    }

  supermarket.saveChanges();
}

void showWelcome() {

	cout << endl << TAB_BIG << TAB_BIG << TAB << "_______________________________________________________________";
	cout << endl << endl;
	cout << TAB_BIG << TAB_BIG << TAB_BIG << TAB_BIG << "  WELCOME TO SUPERMARKET ++";
	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << "_______________________________________________________________";
	cout << endl << endl << endl;

}