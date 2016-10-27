#include "Supermarket.h"

//SUPERMARKET CONSTRUCTOR

Supermarket::Supermarket(string storeName, string clientsFilename, string productsFilename, string transactionsFilename){

	this->storeName = storeName;
	this->clientsFilename = clientsFilename;
	this->productsFilename = productsFilename;
	this->transactionsFilename = transactionsFilename;

	loadClients();
	loadProducts();
	loadTransactions();
}

/*********************************
* CLIENTS MANAGER
********************************/

//LOAD CLIENTS FILE

void Supermarket::loadClients() {

	maxClientsId = 0;

	int i = 0;
	string numClients;

	ifstream inputFile;
	inputFile.open(clientsFilename);

	if (inputFile.fail()) {

		cerr << " Error opening clients file";
		exit(1);
	}
	else
	{
		getline(inputFile, numClients);

		while (!inputFile.eof())
		{
			Client client(inputFile);

			clients.push_back(client);

			clientIdx.insert(std::pair<string, int>(client.getName(), i));

			i++;

			if (client.getId() > maxClientsId)
				maxClientsId = client.getId();
		}
		inputFile.close();
	}
}

//SHOW CLIENTS DATABASE HEADER

void Supermarket::showClientsDatabaseCab(){

		cout << endl << " ***********************" << endl;
		cout << "    CLIENTS DATABASE" << endl;
		cout << " ***********************" << endl << endl;

}

//SHOW CLIENTS DATABASE

void Supermarket::showClients(){

		if (clients.empty()) 
			std::cout << " The clients database is empty!" << endl;
		else 
			for (const auto& c:clients) 
				cout << c;
}  

//CREATE CLIENT

void Supermarket::createClient() {
	
	int i = clients.size();
	unsigned int id = ++maxClientsId;
	string name;
	float spentAmount = 0;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "======================== NEW CLIENT ========================" << endl;
	cout << endl << endl;

	cout << " Please enter the client name> ";
	getline(cin, name);

	verifyStringIsNotEmptyAndNotANumber(name, "client");

	Date inscriptionDate = Date();

	Client client(id, name, inscriptionDate, spentAmount);
	clients.push_back(client);

	clientIdx.insert(std::pair<string, int>(name, ++i));

	clientesAlterados = true;

	cout << endl << " New client created sucessfully!" << endl << endl;

	cout << client;

	cin.get();
}

// MODIFY CLIENT

void Supermarket::modifyClient(){

	int id;
	string newName;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "======================= MODIFY CLIENT =====================" << endl << endl;

	if (clients.empty()) {
		cout << " There are no clients to modify!" << endl;
		cout << " The clients database is empty!" << endl;
		cin.get();
	}

	else {
		showClientsDatabaseCab();
		showClients();
		cout << endl << " Please enter the client ID to modify> ";
		cin >> id;
		cin.ignore(1000, '\n');

		verifyCorrectId(id, "client");

		while (getClient(id) == nullptr)
			verifyIdExists(id, "client", "modify");

		Client* clientPtr = getClient(id);

		cout << (*clientPtr);

		cout << endl << " Please enter the new client name> ";
		getline(cin, newName);

		verifyStringIsNotEmptyAndNotANumber(newName, "client");

		(*clientPtr).setName(newName);

		clientesAlterados = true;

		cout << endl << " Client name modified sucessfully!" << endl << endl;

		cout << (*clientPtr);

		cin.get();

		showClients();
	}
}

// REMOVE CLIENT

void Supermarket::removeClient(){

	int id;
	char ch;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "======================== REMOVE CLIENT =====================" << endl;
	cout << endl;

	if (clients.empty()) {
		cout << " There are no clients to remove!" << endl;
		cout << " The clients database is already empty!" << endl;
		cin.get();
	}

	else {
		showClientsDatabaseCab();
		showClients();
		cout << endl << " Please enter the client ID to remove> ";
		cin >> id;
		cin.ignore(1000, '\n');

		verifyCorrectId(id, "client");

		while (getClient(id) == nullptr) 
			verifyIdExists(id, "client", "remove");

		Client* clientPtr = getClient(id);

		int i = clientIdx[(*clientPtr).getName()];

		cout << (*clientPtr);

		cout << " Are you sure you want to remove that client? (y/n)> ";
		cin >> ch;
		cin.ignore(1000, '\n');

		if (toupper(ch) == 'Y') {
			clients.erase(clients.begin() + i);
			clientIdx.erase((*clientPtr).getName());
			cout << endl << " Client removed sucessfully!" << endl;
			cin.get();
		}

		showClientsDatabaseCab();
		showClients();

		clientesAlterados = true;

		cin.get();

	}
}

// SEARCH CLIENT BY ID

void Supermarket::searchClientByID(){

		int id;

		cout << endl;
		cout << TAB_BIG << TAB_BIG << TAB << TAB << "==================== SEARCH CLIENT BY ID ===================" << endl;
		cout << endl;

		if (clients.empty()) {
			cout << " There are no clients to remove!" << endl;
			cout << " The clients database is already empty!" << endl;
			cin.get();
		}

		else {

			cout << endl << " Please enter the client ID> ";

			cin >> id;
			cin.ignore(1000, '\n');

			verifyCorrectId(id, "client");

			while (getClient(id) == nullptr)
				verifyIdExists(id, "client", "");

			Client* clientPtr = getClient(id);

			cout << endl << " Client found!" << endl << endl;

			Sleep(1000);

			cout << (*clientPtr);

			cin.get();
		}
}

// SEARCH CLIENT BY NAME

void Supermarket::searchClientByName(){

		string name;

		cout << endl;
		cout << TAB_BIG << TAB_BIG << TAB << TAB << "==================== SEARCH CLIENT BY NAME ===================" << endl;
		cout << endl;

		if (clients.empty()) {
			cout << " There are no clients to remove!" << endl;
			cout << " The clients database is already empty!" << endl;
			cin.get();
		}

		else {

			cout << endl << " Please enter the client name> ";

			getline(cin, name);

			verifyStringIsNotEmptyAndNotANumber(name, "client");

			while (getClient(name) == nullptr)
				verifyNameExists(name, "client");

			Client* clientPtr = getClient(name);

			cout << endl << " Client found!" << endl << endl;

			Sleep(1000);

			cout << (*clientPtr);

			cin.get();

		}
}

