#include <iostream>
using namespace std;

class Node {
public:

    int val;
    Node* next;
    Node(int va) {
        val = va;
        next = NULL;
    }
};


class Pila {
public:
    Node* top;
    Pila() {
        top = NULL;
    }
    void push(int n);
    void pop(int &x);
    void print();
};
void Pila::push(int n) {
    if (!top) {
        top = new Node(n);
    }
    else {
        Node* tmp = top;
        top = new Node(n);
        top->next = tmp;
    }
}

void Pila::pop(int &x) {
    if (!ini) {
        cout << "no hay elementos";
    }
    else if (!ini->next) {
        delete ini;
        ini = NULL;
        end = NULL;
    }
    else {
        ini = ini->next;
        delete ini->prev;
        ini->prev = NULL;
    }
}


void Pila::print() {
    for (Node* p = ini; p; p = p->next) {
        cout << p->val << "///";
    }
    cout << "\n";
}

int main()
{
    Pila p;

    p.print();
    p.print();
    cout << x;
}
