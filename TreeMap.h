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
    int height;
public:
    //Constructors:
    Node<T>() : key(-1),
                object(nullptr),
                fatherPtr(nullptr),
                leftSunPtr(nullptr),
                rightSunPtr(nullptr),
                height(0) {}

    Node<T>(int key, T *t) : key(key),
                             object(nullptr),
                             fatherPtr(nullptr),
                             leftSunPtr(nullptr),
                             rightSunPtr(nullptr), height(0) {
        T *newObject = new T(*t);
        object = newObject;
    }

    //Destructor:
    ~Node<T>() {
        delete ((T *) object);
    }

    //Copy Constructor:
    Node<T>(const Node<T> &a) : key(a.key),
                                object(a.object),
                                fatherPtr(nullptr),
                                leftSunPtr(nullptr),
                                rightSunPtr(nullptr), height(a.height) {}

    //Assignment Operator:
    Node<T> &operator=(const Node<T> &a) {
        if (this == &a) return *this;
        key = a.key;
        object = new T(a.object);
        fatherPtr = nullptr;
        leftSunPtr = nullptr;
        rightSunPtr = nullptr;
        height = a.height;
        return *this;
    }

    int getKey() const {
        return this->key;
    }

    T *getObject() const {
        return this->object;
    }

    int getHeight() const {
        return this->height;
    }

    void setHeight(int newHeight) {
        this->height = newHeight;
    }

    Node<T> *getFatherPtr() const {
        return this->fatherPtr;
    };

    Node<T> *getLeftSunPtr() const {
        return this->leftSunPtr;
    };

    Node<T> *getRightSunPtr() const {
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

    int numberOfSuns() const {
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
        T *tempObject = a->getObject();
        a->key = this->getKey();
        a->object = this->getObject();
        this->key = tempKey;
        this->object = tempObject;
    }

    int getBalance() const {
        return (getLeftSunPtr()->getHeight() - getRightSunPtr()->getHeight());
    }

    bool isBalanced() const {
        return (this->getBalance() <= 1 && this->getBalance() >= (-1));
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

    static void postOrderDelete(Node<T> *node) {
        if (!node) {
            return;
        }
        postOrderDelete(node->getLeftSunPtr());
        postOrderDelete(node->getRightSunPtr());
        delete node;
    }

    //Destructor:
    ~TreeMap() {
        postOrderDelete(root);
    }

    static void preOrderCopy(Node<T> *newNode, Node<T> *node) {
        if (!newNode) {
            node = nullptr;
        } else {
            newNode = node;
            preOrderCopy(newNode->getLeftSunPtr(), node->getLeftSunPtr());
            preOrderCopy(newNode->getRightSunPtr(), node->getRightSunPtr());
        }
    }

    //Copy Constructor:
    TreeMap(const TreeMap &a) : root(nullptr),
                                size(a.size) {
        preOrderCopy(root, a.root);
    }

    //Assignment Operator:
    TreeMap &operator=(const TreeMap &a)= default;

    //Rotations:
    void Rotate(Node<T> *node) {
        if (node->getBalance() == 2) {        //left_____
            if (node->getLeftSunPtr()->getBalance() >= 0) {   //leftLeft
                leftLeftRotate(node);
            } else {      //leftRight
                leftRightRotate(node);
            }
        } else {                  //right____
            if (node->getRightSunPtr()->getBalance() <= 0) {    //rightRight
                rightRightRotate(node);
            } else {        //rightLeft
                rightLeftRotate(node);
            }
        }
    }

    Node<T> *leftLeftRotate(Node<T> *node) {
        Node<T> *newFather = node->getLeftSunPtr();
        node->setLeftSun(newFather->getRightSunPtr());
        node->getLeftSunPtr()->setFather(node);
        newFather->setRightSun(node);
        node->setFather(newFather);
        return newFather;
    }

    Node<T> *leftRightRotate(Node<T> *node) {
        Node<T> *newFather = node->getLeftSunPtr()->getRightSunPtr();
        node->getLeftSunPtr()->setRightSun(newFather->getLeftSunPtr());
        newFather->getLeftSunPtr()->setFather(node->getLeftSunPtr());
        newFather->setLeftSun(node->getLeftSunPtr());
        node->getLeftSunPtr()->setFather(newFather);
        node->setLeftSun(newFather->getRightSunPtr());
        newFather->getRightSunPtr()->setFather(node);
        newFather->setRightSun(node);
        node->setFather(newFather);
        return newFather;
    }

    Node<T> *rightRightRotate(Node<T> *node) {
        Node<T> *newFather = node->getRightSunPtr();
        node->setRightSun(newFather->getLeftSunPtr());
        node->getRightSunPtr()->setFather(node);
        newFather->setRightSun(node);
        node->setFather(newFather);
        return newFather;
    }

    Node<T> *rightLeftRotate(Node<T> *node) {
        Node<T> *newFather = node->getLeftSunPtr()->getRightSunPtr();
        node->getRightSunPtr()->setLeftSun(newFather->getRightSunPtr());
        newFather->getRightSunPtr()->setFather(node->getRightSunPtr());
        newFather->setRightSun(node->getRightSunPtr());
        node->getRightSunPtr()->setFather((newFather));
        node->setRightSun(newFather->getLeftSunPtr());
        newFather->getLeftSunPtr()->setFather(node);
        newFather->setLeftSun(node);
        node->setFather(newFather);
        return newFather;
    }

    StatusType findNode(int key, Node<T> *node, Node<T> *root) const {
        node = root;
        if (!node) {        //if we got into null
            return FAILURE;
        }
        if (node->getKey() == key) {        //if we found they key
            return SUCCESS;
        }
        if (node->getKey() > key) {
            return findNode(key, node, node->getLeftSunPtr());
        } else { // case: it->getKey() < key)
            return findNode(key, node, node->getRightSunPtr());
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
    StatusType addNodeAvl(int key, T *t, void **node) {
        addNodeTree(key, t, node);
        ((Node<T> *) node)->setHeight(0);
        while (((Node<T> *) node) != root) {
            Node<T> *parent = ((Node<T> *) node)->getFatherPtr();
            if (parent->getHeight() >= ((Node<T> *) node)->getHeight()) {
                return SUCCESS;
            }
            parent->setHeight(((Node<T> *) node)->getHeight() + 1);
            if (!parent->isBalanced()) {
                Rotate(parent);
                return SUCCESS;
            } else {
                ((Node<T> *) node) = parent;
            }
        }

    }

    StatusType addNodeTree(int key, T *t, void **node) {
        if (size == 0) {    //if its the first Node of the tree
            try {
                Node<T> *newNode = new Node<T>(key, t);
                root = newNode;
            }
            catch (std::bad_alloc &a) {
                return ALLOCATION_ERROR;
            }
            return SUCCESS;
        }
        Node<T> *lastCheck = nullptr;
        StatusType findStatus = findNode(key, lastCheck, root);
        if (findStatus == SUCCESS) {
            return FAILURE;
        } else {       //there is no key like this, and we will insert new Node<T>
            Node<T> newNode(key, t);
            this->size++;
            if (key < lastCheck->getKey()) {
                lastCheck->setLeftSun(&newNode);
                newNode.setFather(lastCheck);
            } else {      //when key> lastCheck->getKey()
                lastCheck->setRightSun(&newNode);
                newNode.setFather(lastCheck);
            }
            return SUCCESS;
        }
    }

    StatusType deleteNodeAvl(int key) {

    }

    StatusType deleteNodeTree(int key) {
        Node<T> *node = nullptr;
        StatusType findStatus = findNode(key, node, root);
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
                    return SUCCESS;
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
                    return SUCCESS;
                }
                case 2: {
                    Node<T> *swappingNode = node->getRightSunPtr();
                    while (swappingNode->getLeftSunPtr()) {
                        swappingNode = swappingNode->getLeftSunPtr();
                    }
                    swappingNode->swap(node);
                    return deleteNodeTree(key);
                }
            }
        }
    }

    StatusType deleteNodeByPtr(Node<T> *node) {
        if (!node) {
            return INVALID_INPUT;
        }
        return deleteNodeTree(node->getKey());
    }

    StatusType getSize(int *n) const {
        *n = this->size;
        return SUCCESS;
    }

    Node<T> *getRoot() const {
        return root;
    }
};

#endif //WET1_TREEMAP_H
