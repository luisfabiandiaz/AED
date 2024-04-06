#include <iostream>
using namespace std;

class Node {
public:

    int val;
    Node* next;
    Node* prev;
    Node(int va,Node* n, Node* p) {
        val = va;
        next = n;
        prev = p;
    }
};


class List {
public:
    Node* ini;
    Node* end;
    List() {
        ini = NULL;
        end = NULL;
    }
    void pushfront(int n);
    void pushback(int n);
    void popfront();
    void popback();
    void print();
    int& operator[](int n);
};
void List::pushfront(int n) {
    if (!ini) {
        ini = new Node(n,NULL,NULL);
        end = ini;
    }
    else {
        end->next = new Node(n, NULL, end);
        end = end->next;
    }
}
void List::pushback(int n) {
    if (!ini) {
        ini = new Node(n, NULL, NULL);
        end = ini;
    }
    else {
        ini->prev = new Node(n, ini, NULL);
        ini = ini->prev;
    }
}
void List::popback() {
    if (!ini) {
        cout << "no hay elementos";
    }
    else if(!ini->next){
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
void List::popfront() {
    if (!ini) {
        cout << "no hay elementos";
    }
    else if (!ini->next) {
        delete ini;
        ini = NULL;
        end = NULL;
    }
    else {
        end = end->prev;
        delete end->next;
        end->next = NULL;
    }
}

void List::print() {
    for (Node* p = ini;p;p=p->next) {
        cout << p->val << "///";
    }
    cout <<"\n";
}
int& List::operator[](int n) {
    Node* p = ini;
    for (int i=0; i!=n; i++) {
        if (!p) {
            cout << "te pasaste";
            break;
        }
         p = p->next;
    }
    return p->val;
}
int main()
{
    List p;
    p.pushfront(3);
    p.pushback(12);
    p.pushfront(7);
    p.pushfront(32);
    p.pushfront(2);
    p.pushfront(13);
    p.pushfront(26);
    p.pushfront(4);
    p.popfront();
    p.popback();
    p.print();
    p[3] = 5;
    int x = p[2];
    p.print();
    cout << x;
}
