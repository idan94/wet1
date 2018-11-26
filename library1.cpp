//
// Created by idanc on 23/11/2018.
//

#include "library1.h"
#include "TreeMap.h"

void *Init() {
    TreeMap<void*> *DS = new TreeMap<void*>();
    return (void *) DS;
}

StatusType Add(void *DS, int key, void *value, void **node) {
    if (!DS) return INVALID_INPUT;
    return ((TreeMap<void*> *) DS)->addNodeTree(key,&value,node); //TODO:AVL
}

StatusType Find(void *DS, int key, void *value) {
    if (!DS) return INVALID_INPUT;
    return ((TreeMap<void*> *) DS)->findNode(key, (Node<void *> *) value,
                                      ((TreeMap<void*> *) DS)->getRoot());
}

StatusType Delete(void *DS, int key) {
    if (!DS) return INVALID_INPUT;
    return ((TreeMap<void*> *) DS)->deleteNodeTree(key);  //TODO:AVL
}

StatusType DeleteByPointer(void *DS, void *p) {
    if (!DS) return INVALID_INPUT;
    return ((TreeMap<void*> *) DS)->deleteNodeByPtr((Node<void *> *) p);
}

StatusType Size(void *DS, int *n) {
    if (!DS) return INVALID_INPUT;
    ((TreeMap<void*> *) DS)->getSize(n);
    return SUCCESS;
}

void Quit(void **DS) {
    delete DS;
}