// GET MAX CLIENTS ID

unsigned int Supermarket::getMaxClientsId() const {

	return maxClientsId;
}

// GET CLIENT*
template <typename T>
Client* Supermarket::getClient(T t) {

	for (auto& c : clients) {
		if (c == t) {
			Client* clientPtr = &c;
			return clientPtr;
		}
	}
	return nullptr;
}

// SHOW CLIENTS BY ALFABETIC ORDER

void Supermarket::showClientByOrder() {

	set<Client> temp;

	for (const auto& c : clients)
		temp.insert(c);

	cout << endl << " ***************************************" << endl;
	cout << "   CLIENTS BY ALFABETIC ORDER DATABASE" << endl;
	cout << " ***************************************" << endl << endl;

	for (const auto& t : temp)
		cout << t;
}

// SHOW CLIENT INFORMATION

void Supermarket::showClientInformation(string name){
	
	Client* clientPtr = getClient(name);

	cout << *clientPtr;
}

//SORT CLIENT BY SPENT AMOUNT

bool sortClientBySpentAmount (const Client &left, const Client &right) {
	
	return (left.getSpentAmount() < right.getSpentAmount());
}

//CALCULATE CLIENTS BOTTOM

vector<Client> Supermarket::calculateBottom(unsigned int numBottomClients) {

	vector <Client> bottomClients;

	for (const auto& c : clients)
		bottomClients.push_back(c);

	sort(bottomClients.begin(), bottomClients.end(), sortClientBySpentAmount);

	vector <Client> bottomClientsN;

	for (int i = 0; i < numBottomClients; i++)
		bottomClientsN.push_back(bottomClients.at(i));

	return bottomClientsN;
}

// ASK NUMBER OF BOTTOM CLIENTS

void Supermarket::numClientsBottom(unsigned int &numBottomClients) {

	cin >> numBottomClients;

	while (cin.fail() || numBottomClients <= 0 || numBottomClients >= clients.size()) {
		if (cin.fail() || numBottomClients <= 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << " You enter a not valid number!" << endl;
			cout << " Please enter a valid number> ";
			cin >> numBottomClients;
			cin.ignore(1000, '\n');
		}
		else {
			cout << " Supermarket only has " << clients.size() << " clients!" << endl;
			cout << " Please enter a valid number> ";
			cin >> numBottomClients;
			cin.ignore(1000, '\n');
		}
	}

	cout << endl;
}

// SHOW CLIENTS BOTTOM

void Supermarket::showClientsBottomCab(string mode) {

	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "======================== CLIENTS BOTTOM DATABASE ========================" << endl;
	cout << endl;
	cout << " Please insert the number of clients you want to " << mode << " > ";

}

void Supermarket::showClientsBottom(const vector<Client> &clientsBottom) {
	
	for (const auto& b : clientsBottom)
		cout << b;

}
vector<Client> Supermarket::runClientsBottom(string mode) {

	showClientsBottomCab(mode);

	unsigned int numBottomClients;

	numClientsBottom(numBottomClients);

	vector <Client> clientsBottom = calculateBottom(numBottomClients);

	showClientsBottom(clientsBottom);

	cin.get();

	return clientsBottom;

}
// VERIFY IF CLIENT HAVE TRANSACIONS

bool Supermarket::clientHaveTransaction(Client client) {

	bool cht = false;

	for (auto& t : transactions) {
		if (t.getIdClient() == client.getId())
			cht = true;
	}
	return cht;
}

// VERIFY IF CLIENT HAVE TRANSACIONS (BY ALFABETIC ORDER)

bool Supermarket::clientHaveTransaction(Client client, vector<Transaction> trans) {

	bool cht = false;

	for (auto& t : trans) {
		if (t.getIdClient() == client.getId())
			cht = true;
	}
	return cht;
}

/*********************************
 * PRODUCTS MANAGER
 ********************************/  

//LOAD PRODUCTS FILE

void Supermarket::loadProducts() {
	
	maxProductsId = 0;
	int i = 0;
	string numProducts;

	ifstream inputFile;
	inputFile.open(productsFilename);

	if (inputFile.fail()) {

		cerr << " Error opening products file";
		exit(1);
	}

	else{

		getline(inputFile,numProducts);

		while (!inputFile.eof()) {

			Product product(inputFile);
			products.push_back(product);

			productIdx.insert(std::pair<string, int>(product.getName(), i));

			i++;

			if (product.getId() > maxProductsId)
				maxProductsId = product.getId();
		}
	}
	inputFile.close();
}

// SHOW PRODUCT INFORMATION

void Supermarket::showProductInformation(string name){

	Product* productPtr = getProduct(name);

	cout << *productPtr;
}

// GET PRODUCT* BY NAME
template <typename T>
Product * Supermarket::getProduct(T t) {

	for (auto& p : products) {
		if (p == t) {
			Product* productPtr = &p;
			return productPtr;
		}
	}
	return nullptr;
}

// GET ALL PRODUCTS

vector<Client> Supermarket::getClients() const{

	return clients;
}

vector<Product> Supermarket::getProducts() const{

	return products;
}

 // SHOW PRODUCTS DATABASE HEADER
void Supermarket::showProductsDatabaseCab() {

	cout << endl << " ***********************" << endl;
	cout << "    PRODUCTS DATABASE" << endl;
	cout << " ***********************" << endl << endl;

}

// SHOW PRODUCTS DATABASE

void Supermarket::showProducts() {

	if (products.empty()) 
		cout << " The products database is empty!" << endl;
	else
		for (const auto& p : products)
			cout << p;
}

// SHOW PRODUCTS BY ALFABETIC ORDER

void Supermarket::showProductsByOrder() const{

		vector<Product> temp = products;

		sort(temp.begin(), temp.end());

		cout << endl << " *******************************************" << endl;
		cout << "   PRODUCTS BY ALFABETIC ORDER DATABASE" << endl;
		cout << " *******************************************" << endl << endl;

		for (const auto& t : temp) {

			cout << t;
		}
}

// CREATE PRODUCT

