#include <iostream>
#include <string>
#include <vector>

#include "Supermarket.h"
#include "Menus.h"
#include "utils.h"


int main(){
  string storeName, clientsFilename, productsFilename, transactionsFilename;

  // pede a informacao sobre o nome da loja e os 3 ficheiros com
  // informacoo de clientes, produtos e transacoes
  if(! readInitialInformation(storeName, clientsFilename, productsFilename, transactionsFilename))
    return(-1);

  // cria uma loja
  Supermarket supermarket(storeName, clientsFilename, productsFilename, transactionsFilename);

  showWelcome();
  cout << " Information of store " << storeName << " of Supermarket++:" << endl << endl;
  cout << supermarket << endl;  // mostra estatisticas da loja

  cin.get();

  mainMenuOptions(supermarket); // menu inicial com as grandes opcoes
				// que implementam as funcioanlidades
				// disonibilizadas
  cin.get();
  return 0;
}
