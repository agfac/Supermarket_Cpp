#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <Windows.h>
#include <set>

#include "defs.h"
#include "Date.h"
#include "Client.h"
#include "Transaction.h"
#include "Product.h"
#include "utils.h"

using namespace std;

class Supermarket {
	/* DATA MEMBERS */
 private:
	string storeName; // nome da loja
	string clientsFilename, productsFilename, transactionsFilename; // nome dos
						     // ficheiros de
						     // clientes,
						     // produtos e
						     // transacoes
	bool transacoesAlterdas = false; // flag que fica a true se for preciso guardar no final as transacoes
	bool clientesAlterados = false; // flag que fica a true se for preciso guardar no final os clientes
	bool productsAlterados = false;
	unsigned int maxClientsId; // variavel que guarda o identificador unico do cliente com o maior numero de identificacao
	unsigned int maxProductsId;
	unsigned int maxTransactionsId;
	vector<Client> clients; // vetor que guarda a informacao dos clientes existentes
	vector<Product> products; // vetor que guarda a informacao dos produtos disponiveis
	vector<Transaction> transactions; // vetor que guarda a informacao das ttransacoes efetuadas
	map<string, int> clientIdx;  // map para "traduzir" nome do cliente no  correspondente  indice no vetor de clientes
	map<string, int> productIdx;  // map para "traduzir" nome do produto no correspondente indice no vetor de produtos
	multimap<int, int> transactionIdx; // multimap para "traduzir" o identificador do cliente nos indices das suas
				   // transacoes no vetor de transacoes

 public:
	Supermarket(string storeName, string clientsFilename, string productsFilename, string transactionsFilename);
	void showClientsDatabaseCab();
	void showClients();
	void createClient();
	void modifyClient();
	void removeClient();
	void searchClientByID();
	void searchClientByName();
	void showClientByOrder();
	void showClientInformation(string name);
	void saveChanges();
	void loadClients();
	vector<Client> calculateBottom(unsigned int numBottomClients);
	void showClientsBottom(const vector<Client> &clientsBottom);
	vector<Client> runClientsBottom(string mode);
	void numClientsBottom(unsigned int & numBottomClients);
	void showClientsBottomCab(string mode);
	void loadProducts();
	void showProductInformation(string name);
	void loadTransactions();
	template <typename T>
	Client* getClient(T t);
	template <typename T>
	Product* getProduct(T t);
	vector<Client> getClients() const;
	vector<Product> getProducts() const;
	vector<Transaction> getTransactions() const;
	unsigned int getMaxClientsId() const;
	void showProductsDatabaseCab();
	void showProducts();
	void showProductsByOrder() const;
	void createProduct();
	void modifyProduct();
	void removeProduct();
	void searchProductByID();
	void searchProductByName();
	void showProductsWithPrice(vector<string> products);
	void createTransaction();
	void showTransactionsDatabaseCab();
	void showTransactionByID(int idTransaction);
	void showAllTransactions();
	void showTransactionsByClient(Client client);
	void showTransactionsByClient(Client client, vector<Transaction> trans);
	void searchTransactionsByID();
	void searchTransactionsByClientName();
	void showTransactionsByDate(Date date);
	void searchTransactionsByDate();
	void searchTransactionsBetweenDates();
	void showTransactionsBetweenDates(Date di, Date df);
	string generateRecomendationSystem();
	vector<vector<bool>> generateRecomendationMatrix(const vector<Client>& clientsVector, map<int, int>& idClientToMatrixLine, map<int, int>& idProductToMatrixColumn);
	void showRecommendationSystem();
	string generateRecomendationSystemBottom(const vector<Client> &clientsBottom);
	void getPotencialClientsProducts(const vector<vector<bool>>& recommendationMatrix, const vector<bool>& comparator, const map<int, int>& idClientToMatrixLine, const map<int, int>& idProductToMatrixColumn, vector<Client>& potencialClients, map<int, int>& potencialProducts);
	vector<bool> getCommonProducts(const vector<vector<bool>>& recommendationMatrix);
	void removeProductsBoughtByBottom(const vector<vector<bool>>& recommendationMatrix, map<int, int>& potencialProducts, const map<int, int> idProductToMatrixColumn);
	vector<Client> getTopClients(const vector<Client>& clientsBottom);
	Product * getProductMoreFrequentOnTopAndLessOnBottom(const vector<vector<bool>>& recommendationBottomMatrix, const vector<vector<bool>>& recommendationTopMatrix, const map<int, int> idProductToMatrixColumn, const map<int, int>& idProductTopToMatrixColumn);
	void showRecommendationSystemBottom();
	bool clientHaveTransaction(Client client);
	bool clientHaveTransaction(Client client, vector<Transaction> trans);
	float getTransactionAmount(int idTransaction);
	void showTransactionAmount(int idTransaction);
	int getTransactionPos(int idTransaction);
	int targetClientRecomendationSystem();
	void reduceRecomendationSystem(vector<vector<bool>> &recommendationMatrix);
	bool boughtSimilarProdcuts(const vector<bool> &target, const vector<bool> &potencialClient);
	void getPotencialProducts(const vector<bool>& target, const vector<bool>& potencialClient, map<int, int> &potencialProducts, const map<int, int> &idProductToMatrixColumn);
	Product * getRecommendedProduct(map<int, int>& potencialProducts);
	void runRecomendationSystem();
	//void callPersonalizedAdvertising(Client* client);

	friend ostream& operator<<(ostream& out, const Supermarket & supermarket);
};
	bool sortClientBySpentAmount(const Client & left, const Client & right);
	bool sortTransactionsByDate(const Transaction & left, const Transaction & right);

#endif