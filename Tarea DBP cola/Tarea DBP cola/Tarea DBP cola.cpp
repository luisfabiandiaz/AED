#include <iostream>
using namespace std;

template <class T> struct Node {
    T valor;
    Node<T>* next;
    Node(T v, Node<T>* n = nullptr) {
        valor = v;
        next = n;
    }
};

template <class T> class Cola {
public:
    Node<T>* head;
    Node<T>* tail;
    Cola() {
        head = NULL;
        tail = NULL;
    }
    void push(T v);
    T pop();
    bool vacio() { return !head; }
};
template <class T> void Cola<T>::push(T v) {
    if (!head) {
        Node<T>* newNode = new Node<T>(v, NULL);
        head = newNode;
        tail = newNode;
    }
    else {
        Node<T>* newNode = new Node<T>(v, NULL);
        tail->next = newNode;
        tail = newNode;
    }
}
template <class T> T Cola<T>::pop() {
    T tmp = 0;
    if (head) {
        Node<T>* aux = head;
        head = head->next;
        delete aux;
    }
    return tmp;
}

int main() {
    Cola<int> P;
    for (int i = 0; i < 10; i++) {
        P.push(i);
    }
    while (!P.vacio()) {
        cout << P.pop();
    }
    return 0;
}