#include <iostream>
using namespace std;

template <class T> struct Node {
    T valor[5];
    Node<T>* next;
    T* mayorarr;
    Node(T v, Node<T>* n = nullptr) {
        for (T* p = valor; p < valor + 5; p++) {
            *p = 0;
        }
        *valor = v;
        next = n;
        mayorarr = &valor[0];
    }
};

template <class T> class Cola {
public:
    Node<T>* head = 0;
    T* headarr;
    void insert(T v);
    void remove(T v);
    bool find(Node<T>*& pos, T v);
    void imprimir();
    bool vacio() { return !head; }
};
template <class T> void Cola<T>::imprimir() {
    for (Node<T>* p = head; p; p = p->next) {
        cout << "{";
        for (T* p2 = p->valor; p2 < p->valor + 5; p2++) {
            cout << *p2 << ",";
        }
        cout << "}";
    }
}
template <class T> bool Cola<T>::find(Node<T>* &pos, T v) {
    for (pos = head; pos; pos = pos->next) {
        T* p2 = pos->valor;
        if (*p2 < v < *(pos->mayorarr)) {
            T* p = pos->valor;
            for (; *p < v; p++) {
            }
            return (*p == v);
        }
    }
    return 0;
}

template <class T> void Cola<T>::insert(T v) {
    Node<T>* p;
    if (!head) {
        Node<T>* newNode = new Node<T>(v, NULL);
        head = newNode;
    }
    else if (find(p, v)) {
    
        
    }
    for (Node<T>* p = head; p->next ; p = p->next) {

    }
}
template <class T> void Cola<T>::remove(T v) {
    T tmp;
    if (head) {
        if (headarr == head->valor + 4) {
            tmp = *headarr;
            Node<T>* aux = head;
            head = head->next;
            headarr = head->valor;
            delete aux;
            return tmp;
        }
        else {
            tmp = *headarr;
            *headarr = 0;
            headarr++;
            return tmp;
        }
    }
}

int main() {
    Cola<int> P;
    for (int i = 1; i < 11; i++) {
        P.insert(i);
    }
    P.imprimir();
    cout << "\n";

    P.imprimir();
}