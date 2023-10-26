
#include "Block.h"
#include "Hash.h"
#include<iostream>


using namespace std;

using std::getline;
using std::cout;
using std::cin;
using std::endl;
using std::string;


int main() {

    std::string transaction;
    Block* prev = nullptr;
    Block* bl = nullptr;
    getline(cin, transaction);
    while (!transaction.empty()){
        bl = new Block(transaction, prev);
        bl->getNonce();
        prev = bl;
        getline(cin, transaction);
    }

    while(bl != nullptr){
        cout << *bl;
        prev = bl;
        bl = bl->get_prev();
        delete prev;
    }




    return 0;
}