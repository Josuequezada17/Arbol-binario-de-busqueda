#ifndef BTREE_HPP_INCLUDED
#define BTREE_HPP_INCLUDED

#include <exception>
#include <string>
#include <fstream>

using namespace std;

template <class T>
class BTree {
    class Node;
  public:
    typedef Node* Position;
  ///Nodo
  private:
    class Node {
      private:
        T* dataPtr;
        Position right;
        Position left;
        int height;

      public:
        class Exception : public std::exception {
          private:
            std::string msg;
          public:
            explicit Exception(const char* message) : msg(message) { }
            explicit Exception(const std::string& message) : msg(message) { }
            virtual ~Exception() throw () { }
            virtual const char* what() const throw () {
                return msg.c_str();
            }
        };
      public:
        Node();
        Node(const T&);

        T getData() const;
        Position& getRight();
        Position& getLeft();
        T* getDataPtr() const;

        void setDataPtr(T*);
        void setData(const T&);
        void setRight(Position&);
        void setLeft(Position&);
    };

  public:
    class Exception : public std::exception {
      private:
        std::string msg;
      public:
        explicit Exception(const char* message) : msg(message) { }
        explicit Exception(const std::string& message) : msg(message) { }
        virtual ~Exception() throw () { }
        virtual const char* what() const throw () {
            return msg.c_str();
        }
    };

    ///Arbol
  private:
    Position root;
    std::ofstream myFile;

    void copyAll(Position&);

    Position& findData(Position&, const T&);

    void insertData(Position&, const T&);
    void deleteAll(Position&);
    void deleteData(Position&, const T&);

    bool isLeaf(Position&);

    int getHeight(Position&);

    Position& getLowest(Position&);
    Position& getHighest(Position&);

    std::string parsePreOrder(Position&);
    std::string parseInOrder(Position&);
    std::string parsePostOrder(Position&);

    std::string toString(Position&);

    void writeToDisk(const Position&);

  public:
    BTree();
    BTree(const BTree&);
    ~BTree();

    bool isEmpty() const;

    void insertData(const T&);
    void deleteData(const T&);

    Position& getLowest();
    Position& getHighest();

    int getHeight();

    Position& findData(const T&);

    T retrieve(Position&) const;

    std::string toString();

    std::string parsePreOrder();
    std::string parseInOrder();
    std::string parsePostOrder();

    void deleteAll();

    BTree& operator = (const BTree&);

    void writeToDisk();
    void readFromDisk();
};

///Implementacion nodo

template<class T>
BTree<T>::Node::Node() : dataPtr(nullptr), right(nullptr), left(nullptr), height(1) { }

template<class T>
BTree<T>::Node::Node(const T& e) : dataPtr(new T(e)), right(nullptr), left(nullptr), height(1) {
    if(dataPtr == nullptr) {
        throw Exception("Memoria no disponible, BTree<T>::Node::Node");
    }
}

template<class T>
T BTree<T>::Node::getData() const {
    if(dataPtr == nullptr) {
        throw Exception("Dato inexistente, T BTree<T>::Node::getData");
    }
    return *dataPtr;
}

template<class T>
T* BTree<T>::Node::getDataPtr() const {
    return dataPtr;
}

template<class T>
typename BTree<T>::Position& BTree<T>::Node::getRight() {
    return right;
}

template<class T>
typename BTree<T>::Position& BTree<T>::Node::getLeft() {
    return left;
}

template<class T>
void BTree<T>::Node::setData(const T& e) {
    if(dataPtr == nullptr) {
        if((dataPtr = new T(e)) == nullptr) {
            throw Exception("Memoria no disponible, BTree<T>::Node::setData");
        }
    } else {
        *dataPtr = e;
    }
}

template<class T>
void BTree<T>::Node::setDataPtr(T* p) {
    dataPtr = p;
}

template<class T>
void BTree<T>::Node::setRight(Position& p) {
    right = p;
}

template<class T>
void BTree<T>::Node::setLeft(Position& p) {
    left = p;
}

///Implementacion arbol

template<class T>
BTree<T>::BTree() : root(nullptr) { }

template<class T>
BTree<T>::BTree(const BTree<T>& t) : BTree() {
    copyAll(t);
}

template<class T>
BTree<T>::~BTree() {
    deleteAll();
}

template<class T>
bool BTree<T>::isEmpty() const {
    return root == nullptr;
}

template<class T>
void BTree<T>::insertData(const T& e) {
    insertData(root, e);
}

template<class T>
void BTree<T>::insertData(Position& r, const T& e) {
    if(r == nullptr) {
        try {
            if((r = new Node(e)) == nullptr) {
                throw Exception("Memoria no disponible, insertData");
            }
        } catch(typename Node::Exception ex) {
            throw Exception(ex.what());
        }
        return;
    }

    else {
        if(e < r->getData()) {
            insertData(r->getLeft(), e);
        }

        else {
            insertData(r->getRight(), e);
        }
    }
}

template<class T>
void BTree<T>::deleteData(const T& e) {
    deleteData(root, e);
}