void Supermarket::createProduct() {

	unsigned int id = ++maxProductsId;
	string name;
	float price = 0;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "======================== NEW PRODUCT ======================" << endl << endl << endl;

	cout << " Please enter the product name> ";
	getline(cin, name);

	verifyStringIsNotEmptyAndNotANumber(name, "product");

	cout << " Please enter the product price> ";
	cin >> price;
	cin.ignore(1000, '\n');

	verifyCorrectPrice(price, "product");

	Product product(id, name, price);

	products.push_back(product);

	productIdx.insert(std::pair<string, int>(name, id));

	cout << endl << " New product created sucessfully!" << endl << endl;

	showProductInformation(product.getName());

	productsAlterados = true;

	cin.get();
}

// MODIFY PRODUCT

void Supermarket::modifyProduct() {

	int id;
	string newName;
	float newPrice;
	char ch;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "====================== MODIFY PRODUCT =====================" << endl << endl;

	if (products.empty()) {
		cout << " There are no products to modify!" << endl;
		cout << " The products database is empty!" << endl;
		cin.get();
	}

	else {
		showProductsDatabaseCab();
		showProducts();
		cout << endl << " Please enter the product ID to modify> ";
		cin >> id;
		cin.ignore(1000, '\n');

		verifyCorrectId(id, "product");

		while ((getProduct(id)) == nullptr)
			verifyIdExists(id, "product", "modify");

		Product* productPtr = getProduct(id);

		showProductInformation((*productPtr).getName());

		cout << " Do you want to modify the product name? (y/n)> ";
		cin >> ch;
		cin.ignore(1000, '\n');

		if (toupper(ch) == 'Y') {
			cout << endl << " Please enter the new product name> ";
			getline(cin, newName);

			verifyStringIsNotEmptyAndNotANumber(newName, "product");

			(*productPtr).setName(newName);
			cout << endl << " Product name modified sucessfully!" << endl;

			showProductInformation((*productPtr).getName());

			cin.get();
		}

		cout << " Do you want to modify the product price? (y/n)> ";
		cin >> ch;
		cin.ignore(1000, '\n');

		if (toupper(ch) == 'Y') {
			cout << endl << " Please enter the new product price> ";
			cin >> newPrice;
			cin.ignore(1000, '\n');

			verifyCorrectPrice(newPrice, "product");

			(*productPtr).setPrice (newPrice);
			cout << endl << " Product price modified sucessfully!" << endl;

			showProductInformation((*productPtr).getName());

			productsAlterados = true;

			cin.get();
		}
	}
}

// REMOVE PRODUCT

void Supermarket::removeProduct() {

	int id;
	char ch;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "====================== REMOVE PRODUCT =====================" << endl << endl;

	if (products.empty()) {
		cout << " There are no products to remove!" << endl;
		cout << " The products database is already empty!" << endl;
		cin.get();
	}

	else {
		showProductsDatabaseCab();
		showProducts();
		cout << endl << " Please enter the product ID to remove> ";
		cin >> id;
		cin.ignore(1000, '\n');

		verifyCorrectId(id, "product");

		while ((getProduct(id)) == nullptr)
			verifyIdExists(id, "product", "remove");

		Product* productPtr = getProduct(id);

		showProductInformation((*productPtr).getName());

		cout << " Are you sure you want to remove that product? (y/n)> ";
		cin >> ch;
		cin.ignore(1000, '\n');

		if (toupper(ch) == 'Y') {
			products.erase(products.begin() + (((*productPtr).getId())-1));

			productIdx.erase((*productPtr).getName());

			showProductInformation((*productPtr).getName());
			cout << endl << " Product removed sucessfully!" << endl;

			productsAlterados = true;

			cin.get();
		}
	}
}

// SEARCH PRODUCT BY ID

void Supermarket::searchProductByID() {

	int id;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "=================== SEARCH PRODUCT BY ID ==================" << endl << endl;

	if (products.empty()) {
		cout << " There are no products to remove!" << endl;
		cout << " The products database is already empty!" << endl;
		cin.get();
	}

	else {

		cout << endl << " Please enter the product ID> ";

		cin >> id;
		cin.ignore(1000, '\n');

		verifyCorrectId(id, "product");

		while ((getProduct(id)) == nullptr)
			verifyIdExists(id, "product", "");

		cout << endl << " Product found!" << endl << endl;

		Sleep(1000);

		Product* productPtr = getProduct(id);

		showProductInformation((*productPtr).getName());

		cin.get();
	}
}

// SEARCH PRODUCT BY NAME

void Supermarket::searchProductByName() {

	string name;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "=================== SEARCH PRODUCT BY NAME ================" << endl << endl;

	if (products.empty()) {
		cout << " There are no products to remove!" << endl;
		cout << " The products database is already empty!" << endl;
		cin.get();
	}

	else {

		cout << endl << " Please enter the product name> ";

		getline(cin, name);

		verifyStringIsNotEmptyAndNotANumber(name, "product");

		while ((getProduct(name)) == nullptr) 
			verifyNameExists(name, "product");

		Product* productPtr = getProduct(name);

		cout << endl << " Product found!" << endl << endl;

		Sleep(1000);

		showProductInformation((*productPtr).getName());

		cin.get();

	}
}

// SHOW PRODUCTS WITH PRICE

void Supermarket::showProductsWithPrice(vector<string> prods) {

	for(const auto& p:prods) {

		cout << " *** PRODUCT " << productIdx[p] << " ***" << endl;
		cout << " Name: " << p << endl;

		for(const auto& prod:products)
			if(prod.getName()==p)
			cout << " Price: " << prod.getPrice() << endl << endl;
	}
}

/*********************************
* TRANSACTIONS MANAGER
********************************/

// LOAD TRANSACTIONS FILE

void Supermarket::loadTransactions() {

	maxTransactionsId =0;
	unsigned int i = 0;
	string numTransactions;

	ifstream inputFile;
	inputFile.open(transactionsFilename);

	if (inputFile.fail()) {
		cerr << " Error opening transaction file";
		exit(1);
	}
	else
	{
		getline(inputFile, numTransactions);

		while (!inputFile.eof())
		{
			Transaction transaction(inputFile);
			transactions.push_back(transaction);

			transactionIdx.insert(std::pair<int, int>(transaction.getIdClient(), i));

			i++;

			if (transaction.getId() > maxTransactionsId)
				maxTransactionsId = transaction.getId();
		}
		inputFile.close();
	}
}

// CREATE TRANSACTION

