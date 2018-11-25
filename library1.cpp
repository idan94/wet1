//
// Created by idanc on 23/11/2018.
//

#include "library1.h"
#include "TreeMap.h"
template <class T>
void *Init() {
    TreeMap<T>* DS = new TreeMap<T>();
    return(void*)DS;
}

StatusType Add(void *DS, int key, void *value, void **node){

}

StatusType Find(void *DS, int key, void *value);

StatusType Delete(void *DS, int key);

StatusType DeleteByPointer(void *DS, void *p);

StatusType Size(void *DS, int *n);

void Quit(void **DS);
