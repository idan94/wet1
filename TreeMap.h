//
// Created by idanc on 23/11/2018.
//

#ifndef WET1_TREEMAP_H
#define WET1_TREEMAP_H

#include <stdexcept>
#include <exception>


template<class T>
class Node {
    int key;
    T *object;
    Node<T> *fatherPtr;
    Node<T> *leftSunPtr;
    Node<T> *rightSunPtr;
public:
    //Constructors:
    Node<T>() : key(-1),
             object(nullptr),
             fatherPtr(nullptr),
             leftSunPtr(nullptr),
             rightSunPtr(nullptr) {}

    Node<T>(int key, T *t) : key(key),
                          object(nullptr),
                          fatherPtr(nullptr),
                          leftSunPtr(nullptr),
                          rightSunPtr(nullptr) {
        T *newObject = new T(t);
        object = newObject;
    }

    //Destructor:
    ~Node<T>() {
        delete *object;
    }

    //Copy Constructor:
    Node<T>(const Node<T> &a) = default;

    //Assignment Operator:
    Node<T> &operator=(const Node<T> &a)= default;

    int getKey() {
        return this->key;
    }

    T *getObject() {
        return this->object;
    }

    Node<T> *getFatherPtr() {
        return this->fatherPtr;
    };

    Node<T> *getLeftSunPtr() {
        return this->leftSunPtr;
    };

    Node<T> *getRightSunPtr() {
        return this->rightSunPtr;
    };

    void setFather(Node<T> *node) {
        this->fatherPtr = node;
    }

    void setLeftSun(Node<T> *node) {
        this->leftSunPtr = node;
    }

    void setRightSun(Node<T> *node) {
        this->rightSunPtr = node;
    }

    int numberOfSuns() {
        int num = 0;
        if (!leftSunPtr) {
            num++;
        }
        if (!rightSunPtr) {
            num++;
        }
        return num;
    }

    void swap(Node<T> *a) {
        int tempKey = a->getKey();
        void *tempObject = a->getObject();
        a->key = this->getKey();
        a->object = this->getObject();
        this->key = tempKey;
        this->object = tempObject;
    }
};



template<class T>
class TreeMap {
    Node<T> *root;
    int size;
public:
    //Constructor:
    TreeMap() : root(nullptr),
                size(0) {
    }

    //Destructor:
    ~TreeMap() = default;

    //Copy Constructor:
    TreeMap(const TreeMap &a) = default;

    //Assignment Operator:
    TreeMap &operator=(const TreeMap &a)= default;

    StatusType find(int key, Node<T> *node, Node<T> *root) {
        node = root;
        if (!node) {        //if we got into null
            return FAILURE;
        }
        if (node->getKey() == key) {        //if we found they key
            return SUCCESS;
        }
        if (node->getKey() > key) {
            return find(key, node, node->getLeftSunPtr());
        } else { // case: it->getKey() < key)
            return find(key, node, node->getRightSunPtr());
        }
    }

    /*Node<T> *find(int key, Node<T>* node=root) {
        if(!root) {
            return nullptr;
        }
        Node<T>* it=root;
        if (it->getKey() == key) {
            return it;
        }
        if(it->getKey() > key){
            return find(key,(it->getLeftSunPtr()));
        }
        else { // case: it->getKey() < key)
            return find(key,(it->getRightSunPtr()));
        }
    }*/

    StatusType addNode(int key, T *t, void **node) {
        if (size == 0) {    //if its the first Node of the tree
            try {
                Node<T> *newNode = new Node<T>(key, t);
                root = newNode;
            }
            catch (std::bad_alloc &a){
                return ALLOCATION_ERROR;
            }
            return SUCCESS;
        }
        Node<T> *lastCheck = nullptr;
        StatusType findStatus = find(key, lastCheck, root);
        if (findStatus == SUCCESS) {
            return FAILURE;
        } else {       //there is no key like this, and we will insert new Node<T>
            Node<T> newNode(key, t);
            this->size++;
            if (key < lastCheck->getKey()) {
                lastCheck->setLeftSun(&newNode);
            } else {      //when key> lastCheck->getKey()
                lastCheck->setRightSun(&newNode);
            }
            return SUCCESS;
        }
    }

    StatusType deleteNode(int key) {
        Node<T> *node = nullptr;
        StatusType findStatus = find(key, node, root);
        int numberOfSuns = node->numberOfSuns();
        if (findStatus == FAILURE) {
            return FAILURE;
        } else {       //means we found the node
            switch (numberOfSuns) {
                case 0: {          //if node is a leaf
                    Node<T> *father = node->getFatherPtr();
                    if (father->getLeftSunPtr() == node) {
                        father->setLeftSun(nullptr);
                    } else { //means node is the right sun of his father.
                        father->setRightSun(nullptr);
                    }
                    delete node;
                    this->size--;
                    break;
                }
                case 1: { //there is ONE sun to node
                    //we will let node's father to point to his sun
                    Node<T> *father = node->getFatherPtr();
                    if (father->getLeftSunPtr() == node) {
                        //node is the left sun
                        if (node->getLeftSunPtr()) {
                            father->setLeftSun(node->getLeftSunPtr());
                            (father->getLeftSunPtr())->setFather(father);
                        } else { //means node has ONLY right sun
                            father->setLeftSun(node->getRightSunPtr());
                            (father->getLeftSunPtr())->setFather(father);
                        }
                    } else {    //node is the right sun
                        if (node->getLeftSunPtr()) {
                            father->setRightSun(node->getLeftSunPtr());
                            (father->getRightSunPtr())->setFather(father);
                        } else { //means node has ONLY right sun
                            father->setRightSun(node->getRightSunPtr());
                            (father->getRightSunPtr())->setFather(father);
                        }
                    }
                    delete node;
                    this->size--;
                    break;
                }
                case 2: {
                    Node<T> *swappingNode = node->getRightSunPtr();
                    while (swappingNode->getLeftSunPtr()) {
                        swappingNode = swappingNode->getLeftSunPtr();
                    }
                    swappingNode->swap(node);
                    deleteNode(key);
                }
                    break;
            }
        }
    }

    StatusType deleteNodeByPtr(Node<T> *node){
        if (!node){
            return INVALID_INPUT;
        }
        return deleteNode(node->getKey());
    }
    
    StatusType getSize(int *n){
        *n=this->size;
        return SUCCESS;
    }
};

#endif //WET1_TREEMAP_H