template<class T>
void BTree<T>::deleteData(Position& r, const T& e) {
    if(r == nullptr) {
        return;
    }

    if(r->getData() == e) {
        if(isLeaf(r)) {
            delete r;
            r = nullptr;
            return;
        }

        if(r->getLeft() != nullptr and r->getRight() != nullptr) {
            T myData(getHighest(r->getLeft())->getData());

            deleteData(r, myData);
            r->setData(myData);

            return;
        }

        Position aux(r->getRight() == nullptr ? aux = r->getLeft() : aux = r->getRight());

        delete r;

        r = aux;
    }

    if(e < r->getData()) {
        deleteData(r->getLeft(), e);
    }

    else {
        deleteData(r->getRight(), e);
    }
}

template<class T>
typename BTree<T>::Position& BTree<T>::getLowest() {
    return getLowest(root);
}

template<class T>
typename BTree<T>::Position& BTree<T>::getLowest(Position& r) {
    if(r == nullptr or r->getLeft() == nullptr) {
        return r;
    }

    return getLowest(r->getLeft());
}

template<class T>
typename BTree<T>::Position& BTree<T>::getHighest() {
    return getHighest(root);
}

template<class T>
typename BTree<T>::Position& BTree<T>::getHighest(Position& r) {
    if(r == nullptr or r->getRight() == nullptr) {
        return r;
    }

    return getHighest(r->getRight());
}

template<class T>
bool BTree<T>::isLeaf(Position& r) {
    return r != nullptr and r->getLeft() == r->getRight();
}

template<class T>
int BTree<T>::getHeight() {
    return getHeight(root);
}

template<class T>
int BTree<T>::getHeight(Position& p) {
    if(p == nullptr) {
        return 0;
    }

    int leftHeight(getHeight(p->getLeft()));
    int rightHeight(getHeight(p->getRight()));

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

template<class T>
typename BTree<T>::Position& BTree<T>::findData(Position& r, const T& e) {
    if(r == nullptr or r->getData() == e) {
        return r;
    }

    if(e < r->getData()) {
        return findData(r->getLeft(), e);
    }

    else {
        return findData(r->getRight(), e);
    }
}

template<class T>
typename BTree<T>::Position& BTree<T>::findData(const T& e) {
    return findData(root, e);
}

template<class T>
T BTree<T>::retrieve(Position& r) const {
    return r->getData();
}

template<class T>
void BTree<T>::copyAll(Position& p) {
    if(p == nullptr) {
        return;
    }

    insertData(p->getData());
    copyAll(p->getLeft());
    copyAll(p->getRight());
}

template<class T>
void BTree<T>::deleteAll() {
    deleteAll(root);
}

template<class T>
void BTree<T>::deleteAll(Position& r) {
    if(r == nullptr) {
        return;
    }

    deleteAll(r->getLeft());
    deleteAll(r->getRight());
    delete r;

    r = nullptr;
}

template<class T>
BTree<T>& BTree<T>::operator = (const BTree& t) {
    Position aux(t.root);
    deleteAll();

    copyAll(aux);
    return *this;
}

template<class T>
string BTree<T>::parsePreOrder() {
    return parsePreOrder(root);
}

template<class T>
string BTree<T>::parsePreOrder(Position& r) {
    string result;
    if(r == nullptr) {
        return result;
    }

    result+= r->getData().toString();
    result+= '\n';
    result+= parsePreOrder(r->getLeft());
    result+= parsePreOrder(r->getRight());
}

template<class T>
string BTree<T>::parseInOrder() {
    return parseInOrder(root);
}

template<class T>
string BTree<T>::parseInOrder(Position& r) {
    string result;
    if(r == nullptr) {
        return result;
    }

    result+= parseInOrder(r->getLeft());
    result+= r->getData().toString();
    result+= '\n';
    result+= parseInOrder(r->getRight());
}

template<class T>
string BTree<T>::parsePostOrder() {
    return parsePostOrder(root);
}

template<class T>
string BTree<T>::parsePostOrder(Position& r) {
    string result;
    if(r == nullptr) {
        return result;
    }

    result+= parsePostOrder(r->getLeft());
    result+= parsePostOrder(r->getRight());
    result+= r->getData().toString();
    result+= '\n';
}

template<class T>
string BTree<T>::toString() {
    return toString(root);
}

template<class T>
string BTree<T>::toString(Position& r) {
    string result;

if(r == nullptr){
    return result;
}

    result+= r->getData().toString();
    result+= '\n';
    result+= toString(r->getLeft());
    result+= toString(r->getRight());

return result;

}

template <class T>
void BTree<T>::writeToDisk() {
    string fileName("file01.txt");
    myFile.open(fileName, ios_base::trunc);

    if(!myFile.is_open()) {
        throw Exception("No se pudo abrir " + fileName + " para escritura");
    }

    writeToDisk(root);
    myFile.close();
}

template <class T>
void BTree<T>::writeToDisk(const Position& r) {
    if(r == nullptr) {
        return;
    }

    myFile << r->getData();
    writeToDisk(r->getLeft());
    writeToDisk(r->getRight());
}

template <class T>
void BTree<T>::readFromDisk() {
    ifstream myFile;
    string fileName("file01.txt");

    myFile.open(fileName);

    if(!myFile.is_open()) {
        throw Exception("No se pudo abrir " + fileName + " para lectura");
    }

    T myObjet;
    deleteAll();

    while((myFile >> myObjet) and myFile.ignore()) {
        insertData(myObjet);
    }

    myFile.close();
}

#endif // BTREE_HPP_INCLUDED