void Supermarket::createTransaction(){
	
	int client;
	int id = ++maxTransactionsId;
	int idClient, idProduct;
	float totalTransaction = 0;
	string productName, line;
	vector<string> transactionProducts;

	bool clientCorrect = false;
	bool moreProducts = false;

	char ch;

	cout << endl << endl;
	cout << TAB_BIG << TAB_BIG << TAB << TAB << "======================== NEW TRANSACTION ======================" << endl << endl;

	if (clients.empty() || products.empty()) {
		if (clients.empty()) {
			cout << " A new transaction could not be created!" << endl;
			cout << " The clients database is empty!" << endl;
			cin.get();
		}
		else {
			cout << " There are no products to modify!" << endl;
			cout << " The products database is empty!" << endl;
			cin.get();
		}
	}

	else {

		//CLIENT

		do {
			clientCorrect = false;

			showClientsDatabaseCab();
			showClients();
			cout << endl << " Please enter the client ID> ";
			cin >> idClient;
			cin.ignore(1000, '\n');

			verifyCorrectId(idClient, "client");

			while (getClient(idClient) == nullptr)
				verifyIdExists(idClient, "client", "create");

			Client* clientPtr = getClient(idClient);
			
			client = clientIdx[(*clientPtr).getName()];

			cout << endl << " Client found!" << endl << endl;

			Sleep(1000);

			cout << (*clientPtr);

			cout << " Are you sure is that client? (y/n)>";
			cin >> ch;
			cin.ignore(1000, '\n');

			if (toupper(ch) == 'Y') {
				clientCorrect = true;
				cout << " Client selected!" << endl << endl;
				Sleep(1000);
			}
			else {
				cout << " Client not selected!" << endl;
				Sleep(1000);
			}
		} while (!clientCorrect);

		//DATE

		Date transactionDate = Date();

		//PRODUCTS
		do {
			moreProducts = false;

			showProductsDatabaseCab();
			showProducts();
			cout << endl << " Please enter the product ID> ";
			cin >> idProduct;
			cin.ignore(1000, '\n');

			verifyCorrectId(idProduct, "product");

			while ((getProduct(idProduct)) == nullptr)
				verifyIdExists(idProduct, "product", "add");

			Product* productPtr = getProduct(idProduct);

			cout << (*productPtr);

			cout << " Are you sure is that product? (y/n)> ";
			cin >> ch;
			cin.ignore(1000, '\n');

			if (toupper(ch) == 'Y') {
				transactionProducts.push_back((*productPtr).getName());
				totalTransaction += ((*productPtr).getPrice());
				cout << " Product added to this transaction!" << endl;
				Sleep(1000);
			}

			else {
				cout << " Product not added to this transaction!" << endl;
				Sleep(1000);
			}

			cout << " Do you want to add more prodcuts to this transaction? (y/n)> ";
			cin >> ch;
			cin.ignore(1000, '\n');

			if (toupper(ch) == 'Y') {
				moreProducts = true;
			}

			else {
				cout << " Transaction created sucessfully!" << endl;
				cin.get();
			}

		} while (moreProducts);

		 clients.at(client).setSpentAmount(totalTransaction);

		 Transaction transaction(id, idClient, transactionDate, transactionProducts);
		 transactions.push_back(transaction);

		 transactionIdx.insert(std::pair<int, int>(idClient, id));

		 transacoesAlterdas = true;

		showTransactionByID(id);
	}
}

// SHOW TRANSACTIONS DATABASE HEADER

void Supermarket::showTransactionsDatabaseCab() {

	cout << endl << " ***********************" << endl;
	cout << "    TRANSACTIONS DATABASE" << endl;
	cout << " ***********************" << endl << endl;

}

// SHOW TRANSACTION

void Supermarket::showTransactionByID(int idTransaction) {

	int posT = getTransactionPos(idTransaction);
	Client* clientPtr = getClient(transactions.at(posT).getIdClient());

	cout << endl;
	cout << setw(60) << "***** Transaction ID. " << idTransaction << " *****" << endl << endl;
	cout << " _____________________________" << endl << endl;
	cout << setw(12) << "CLIENT ID. " << transactions.at(posT).getIdClient() << endl;
	cout << setw(14) << "CLIENT NAME: " << (*clientPtr).getName() << endl;
	cout << setw(7) << " DATE: ";
	cout << transactions.at(posT).getDate();
	cout << endl << " _____________________________" << endl;
	cout << endl << endl;

	showProductsWithPrice(transactions.at(posT).getProducts());

	showTransactionAmount(idTransaction);

	cin.get();
	clearScreen();

}

// SHOW TRANSACTIONS DATABASE

void Supermarket::showAllTransactions() {

	cout << endl;
	cout << TAB_BIG << TAB_BIG << TAB << " ==================== TRANSACTIONS DATABASE =====================" << endl << endl << endl;

	int aux = 0;

	for (const auto& t:transactions) {

		cout << endl;
		cout << setw(63) << "***** Transaction ID. " << t.getId() << " *****" << endl << endl;
		cout << " _____________________________" << endl << endl;
		cout << setw(12) << "CLIENT ID. " << t.getIdClient() << endl;
		
		Client* clientPtr = getClient(t.getIdClient());
		
		cout << setw(14) << "CLIENT NAME: " << (*clientPtr).getName() << endl;
		
		cout << setw(7) << " DATE: ";
		cout << t.getDate();
		cout << endl << " _____________________________" << endl;
		cout << endl << endl;
		showProductsWithPrice(t.getProducts());
		cout << " _____________________________" << endl << endl;

		showTransactionAmount(t.getId());

		cin.get();
		clearScreen();
	}
}

// SHOW TRANSACTION BY CLIENT

void Supermarket::showTransactionsByClient(Client client) {

	cout << " _____________________________" << endl << endl;
	cout << setw(12) << "CLIENT ID. " << client.getId() << endl;
	cout << setw(14) << "CLIENT NAME: " << client.getName() << endl;
	cout << setw(14) << " SPENT AMOUNT: " << client.getSpentAmount() << endl;
	cout << " _____________________________" << endl;

	for (auto& t : transactions) {
		cout << endl;
		if (t.getIdClient() == client.getId()) {
			cout << setw(63) << "***** Transaction ID. " << t.getId() << " *****" << endl << endl;
			cout << setw(7) << " DATE: ";
			cout << t.getDate();
			cout << endl << endl;
			showProductsWithPrice(t.getProducts());
			showTransactionAmount(t.getId());

			cin.get();
			clearScreen();
		}
	}
}

