#include <iostream>
using namespace std;

class Node {
public:

    int arr[5];
    Node* next;

    Node() {
        for (int* p = arr; p != arr + 5; p++) {
            *p = 0;
        }
    };
};


class List {
public:
    Node* init;
    Node* END;
    int* end;
    List() {
        init = new Node();
        end = NULL;
        END = init;
    }
    bool add(int n);
    bool del(int n);
    void av1(int* pos, Node* p, bool cm);
    void av2(int* pos, Node* p);
    bool find(int k, int*& pos, Node*& p);
    void print();
};

bool List::find(int k, int*& pos, Node*& p) {
    p = init;
    for (; p;) {
        if (k < *(p->arr + 5) || *(p->arr + 5)==0) {
            for (int* q = p->arr; q != p->arr + 5; q++) {
                if (*q == k) {
                    pos = q;
                    return 1;
                }
                if (*q > k) {
                    pos = q;
                    return 0;
                }
            }
        }
        if (p->next) {
            p = p->next;
        }
        else {
            break;
        }
    }

    if (k > *end) {
        if (end == (p->arr + 4)) {
            pos = NULL;
            return 0;
        }
        else {
            pos = end + 1;
            return 0;
        }
    }
}
void List::av1(int* pos, Node* POS, bool cm) {
    int tmp = *pos;
    *pos = 0;
    bool temp;
    for (int* q = pos + 1; q != POS->arr + 5; q++) {
        int tmp2 = *q;
        *q = tmp;
        tmp = tmp2;
    }
    if (POS->next) {
        for (Node* p = POS->next; p; p = p->next) {
            for (int* q = p->arr; q != p->arr + 5; q++) {
                int tmp2 = *q;
                *q = tmp;
                tmp = tmp2;
            }
        }
    }
    if (!cm) {
        end = end + 1;
    }
}
void List::av2(int* pos, Node* POS) {
    int tmp;
    *pos = 0;
    bool temp;
    for (int* q = pos ; q != POS->arr + 5; q++) {
        tmp = *q;
        *q = *(q + 1);
        *(q + 1) = tmp;
    }
    if (POS->next) {
        *(POS->arr + 4) = *(POS->next->arr);
        *(POS->next->arr) = 0;
    }
    for (Node* p = POS->next; p; p = p->next) {
        for (int* q = p->arr; q != p->arr + 5; q++) {
            tmp = *q;
            *q = *(q + 1);
            *(q + 1) = tmp;
        }
        if (p->next) {
        *(p->arr + 4) = *(p->next->arr);
        *(p->next->arr) = 0;
            }
        }
    
}
bool  List::del(int n) {
    int* pos;
    Node* POS;
    bool cm = 0;
    if (find(n, pos, POS)) {       
        av2(pos, POS);
        end = end - 1;
        return 1;
    }
    else {
        return 0;
    }
}

bool  List::add(int n) {
    if (!end) {
        end = init->arr;
        *end = n;
        return 1;
    }
    int* pos;
    Node* POS;
    bool cm = 0;
    if (!find(n, pos, POS)) {
        if (!pos) {
            END->next = new Node();
            END = END->next;
            end = END->arr;
            *end = n;
            return 1;
        }
        else if (end == END->arr + 4) {
            END->next = new Node();
            END = END->next;
            end = END->arr;
            cm = 1;
        }
        av1(pos, POS, cm);
        *pos = n;
        return 1;
    }
    else {
        return 0;
    }
}
void List::print() {
    for (Node* p = init; p; p = p->next) {
        for (int* q = p->arr; q != p->arr + 5; q++) {
            cout << *q << "////";
        }
    }
}

int main()
{
    List p;
    p.add(5);
    p.add(2);
    p.add(1);
    p.add(7);
    p.add(8);
    p.add(3);
    p.add(10);
    p.add(4);
    p.add(9);
    p.add(6);
    p.add(11);
    p.add(13);
    p.add(12);
    p.del(4);
    p.del(1);
    p.del(13);


    p.print();
}
