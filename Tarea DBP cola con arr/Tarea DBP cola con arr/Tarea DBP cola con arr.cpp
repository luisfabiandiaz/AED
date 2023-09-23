#include <iostream>
using namespace std;

template <class T> struct Node {
    T valor[5];
    Node<T>* next;
    Node(T v, Node<T>* n = nullptr) {
        for (T* p = valor; p < valor + 5; p++) {
            *p = 0;
        }
        *valor = v;
        next = n;
    }
};

template <class T> class Cola {
public:
    Node<T>* head = 0;
    Node<T>* tail = 0;
    T* headarr;
    T* tailarr;
    void push(T v);
    T pop();
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
template <class T> void Cola<T>::push(T v) {
    if (!head) {
        Node<T>* newNode = new Node<T>(v, NULL);
        head = newNode;
        tail = newNode;
        tailarr = tail->valor;
        headarr = tail->valor;
    }
    else if (tailarr != tail->valor + 4) {
        tailarr++;
        *tailarr = v;
    }
    else {
        Node<T>* newNode = new Node<T>(v, NULL);
        tail->next = newNode;
        tail = newNode;
        tailarr = tail->valor;
    }
}
template <class T> T Cola<T>::pop() {
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
        P.push(i);
    }
    P.imprimir();
    cout << "\n";
    cout << P.pop() << "\n";
    cout << P.pop() << "\n";
    cout << P.pop() << "\n";
    cout << P.pop() << "\n";

    P.imprimir();
}