// SHOW TRANSACTION BY CLIENT (BY ALFABETIC ORDER)

void Supermarket::showTransactionsByClient(Client client, vector<Transaction> trans) {

	cout << " _____________________________" << endl << endl;
	cout << setw(12) << "CLIENT ID. " << client.getId() << endl;
	cout << setw(14) << "CLIENT NAME: " << client.getName() << endl;
	cout << setw(14) << " SPENT AMOUNT: " << client.getSpentAmount() << endl;
	cout << " _____________________________" << endl;

	for (auto& t : trans) {
		if (t.getIdClient() == client.getId()) {
			cout << endl;
			cout << setw(63) << "***** Transaction ID. " << t.getId() << " *****" << endl << endl;
			cout << setw(7) << " DATE: ";
			cout << t.getDate();
			cout << endl << endl;
			showProductsWithPrice(t.getProducts());
			showTransactionAmount(t.getId());

			cin.get();
			clearScreen();
		}
	}
}

// SEARCH TRANSACTION BY ID

void Supermarket::searchTransactionsByID() {

	int aux = 0;
	int idTransaction = -1;
	bool idCorrect = false;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << "==================== SEARCH TRANSACTIONS BY ID ===================" << endl << endl;

	if (transactions.empty()) {
		cout << " There are no transactions to be searched!" << endl;
		cout << " The transactions database is empty!" << endl;
		cin.get();
	}

	else {
		do {
			cout << endl << " Please enter the transaction ID> ";

			cin >> aux;
			cin.ignore(1000, '\n');

			verifyCorrectId(aux, "transaction");

			for (auto& t : transactions) {
				if (t.getId() == aux) {
					idCorrect = true;
					idTransaction = aux;
					showTransactionByID(idTransaction);
				}
			}

			if (idTransaction == -1)
				cout << "There is no transaction with that ID!" << endl;

		} while (!idCorrect);
	}
}

// SEARCH TRANSACTION BY CLIENT NAME

void Supermarket::searchTransactionsByClientName() {

	string name;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << "==================== SEARCH TRANSACTIONS BY CLIENT NAME ===================" << endl << endl;

	if (clients.empty() || transactions.empty()) {
		if (clients.empty()) {
			cout << " A transaction could not be searched!" << endl;
			cout << " The clients database is empty!" << endl;
			cin.get();
		}
		else {
			cout << " There are no transactions to be searched!" << endl;
			cout << " The transactions database is empty!" << endl;
			cin.get();
		}
	}

	else {

		vector<Transaction> transactionsOrdered;

		for (const auto& t : transactions)
			transactionsOrdered.push_back(t);

		sort(transactionsOrdered.begin(), transactionsOrdered.end(), sortTransactionsByDate);
		
		cout << endl << " Please enter the client name> ";

		getline(cin, name);

		verifyStringIsNotEmptyAndNotANumber(name, "client");

		while (getClient(name) == nullptr)
			verifyNameExists(name, "client");
		
		Client* clientPtr = getClient(name);

		cout << endl << " Client found!" << endl << endl;

		Sleep(1000);

		if (clientHaveTransaction((*clientPtr),transactionsOrdered))
			showTransactionsByClient((*clientPtr), transactionsOrdered);
		else
		{
			cout << " The client selected have no transactions!" << endl;
			cin.get();
		}
	}
}

// SHOW TRANSACTIONS BY DATE

void Supermarket::showTransactionsByDate(Date date) {

	bool transactionExists = false;

	cout << endl << " ___________________" << endl << endl;
	cout << setw(7) << "  DATE: ";
	cout << date;
	cout << endl << " ___________________" << endl;

	for (auto& t : transactions) {
		if (t.getDate() == date) {
			transactionExists = true;
			cout << endl;
			cout << setw(62) << "***** Transaction ID. " << t.getId() << " *****" << endl << endl;
			cout << endl;

			cout << " _____________________________" << endl << endl;
			cout << setw(12) << "CLIENT ID. " << t.getIdClient() << endl;

			Client* clientPtr = getClient(t.getIdClient());

			cout << setw(14) << "CLIENT NAME: " << (*clientPtr).getName() << endl;
			cout << " SPENT AMOUNT: " << (*clientPtr).getSpentAmount() << endl;

			showProductsWithPrice(t.getProducts());

			showTransactionAmount(t.getId());

			cin.get();
			clearScreen();
		}
	}
		if(!transactionExists){
			cout << endl << setw(14) << " There is no transaction on that day!" << endl;
			cin.get();
			clearScreen();
		}
		cout << " _____________________________" << endl << endl;
	
}

// SEARCH TRANSACTIONS BY DATE

void Supermarket::searchTransactionsByDate() {

	string line;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << "==================== SEARCH TRANSACTIONS BY DATE ===================" << endl << endl << endl;

	cout << " Please enter a date for search transactions (dd/mm/yyyy)>";
	getline(cin, line);

	Date date(line);

	showTransactionsByDate(date);

}

// SEARCH TRANSACTIONS BETWEEN DATES

void Supermarket::searchTransactionsBetweenDates() {

	string line;

	cout << endl;
	cout << TAB_BIG << TAB_BIG << "==================== SEARCH TRANSACTIONS BETWEEN DATES ===================" << endl << endl << endl;

	//Initial date

	cout << " Please enter the initial date for search transactions (dd/mm/yyyy)>";
	getline(cin, line);

	Date dateI(line);

	//Final date

	cout << " Please enter the final date for search transactions (dd/mm/yyyy)>";
	getline(cin, line);

	Date dateF(line);

	showTransactionsBetweenDates(dateI, dateF);
}

// SHOW TRANSACTIONS BETWEEN DATES

