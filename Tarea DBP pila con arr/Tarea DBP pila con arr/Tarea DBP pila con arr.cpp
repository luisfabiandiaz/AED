#include <iostream>
using namespace std;

template <class T> struct Node {
    T valor[5];
    T* toparr = valor;
    Node<T>* next;
    Node(T v, Node<T>* n = nullptr) {
        *toparr = v;
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
    for (Node<T>* p = head; p != end; p = head->next) {
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
    else if ((top->toparr) + 4 == NULL) {
        for (; top->p == top->valor + 4; end->p++) {
            if (end->p == NULL) {
                *(end->p) = v;
                break;
            }
        }
    }
    else {
        Node<T>* newNode = new Node<T>(v, NULL);
        end->next = newNode;
        end = newNode;
    }
}
// template <class T> void Pila<T>::pop() {
//     if (head) {
//         Node<T>* aux = head;
//         head = head->next;
//         delete aux;
//     }
// }

int main() {
    Pila<int> P;
    for (int i = 0; i < 10; i++) {
        P.push(i);
    }
    P.imprimir();
}