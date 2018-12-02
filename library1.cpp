//
// Created by idanc on 23/11/2018.
//

#include "library1.h"
#include "TreeMap.h"

template<class T>
void *Init() {
    void * DS;
    try {
        DS =(void*) new TreeMap<void *>();
    }
    catch (std::bad_alloc &a){
        return nullptr;
    }
    return DS;
}

template<class T>
StatusType Add(void *DS, int key, void *value, void **node) {
    if (!DS || !node) return INVALID_INPUT;
    try {
        return ((TreeMap<T> *) DS)->addNodeAvl(key, &value, node);
    }
    catch (std::bad_alloc &a){
        return ALLOCATION_ERROR;
    }
}

template<class T>
StatusType Find(void *DS, int key, void **value) {
    if (!DS || !value) return INVALID_INPUT;
    return ((TreeMap<T> *) DS)->findNode(key, ((Node<T> **)value));
}

template<class T>
StatusType Delete(void *DS, int key) {
    if (!DS) return INVALID_INPUT;
    return ((TreeMap<T> *) DS)->deleteNodeAvl(key);
}

template<class T>
StatusType DeleteByPointer(void *DS, void *p) {
    if (!DS) return INVALID_INPUT;
    return ((TreeMap<T> *) DS)->deleteNodeByPtr((Node<T> *) p);
}

template<class T>
StatusType Size(void *DS, int *n) {
    if (!DS || !n) return INVALID_INPUT;
    ((TreeMap<T> *) DS)->getSize(n);
    return SUCCESS;
}

template<class T>
void Quit(void **DS) {
    delete DS;
}
