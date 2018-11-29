
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "library1.h"
#include <iostream>
#include "TreeMap.h"


int main(int argc, const char**argv) {
    using std::cout;
    using std::endl;
    std::cout << "Hello123" << std::endl;
    TreeMap<char> myMap;
    void *temp = malloc(sizeof(void*));
    char a='a', b ='b', c = 'c', d='d', e='e';
    char *ptrA= &a;
    myMap.addNodeAvl(9,ptrA,&temp);
    myMap.addNodeAvl(14,&b,&temp);
    myMap.addNodeAvl(4,&c,&temp);
    myMap.addNodeAvl(12,&d,&temp);
    myMap.addNodeAvl(19,&e,&temp);
    std::cout << "end" << endl;
    return 0;
}