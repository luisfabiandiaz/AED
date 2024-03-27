#include <iostream>
using namespace std;

template <class T> struct Node {
    T valor[5];
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
    Node<T>* top=0;
    T* toparr;
    void push(T v);
    T pop();
    void imprimir();
};
template <class T> void Pila<T>::imprimir() {
    for (Node<T>* p = top; p; p = p->next) {
        cout << "{";
        for (T* p2 = p->valor; p2 < p->valor + 5; p2++) {
            cout << *p2 << ",";
        }
        cout << "}";
    }
}
template <class T> void Pila<T>::push(T v) {
    if (!top) {
        Node<T>* newNode = new Node<T>(v, NULL);
        top = newNode;
        toparr = top->valor;
    }
    else if (toparr != top->valor+4) {
        toparr++;
        *toparr = v;
    }
    else {
        Node<T>* newNode = new Node<T>(v, top);
        top = newNode;
        toparr = top->valor;
    }
}
 template <class T> T Pila<T>::pop() {
     T tmp;
     if (top) {
         if (toparr == top->valor) {
             tmp = *toparr;
             Node<T>* aux = top;
             top = top->next;
             toparr = top->valor;
             delete aux;
             return tmp;
         }
         else {
             tmp = *toparr;
             *toparr = 0;
             toparr--;
             return tmp;
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


    P.imprimir();
}