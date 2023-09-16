#include <iostream>
using namespace std;

template <class T> struct Node {
    T valor[5];
    T* toparr = valor+4;
    Node<T>* next;
    Node(T v, Node<T>* n = nullptr) {
        for (T* p=valor;p<valor+5;p++) {
            *p = 0;
        }
        *valor = v;
        next = n;
    }
};

template <class T> class Pila {
public:
    Node<T>* top;
    Pila() { top = NULL; }
    void push(T v);
    void pop();
    void imprimir();
};
template <class T> void Pila<T>::imprimir() {
    for (Node<T>* p = top; p; p = p->next) {
        for (T* p2 = p->valor; p2 < p->valor + 5; p2++) {
            cout << *p2 << ",";
        }
    }
}
template <class T> void Pila<T>::push(T v) {
    if (!top) {
        Node<T>* newNode = new Node<T>(v, NULL);
        top = newNode;
    }
    else if (*(top->toparr)==(0)) {
        int cont = 0;
        for (T* tmp = top->valor; tmp != top->valor + 5; tmp++) {
            if (*(tmp) == 0) {
                *(tmp) = v;
                break;
            }
        }
    }
    else {
        Node<T>* newNode = new Node<T>(v, top);
        top = newNode;
    }
}
 template <class T> void Pila<T>::pop() {
     if (top) {
         if (*(top->valor)==0) {
             Node<T>* aux = top;
             top = top->next;
             delete aux;
         }
         else {
             for (T* tmp = top->valor+4; tmp != top->valor-1; tmp--) {
                 if (*(tmp) != 0) {
                     *(tmp) = 0;
                     break;
                 }
             }
         }
     }
 }

int main() {
    Pila<int> P;
    for (int i = 1; i < 11; i++) {
        P.push(i);
    }
    P.imprimir();
    cout << "\n";
    P.pop();
    P.pop();
    P.pop();
    P.pop();
    P.pop();

    P.imprimir();
}