//
// Created by idanc on 23/11/2018.
//

#ifndef WET1_TREEMAP_H
#define WET1_TREEMAP_H

#include <stdexcept>
#include <exception>
#include <iostream>


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
        object = new T(*(a.object));
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

    int fixHeight() {
        int left, right;
        if (!this->getLeftSunPtr()) {
            left = -1;
        } else {
            left = this->getLeftSunPtr()->getHeight();
        }
        if (!this->getRightSunPtr()) {
            right = -1;
        } else {
            right = this->getRightSunPtr()->getHeight();
        }
        this->setHeight(left > right ? left + 1 : right + 1);   //take max
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
        if (leftSunPtr) {
            num++;
        }
        if (rightSunPtr) {
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
        int left = 0, right = 0;
        if (this->getLeftSunPtr()) {
            left = this->getLeftSunPtr()->getHeight();
        }
        if (this->getRightSunPtr()) {
            right = this->getRightSunPtr()->getHeight();
        }
        return (left - right);
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
    void rotate(Node<T> *node) {
        if (node == root) {
            if (node->getBalance() == 2) {        //left_____
                if (node->getLeftSunPtr()->getBalance() >= 0) {   //leftLeft
                    this->root = leftLeftRotate(node);
                    this->root->setFather(nullptr);
                } else {      //leftRight
                    this->root = leftRightRotate(node);
                    this->root->setFather(nullptr);
                }
            } else {                  //right____getBalance==(-2)
                if (node->getRightSunPtr()->getBalance() <= 0) {   //rightRight
                    this->root = rightRightRotate(node);
                    this->root->setFather(nullptr);
                } else {        //rightLeft
                    this->root = rightLeftRotate(node);
                    this->root->setFather(nullptr);
                }
            }
            if (root->getLeftSunPtr()) {
                root->getLeftSunPtr()->fixHeight();
            }
            if (root->getRightSunPtr()) {
                root->getRightSunPtr()->fixHeight();
            }
            root->fixHeight();
        } else {
            Node<T> *father = node->getFatherPtr();
            if (node->getBalance() == 2) {        //left_____
                if (node->getLeftSunPtr()->getBalance() >= 0) {   //leftLeft
                    if (father->getLeftSunPtr() == node) {
                        father->setLeftSun(leftLeftRotate(node));
                        father->getLeftSunPtr()->setFather(father);
                    } else {      //node is the right son of his father
                        father->setRightSun(leftLeftRotate(node));
                        father->getRightSunPtr()->setFather(father);
                    }
                } else {      //leftRight
                    if (father->getLeftSunPtr() == node) {
                        father->setLeftSun(leftRightRotate(node));
                        father->getLeftSunPtr()->setFather(father);
                    } else {      //node is the right son of his father
                        father->setRightSun(leftRightRotate(node));
                        father->getRightSunPtr()->setFather(father);
                    }
                }
            } else {                  //right____getBalance==(-2)
                if (node->getRightSunPtr()->getBalance() <= 0) {    //rightRight
                    if (father->getLeftSunPtr() == node) {
                        father->setLeftSun(rightRightRotate(node));
                        father->getLeftSunPtr()->setFather(father);
                    } else {      //node is the right son of his father
                        father->setRightSun(rightRightRotate(node));
                        father->getRightSunPtr()->setFather(father);
                    }
                } else {        //rightLeft
                    if (father->getLeftSunPtr() == node) {
                        father->setLeftSun(rightLeftRotate(node));
                        father->getLeftSunPtr()->setFather(father);
                    } else {      //node is the right son of his father
                        father->setRightSun(rightLeftRotate(node));
                        father->getRightSunPtr()->setFather(father);
                    }
                }
            }
            if (father->getLeftSunPtr()) {
                father->getLeftSunPtr()->fixHeight();
            }
            if (father->getRightSunPtr()) {
                father->getRightSunPtr()->fixHeight();
            }
            father->fixHeight();
        }
    }

    Node<T> *leftLeftRotate(Node<T> *node) {
        Node<T> *newFather = node->getLeftSunPtr();
        node->setLeftSun(newFather->getRightSunPtr());
        if (node->getLeftSunPtr()) {
            node->getLeftSunPtr()->setFather(node);
        }
        newFather->setRightSun(node);
        node->setFather(newFather);
        return newFather;
    }

    Node<T> *leftRightRotate(Node<T> *node) {
        Node<T> *newFather = node->getLeftSunPtr()->getRightSunPtr();
        node->getLeftSunPtr()->setRightSun(newFather->getLeftSunPtr());
        if (newFather->getLeftSunPtr()) {
            newFather->getLeftSunPtr()->setFather(node->getLeftSunPtr());
        }
        newFather->setLeftSun(node->getLeftSunPtr());
        node->getLeftSunPtr()->setFather(newFather);
        node->setLeftSun(newFather->getRightSunPtr());
        if (newFather->getRightSunPtr()) {
            newFather->getRightSunPtr()->setFather(node);
        }
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
        Node<T> *newFather = node->getRightSunPtr()->getLeftSunPtr();
        node->getRightSunPtr()->setLeftSun(newFather->getRightSunPtr());
        if (newFather->getRightSunPtr()) {
            newFather->getRightSunPtr()->setFather(node->getRightSunPtr());
        }
        newFather->setRightSun(node->getRightSunPtr());
        node->getRightSunPtr()->setFather((newFather));
        node->setRightSun(newFather->getLeftSunPtr());
        if (newFather->getLeftSunPtr()) {
            newFather->getLeftSunPtr()->setFather(node);
        }
        newFather->setLeftSun(node);
        node->setFather(newFather);
        return newFather;
    }

    void inorderPrint() {
        std::cout << "Printing tree In Order: " << std::endl;
        inorderPrintAux(root);
        std::cout << "Done Printing In Order " << std::endl;
    }

    void inorderPrintAux(Node<T> *node) {
        if (!node) return;
        inorderPrintAux(node->getLeftSunPtr());
        std::cout << (node->getKey()) << "  ";
        inorderPrintAux(node->getRightSunPtr());
    }

    StatusType findNode(int key, Node<T> **node) const {
        if (!this->getRoot()) {
            return FAILURE;
        }
        return findNodeAux(key, root, node);
    }

    StatusType findNodeAux(int key, Node<T> *node, Node<T> **wanted) const {
        if (node->getKey() == key) {        //if we found they key
            *wanted = node;
            return SUCCESS;
        }
        if (node->getKey() > key) {
            if (!node->getLeftSunPtr()) {
                *wanted = node;
                return FAILURE;
            }
            return findNodeAux(key, node->getLeftSunPtr(), wanted);
        } else { // case: it->getKey() < key)
            if (!node->getRightSunPtr()) {
                *wanted = node;
                return FAILURE;
            }
            return findNodeAux(key, node->getRightSunPtr(), wanted);
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
        ((Node<T> *) *node)->fixHeight();
        while (((Node<T> *) *node) != root) {
            ((Node<T> *) *node)->fixHeight();
            Node<T> *parent = ((Node<T> *) *node)->getFatherPtr();
            if (parent->getHeight() >= ((Node<T> *) *node)->getHeight() + 1) {
                parent->fixHeight();
                return SUCCESS;
            }
            parent->setHeight(((Node<T> *) node)->getHeight() + 1);
            //parent->fixHeight();
            if (!parent->isBalanced()) {
                rotate(parent);
                return SUCCESS;
            } else {
                // ((Node<T> *) node) = parent;
                *node = (void *) parent;
            }
        }
        return SUCCESS;
    }

    StatusType addNodeTree(int key, T *t, void **node) {
        if (size == 0) {    //if its the first Node of the tree
            try {
                Node<T> *newNode = new Node<T>(key, t);
                root = newNode;
                *node = newNode;
            }
            catch (std::bad_alloc &a) {
                return ALLOCATION_ERROR;
            }
            size++;

            return SUCCESS;
        }
        Node<T> *lastCheck = nullptr;
        StatusType findStatus = findNode(key, &lastCheck);
        if (findStatus == SUCCESS) {
            return FAILURE;
        } else {       //there is no key like this, and we will insert new Node<T>
            *node = new Node<T>(key, t);
            this->size++;
            if (key < lastCheck->getKey()) {
                lastCheck->setLeftSun(((Node<T> *) *node));
                ((Node<T> *) *node)->setFather(lastCheck);
            } else {      //when key> lastCheck->getKey()
                lastCheck->setRightSun(((Node<T> *) *node));
                ((Node<T> *) *node)->setFather(lastCheck);
            }

            return SUCCESS;
        }
    }

    StatusType deleteNodeAvl(int key) {
        Node<T> *node = nullptr;
        if (deleteNodeTree(key, &node)== FAILURE){
            return FAILURE;
        };
        while (1) {
            //step 1: Update h(v)
            node->fixHeight();
            int fatherPrevHeight;
            if (node != root) {
                fatherPrevHeight = node->getFatherPtr()->getHeight();
            }
            //step 2: check balance, rotate if needed and go up
            if (!node->isBalanced()) {
                rotate(node);
                if (node == root) break;
                if (node->getFatherPtr()->getHeight() == fatherPrevHeight) {
                    return SUCCESS;
                }
                node = node->getFatherPtr();
                continue;
            }
            if (node == root) break;
            node = node->getFatherPtr();

            /*if (node->getFatherPtr()->getHeight() == fatherPrevHeight) {
                return SUCCESS;
            } else {      //the height has benn changed and BS is good
                node = node->getFatherPtr();
            }*/
        }
        return SUCCESS;
    }

    StatusType deleteNodeTree(int key, Node<T> **fatherOfDeleted) {
        Node<T> *node = nullptr;
        StatusType findStatus = findNode(key, &node);

        if (findStatus == FAILURE) {
            return FAILURE;
        } else {       //means we found the node
            int numberOfSuns = node->numberOfSuns();
            switch (numberOfSuns) {
                case 0: {          //if node is a leaf
                    Node<T> *father = node->getFatherPtr();
                    if (father->getLeftSunPtr() == node) {
                        father->setLeftSun(nullptr);
                    } else { //means node is the right son of his father.
                        father->setRightSun(nullptr);
                    }
                    *fatherOfDeleted = father;
                    delete node;
                    this->size--;
                    return SUCCESS;
                }
                case 1: { //there is ONE son to node
                    //we will let node's father to point to his son
                    Node<T> *father = node->getFatherPtr();
                    if (father->getLeftSunPtr() == node) {
                        //node is the left son
                        if (node->getLeftSunPtr()) {
                            father->setLeftSun(node->getLeftSunPtr());
                            (father->getLeftSunPtr())->setFather(father);
                        } else { //means node has ONLY right son
                            father->setLeftSun(node->getRightSunPtr());
                            (father->getLeftSunPtr())->setFather(father);
                        }
                    } else {    //node is the right son
                        if (node->getLeftSunPtr()) {
                            father->setRightSun(node->getLeftSunPtr());
                            (father->getRightSunPtr())->setFather(father);
                        } else { //means node has ONLY right son
                            father->setRightSun(node->getRightSunPtr());
                            (father->getRightSunPtr())->setFather(father);
                        }
                    }
                    **fatherOfDeleted = *father;
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
                    return deleteNodeTree(key, fatherOfDeleted);
                }
            }
        }
    }

    StatusType deleteNodeByPtr(Node<T> *node) {
        if (!node) {
            return INVALID_INPUT;
        }
        return deleteNodeAvl(node->getKey());
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
