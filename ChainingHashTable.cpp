
#include "ChainingHashTable.h"
#include "Hash.h"
#include <string>
#include <stdexcept>
#include <fstream>


using std::string;
using std::ofstream;


ChainingHashTable::ChainingHashTable() : cells(nullptr){
    capacity = 0;
    size = 0;
    cells = new Cell<string, int>*[capacity] {};
}
ChainingHashTable::ChainingHashTable(int cap){
    cells = new Cell<string, int>*[cap] {};
    capacity = cap;
    size = 0;
}
ChainingHashTable::~ChainingHashTable(){
    Cell<string, int>* temp;
    Cell<string, int>* del;
    if(cells != nullptr){
        for(int i = 0; i < capacity; i++){
            temp = cells[i];
            if(temp != nullptr){
                del = temp;
                temp = temp->next;
                delete del;
            }
        }
    }
    if(cells != nullptr){
        delete[] cells;
    }
}

// TODO: include declarations to override the pure vritual functions from the base class
unsigned int ChainingHashTable::hash(std::string key){
    unsigned int hashVal = Hash::PRH24(key);
    return hashVal % capacity;  
}

void ChainingHashTable::insert(std::string key, int val){
    unsigned int hashVal = hash(key);
    if(cells[hashVal] == nullptr){
        cells[hashVal] = new Cell<string, int>(key, val);
        return;    
    }

    Cell<string, int>* temp = cells[hashVal];
    while(temp->next != nullptr){
        if(temp->key == key){
            temp->value = val;
            size++;
            return;
        }
        temp = temp->next;
    }
    if(temp->key == key){
        temp->value = val;
        size++;
        return;
    }
    Cell<string, int>* newCell = new Cell<string, int>(key, val);
    temp->next = newCell;
    size++;
} 

int ChainingHashTable::remove(std::string key){
    unsigned int hashVal = hash(key);
    if(cells[hashVal] != nullptr && cells[hashVal]->key == key){
        Cell<string, int>* del = cells[hashVal];
        unsigned int temp = del->value;
        cells[hashVal] = del->next;
        delete del;
        size--;
        return temp;
    }
    if(cells[hashVal]->next != nullptr){
        Cell<string, int>* curr = cells[hashVal]->next;
        Cell<string, int>* prev = cells[hashVal];
        while(curr != nullptr){
            if(curr->key == key){
                prev->next = curr->next;
                unsigned int temp = curr->value;
                delete curr;
                size--;
                return temp;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    throw std::runtime_error("not found");
} 

int ChainingHashTable::get(std::string key){
    unsigned int hashVal = hash(key);
    if(cells[hashVal] == nullptr)
        return 0;
    Cell<string, int>* temp = cells[hashVal];
    while(temp->key != key){
        if(temp->next == nullptr){
            return 0;
        }
        temp = temp->next;
    }
    return temp->value;
}

void ChainingHashTable::printAll(std::string filename){
    ofstream file;
    file.open(filename);
    Cell<string, int>* temp = nullptr;
    for(int i = 0; i < capacity; i++){
        if(cells[i] != nullptr){
            temp = cells[i];
        }
        while(temp != nullptr){
            file << temp->key << " " << temp->value << std::endl;
            temp = temp->next;
        }
    }
    file.close();
}