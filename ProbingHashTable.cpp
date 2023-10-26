
#include "ProbingHashTable.h"
#include "Hash.h"
#include <string>
#include <stdexcept>
#include <fstream>


using std::string;
using std::ofstream;

ProbingHashTable::ProbingHashTable(){
    capacity = 0;
    size = 0;
}
ProbingHashTable::ProbingHashTable(int cap){
    cells = new Cell<string, int>[cap];
    capacity = cap;
    size = 0;
}
ProbingHashTable::~ProbingHashTable(){
    capacity = 0;
    size = 0;
    delete[] cells;
}
// TODO: include declarations to override the pure vritual functions from the base class
unsigned int ProbingHashTable::hash(std::string key){
    unsigned int hashVal = Hash::PRH24(key);
    return hashVal % capacity;  
}

void ProbingHashTable::insert(std::string key, int val){ //could fail if the entire table was full
    unsigned int hashVal = hash(key);
    while(cells[hashVal].key != ""){
        if(cells[hashVal].key == key){
            cells[hashVal].value = val;
            size++;
            return;
        }
        hashVal = (hashVal + 1) % capacity;
    }
    cells[hashVal].key = key;
    cells[hashVal].value = val;
    size++;
} 

int ProbingHashTable::remove(std::string key){
    unsigned int hashVal = hash(key);
    if(cells[hashVal].key == key){
        cells[hashVal].key = "";
        unsigned int temp = cells[hashVal].value;
        cells[hashVal].value = 0;
        size--;
        return temp;
    }
    while(cells[hashVal].key != key){
        hashVal = (hashVal + 1) % capacity;
        if(cells[hashVal].key == ""){
            throw std::runtime_error("not found");
        }
        else if(cells[hashVal].key == key){
            cells[hashVal].key = "";
            unsigned int temp = cells[hashVal].value;
            cells[hashVal].value = 0;
            size--;
            return temp;
        }
    }
    return 0;
} 

int ProbingHashTable::get(std::string key){
    unsigned int hashVal = hash(key);

    while(cells[hashVal].key != key){
        if(cells[hashVal].key == ""){
            return 0;
        }
        hashVal = (hashVal + 1) % capacity;
    }
    return cells[hashVal].value;
}

void ProbingHashTable::printAll(std::string filename){
    ofstream file;
    file.open(filename);
    for(int i = 0; i < capacity; i++){
        if(cells[i].key != ""){
            file << cells[i].key << " " << cells[i].value << std::endl;
        }
    }
    file.close();
}