void Supermarket::showTransactionsBetweenDates(Date di, Date df) {

	bool transactionExists = false;

	cout << endl << " _____________________________" << endl << endl;
	cout << setw(7) << "  INITAL DATE: ";
	cout << di;
	cout << endl;
	cout << setw(7) << "  FINAL DATE: ";
	cout << df;
	cout << endl << " _____________________________" << endl;

	for (auto& t : transactions) {
		if (t.getDate()>=di && t.getDate()<=df) {
			transactionExists = true;
			cout << endl;
			cout << setw(62) << "***** Transaction ID. " << t.getId() << " *****" << endl << endl;
			cout << endl;

			cout << " _____________________________" << endl << endl;
			cout << setw(12) << "CLIENT ID. " << t.getIdClient() << endl;

			Client* clientPtr = getClient(t.getIdClient());

			cout << setw(14) << "CLIENT NAME: " << (*clientPtr).getName() << endl;
			cout << " SPENT AMOUNT: " << (*clientPtr).getSpentAmount() << endl;

			showProductsWithPrice(t.getProducts());

			showTransactionAmount(t.getId());

			cin.get();
			system("cmd /c cls");
		}
	}

	if (!transactionExists) {
		cout << endl << setw(14) << " There is no transaction between those dates!" << endl;
		cin.get();
		clearScreen();
	}	
}

// GET TOTAL TRANSACTION AMOUNT

float Supermarket::getTransactionAmount(int idTransaction) {

	int posT = getTransactionPos(idTransaction);
	float total = 0;

	for (const auto& p : transactions.at(posT).getProducts()) {
		for (const auto& prod : products)
			if (prod.getName() == p)
				total += prod.getPrice();
	}
	return total;
}

// SHOW TOTAL TRANSACTION AMOUNT

void Supermarket::showTransactionAmount(int idTransaction) {

	cout << " TRANSACTION TOTAL AMOUNT: " << getTransactionAmount(idTransaction) << endl;

}

// GET ALL TRANSACTIONS

vector<Transaction> Supermarket::getTransactions() const {

	return transactions;
}

// GET TRANSACTION POSITION IN TRANSACTIONS VECTOR

int Supermarket::getTransactionPos(int idTransaction) {

	int Pos = 0;

	for (int i = 0; i < transactions.size(); i++) {
		if (transactions.at(i).getId() == idTransaction)
			return i;
		else
			Pos = -1;
	}
	return Pos;
}

// SORT TRANSACTIONS BY DATE

bool sortTransactionsByDate(const Transaction & left, const Transaction & right) {

	return (left.getDate() < right.getDate());
}

/*********************************
* RECOMMENDATION MANAGER
********************************/

// CHOOSE TARGET CLIENT
int Supermarket::targetClientRecomendationSystem() {

	int idTargetClient;

	if (clients.empty()) {
		cout << " There are no clients to remove!" << endl;
		cout << " The clients database is already empty!" << endl;
		cin.get();
	}

	else {

		cout << endl;
		cout << TAB_BIG << TAB_BIG << TAB << TAB << TAB << "==================== SEARCH TARGET CLIENT BY ID ===================" << endl << endl;
		showClientsDatabaseCab();
		showClients();
		cout << " Please enter the target client ID> ";

		cin >> idTargetClient;
		cin.ignore(1000, '\n');

		verifyCorrectId(idTargetClient, "client");

		while (getClient(idTargetClient) == nullptr)
			verifyIdExists(idTargetClient, "client", "");

		Client* clientPtr = getClient(idTargetClient);

		cout << endl;
		cout << " Client found!" << endl << endl;

		Sleep(1000);

		cout << (*clientPtr);

		cin.get();
	}

	return idTargetClient;
}

// GENERATE RECOMMENDATION SYSTEM

string Supermarket::generateRecomendationSystem() {

	int idTargetClient = targetClientRecomendationSystem();

	//RECOMMENDATION MATRIX

	map<int, int> idClientToMatrixLine; //ID CLIENT TO MATRIX LINE
	map<int, int> idProductToMatrixColumn; //ID PRODUCT TO MATRIX COLUMN

	vector<vector<bool>> recommendationMatrix = generateRecomendationMatrix(clients, idClientToMatrixLine, idProductToMatrixColumn);

	//TARGET CLIENT LINE
	vector<bool> targetClientLine = recommendationMatrix.at(idClientToMatrixLine[idTargetClient]);

	//RECOMMENDATION MATRIX WITHOUT TARGET CLIENT LINE
	vector<vector<bool>> reducedRecommendationMatrix = recommendationMatrix;

	unsigned int rowToDelete = idClientToMatrixLine[idTargetClient];

	reducedRecommendationMatrix.erase(reducedRecommendationMatrix.begin() + rowToDelete);

	// GET POTENCIAL CLIENTS AND PRODUCTS

	vector <Client> potencialClients;
	map<int, int> potencialProducts;

	getPotencialClientsProducts(reducedRecommendationMatrix, targetClientLine, idClientToMatrixLine, idProductToMatrixColumn, potencialClients, potencialProducts);

	Product* product = getRecommendedProduct(potencialProducts);

	if (product == NULL)
		return "";
	else
		return (*product).getName();
}

// GENERATE RECOMMENDATION MATRIX

vector<vector<bool>> Supermarket::generateRecomendationMatrix(const vector<Client> &clientsVector, map<int, int> &idClientToMatrixLine, map<int, int> &idProductToMatrixColumn) {

	//RECOMMENDATION MATRIX

	unsigned int nLin = clientsVector.size();
	unsigned int nCol = products.size();

	vector<vector<bool>> recommendationMatrix(nLin, vector<bool>(nCol, false));

	map<int, int>::iterator itClient;

	//FILL CLIENT MAP
	for (int i = 0; i < nLin; i++)
		idClientToMatrixLine[clientsVector.at(i).getId()] = i;

	//FILL PRODUCT MAP
	for (int j = 0; j < nCol; j++)
		idProductToMatrixColumn[products.at(j).getId()] = j;

	//SET TRUE ON PRODUCT BOUGHT BY CLIENT
	for (auto& t : transactions) {
		itClient = idClientToMatrixLine.find(t.getIdClient());
		if (itClient != idClientToMatrixLine.end())
			for (auto& p : t.getProducts()) {
				Product* product = getProduct(p);
				recommendationMatrix.at(idClientToMatrixLine[t.getIdClient()]).at(idProductToMatrixColumn[(*product).getId()]) = true;
			}
	}

	return recommendationMatrix;
}

// BOUGHT SIMILAR PRODUCTS

