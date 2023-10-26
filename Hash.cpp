#include "Hash.h"
#include <string>
// TODO: implement the hash function (remember to namespace to Hash::)

unsigned int Hash::PRH24(std::string s){
    unsigned int hash = 0;
    unsigned int p = 137;
    unsigned int factor = 1;
    unsigned int m = 16777215;
    for (std::string::iterator it = s.begin(); it != s.end(); it++) {
        hash += int(*it) * factor % m;
        factor = factor * p % m;
    }
    return hash % m;
}