bool Supermarket::boughtSimilarProdcuts(const vector<bool> &target, const vector<bool> &potencialClient) {

	unsigned int nProductsTarget = 0;
	unsigned int nProductsPotencial = 0;

	for (int i = 0; i < target.size(); i++) 
		if (target.at(i) == true)
			nProductsTarget++;
	
	for (int i = 0; i < potencialClient.size(); i++)
		if (potencialClient.at(i) == true)
			nProductsPotencial++;

	if(nProductsTarget==0)
		return false;

	else if (nProductsTarget >= nProductsPotencial)
		return false;

	else
		for(int i = 0; i < target.size(); i++)
			if (target[i] == true && potencialClient[i] == false)
				return false;

	return true;
}

// GET POTENCIAL PRODUTS

void Supermarket::getPotencialProducts(const vector<bool> &target, const vector<bool> &potencialClient, map<int,int> &potencialProducts, const map<int, int> &idProductToMatrixColumn) {

	for (int i = 0; i < target.size(); i++)
		if (target[i] == false && potencialClient[i] == true)
			for (auto itProduct = idProductToMatrixColumn.begin(); itProduct != idProductToMatrixColumn.end(); ++itProduct) {
				if (itProduct->second == i)
					potencialProducts[itProduct->first]++;
			}
}

// GET RECOMMENDED PRODUCT

Product* Supermarket::getRecommendedProduct(map<int, int> &potencialProducts) {

	int qtdMax = -1;
	int idProductMax = -1;
	
	for (auto it = potencialProducts.cbegin(); it != potencialProducts.cend(); ++it){
		if (it->second > qtdMax) {
			idProductMax = it->first;
			qtdMax = it->second;
		}
	}

	Product* product = getProduct(idProductMax);

	return product;
}

// SHOW RECOMMENDATION SYSTEM

void Supermarket::showRecommendationSystem() {

	string productName = generateRecomendationSystem();

	if(productName=="")
		cout << " There is no recommended product for the selected client!" << endl;
	else
		cout << " The recommended product for the selected client is: " << productName << endl;

}

// GENERATE RECOMMENDATION SYSTEM TO BOTTOM CLIENTS

string Supermarket::generateRecomendationSystemBottom(const vector<Client> &clientsBottom) {

	map<int, int> idClientToMatrixLine; //ID CLIENT TO MATRIX LINE
	map<int, int> idProductToMatrixColumn; //ID PRODUCT TO MATRIX COLUMN

	vector<vector<bool>> recommendationMatrix = generateRecomendationMatrix(clientsBottom, idClientToMatrixLine, idProductToMatrixColumn);

	// GET COMMON PRODUCTS
	vector<bool> commonProducts = getCommonProducts(recommendationMatrix);

	// GET CLIENTS ON TOP

	vector<Client> topClients = getTopClients(clientsBottom);

	// GET RECOMMENDATION TOP CLIENTS MATRIX

	map<int, int> idClientTopToMatrixLine; //ID CLIENT TO MATRIX LINE
	map<int, int> idProductTopToMatrixColumn; //ID PRODUCT TO MATRIX COLUMN

	vector<vector<bool>> recommendationTopClientsMatrix = generateRecomendationMatrix(topClients, idClientTopToMatrixLine, idProductTopToMatrixColumn);

	// GET POTENCIAL CLIENTS

	vector<Client> potencialClients; 
	map<int, int> potencialProducts;

	getPotencialClientsProducts(recommendationTopClientsMatrix, commonProducts, idClientTopToMatrixLine, idProductTopToMatrixColumn, potencialClients, potencialProducts);	

	removeProductsBoughtByBottom(recommendationMatrix, potencialProducts, idProductToMatrixColumn);

	if (potencialProducts.size() != 0) {
		multimap<int, int> potencialProducts_flip = flip_map(potencialProducts);

		multimap<int, int>::reverse_iterator itPotencialProducts_flip = potencialProducts_flip.rbegin();

		Product* product = getProduct(itPotencialProducts_flip->second);

		if (product == NULL) {
			Product* productRecommended = getProductMoreFrequentOnTopAndLessOnBottom(recommendationMatrix, recommendationTopClientsMatrix, idProductToMatrixColumn, idProductTopToMatrixColumn);
			if (productRecommended != nullptr)
				return (*productRecommended).getName();
			else
				return "";
		}
		else
			return (*product).getName();
	}
	else{

		Product* productRecommended = getProductMoreFrequentOnTopAndLessOnBottom(recommendationMatrix, recommendationTopClientsMatrix, idProductToMatrixColumn, idProductTopToMatrixColumn);
		
		if(productRecommended != nullptr)
			return (*productRecommended).getName();
		else 
			return "";
	}
	
}

// GET POTENCIAL CLIENTS

void Supermarket::getPotencialClientsProducts(const vector<vector<bool>>& recommendationMatrix, const vector<bool>& comparator, const map<int, int> &idClientToMatrixLine, const map<int, int> &idProductToMatrixColumn, vector<Client> &potencialClients, map<int,int> &potencialProducts){
	
	map<int, int>::const_iterator itClient;

	for (int i = 0; i < recommendationMatrix.size(); i++) {
		vector<bool> line = recommendationMatrix.at(i);
		if (boughtSimilarProdcuts(comparator, line)) {
			for (itClient = idClientToMatrixLine.begin(); itClient != idClientToMatrixLine.end(); ++itClient) {
				if (itClient->second == i) {
					Client* client = getClient(itClient->first);
					potencialClients.push_back(*client);
				}
			}
			getPotencialProducts(comparator, line, potencialProducts, idProductToMatrixColumn);
		}
	}
}

// GET COMMON PRODUCTS 

vector<bool> Supermarket::getCommonProducts(const vector<vector<bool>> &recommendationMatrix) {

	bool common =true;
	vector<bool> commonProducts;

	for (int col = 0; col < recommendationMatrix.at(0).size(); col++) {
		for (int line = 0; line < recommendationMatrix.size(); line++) {
			if (recommendationMatrix.at(line).at(col) == false) {
				common = false;
				break;
			}
		}
		if(!common)
			commonProducts.push_back(false);
		else
			commonProducts.push_back(true);
		common = true;
	}
	return commonProducts;
}

void Supermarket::removeProductsBoughtByBottom(const vector<vector<bool>> &recommendationMatrix, map<int, int> &potencialProducts, const map<int, int> idProductToMatrixColumn) {

	bool bought = false;
	map<int, int>::const_iterator itProduct;

	for (int col = 0; col < recommendationMatrix.at(0).size(); col++) {
		for (int line = 0; line < recommendationMatrix.size(); line++) {
			if (recommendationMatrix.at(line).at(col) == true) {
				bought = true;
				break;
			}
		}
		if (bought) {
			for (itProduct = idProductToMatrixColumn.begin(); itProduct != idProductToMatrixColumn.end(); ++itProduct)
				if (itProduct->second == col) 
					potencialProducts.erase(itProduct->first);
		}
		
		bought = false;
	}
}
// GET CLIENTS ON TOP

vector<Client> Supermarket::getTopClients(const vector<Client> &clientsBottom) {

	vector<Client> topClients = clients;

	for (auto& cb : clientsBottom)
		topClients.erase(find(topClients.begin(), topClients.end(), cb));

	return topClients;
}

Product* Supermarket::getProductMoreFrequentOnTopAndLessOnBottom(const vector<vector<bool>> &recommendationBottomMatrix, const vector<vector<bool>> &recommendationTopMatrix, const map<int, int> idProductToMatrixColumn, const map<int, int> &idProductTopToMatrixColumn) {

	map<int,int> ProductsBottom;
	map<int,int> ProductsTop;

	int sum=0;

	for (int col = 0; col < recommendationBottomMatrix.at(0).size(); col++) {
		for (int line = 0; line < recommendationBottomMatrix.size(); line++) {
			if (recommendationBottomMatrix.at(line).at(col) == true)
				sum++;
		}
		for (auto itProduct = idProductToMatrixColumn.begin(); itProduct != idProductToMatrixColumn.end(); ++itProduct) {
			if (itProduct->second == col) {
				ProductsBottom.insert(pair<int, int>(itProduct->first, sum));
				break;
			}
		}
		sum = 0;
	}

	for (int col = 0; col < recommendationTopMatrix.at(0).size(); col++) {
		for (int line = 0; line < recommendationTopMatrix.size(); line++) {
			if (recommendationTopMatrix.at(line).at(col) == true)
				sum++;
		}
		for (auto itProduct = idProductTopToMatrixColumn.begin(); itProduct != idProductTopToMatrixColumn.end(); ++itProduct) {
			if (itProduct->second == col && sum!=0) {
				ProductsTop.insert(pair<int, int>(itProduct->first, sum));
				break;
			}
		}		
		sum = 0;
	}

	multimap<int, int> ProductsBottom_flip = flip_map(ProductsBottom);;
	multimap<int, int> ProductsTop_flip = flip_map(ProductsTop);

	multimap<int, int>::iterator i;
	multimap<int, int>::reverse_iterator j;

	for (i = ProductsBottom_flip.begin(), j = ProductsTop_flip.rbegin(); j != ProductsTop_flip.rend(); ++i, ++j) {
		if (i->first < j->first) {
			if (i->second == j->second) {
				Product* product = getProduct(i->second);
				return product;
			}
		}
	}
	
	if (ProductsTop_flip.size() != 0) {
		j = ProductsTop_flip.rbegin();
		Product* product = getProduct(j->second);
		return product;
	}
	else
		return nullptr;
}

// SHOW RECOMMENDATION SYSTEM BOTTOM
void Supermarket::showRecommendationSystemBottom() {
	
	vector<Client> clientsBottom = runClientsBottom("advertise");

	string productName = generateRecomendationSystemBottom(clientsBottom);

	if (productName == "")
		cout << " There is no recommended product for bottom clients!" << endl;
	else
		cout << " The recommended product for bottom clients is: " << productName << endl;
}

/*********************************
 * SAVE CHANGES
 ********************************/  

// SAVE CHANGES

void Supermarket::saveChanges() {

	if (clientesAlterados || productsAlterados || transacoesAlterdas) {

		cout << endl;
		cout << TAB << "Saving modifications before exit";
		Sleep(1000);
		cout << ".";
		Sleep(1000);
		cout << ".";
		Sleep(1000);
		cout << ".";
		Sleep(1000);
		cout << endl;
		cout << TAB << "Files saved successfully!" << endl;
		cout << TAB << "Good Bye!" << endl;

		if (clientesAlterados) {

			ofstream outputFile;
			outputFile.open(clientsFilename);

			string line;

			if (outputFile.fail()) {

				cerr << " Error opening clients file";
				exit(1);

			}

			else {

				outputFile << clients.size() << endl;

				for (auto& c : clients) {

					if (c.getId() != clients.back().getId()) {

						c.save(outputFile);
						outputFile << endl;
					}
					else
						c.save(outputFile);
				}

			}
			outputFile.close();
		}

		//SAVE PRODUCTS

		if (productsAlterados) {

			ofstream outputFile;
			outputFile.open(productsFilename);

			if (outputFile.fail()) {
				cerr << " Error opening products file";
				exit(1);
			}
			else {

				outputFile << products.size() << endl;

				for (auto& p : products) {

					if (p.getId() != products.back().getId()) {

						p.save(outputFile);
						outputFile << endl;
					}
					else
						p.save(outputFile);
				}
			}
			outputFile.close();
		}

		// SAVE TRANSACTIONS

		if (transacoesAlterdas) {

			ofstream outputFile;
			outputFile.open(transactionsFilename);

			if (outputFile.fail()) {
				cerr << " Error opening transactions file";
				exit(1);
			}

			else {

				outputFile << transactions.size() << endl;

				for (auto& t : transactions) {

					if (t.getId() != transactions.back().getId()) {

						t.save(outputFile);
						outputFile << endl;
					}
					else
						t.save(outputFile);
				}
			}
			outputFile.close();
		}
	}
	else
		cout << TAB << "Good Bye!" << endl;
}

/*********************************
 * STORE STATISTICS
 ********************************/  

// SHOW STORE STATISTICS

ostream& operator<<(ostream& out, const Supermarket & supermarket){

	out << " Number of Clients: " << supermarket.clients.size() << endl;
	out << " Number of Products: " << supermarket.products.size() << endl;
	out << " Number of Transactions: " << supermarket.transactions.size() << endl;

	cin.get();

	return out;
}