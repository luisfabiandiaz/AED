#include <iostream>
using namespace std;
//ej 1
class Pila {
public:
    int elem[10];
    int* top = NULL;
    bool Push(int a);
    bool Pop(int& a);
    Pila() {
        for (int* p = elem; p < elem + 10; p++) {
            *p = 0;
        }
    }
};
bool Pila::Push(int a) {
    for (int* p = elem; p < elem + 10; p++) {
        if (*p == 0) {
            *p = a;
            return 1;
        }
    }
    return 0;
}
bool Pila::Pop(int& a) {

    for (int* p = elem + 10; p > elem; p--) {
        if (*p != 0) {
            a = *p;
            *p = 0;
            return 1;
        }
    }
    return 0;
}
//el pop regresa lo borrado y ordena la lista



//ej 2
//arr con n elemnetos ordenados de men a mayor
///binbus encuentra la key y la devuelve en pos
bool BinBus(int* ini, int* fin, int*& pos, int key) {
    int* med = ini;
    med += (fin - ini) / 2;
    while (*ini <= *fin) {
        if (*med < key) {
            ini = med;
            med += ((fin - ini) + 1) / 2 ;
        }
        else if (*med == key)
        {
            cout << "Se encontro la posicion" << "\n";
            pos = med;
            return 1;
        }
        else {
            fin = med;
            med -= ((fin - ini) + 1) / 2;
        }
        if (*ini == *fin) {
            cout << key << " no se encontro" << "\n";
            return 0;
        }
    }
}

int main()
{
    int arr[15] = { 10,20,30,40,50,60,70,80,90,100,110,120,130,140,150 };
    int* pos;
    BinBus(arr, arr + 14, pos, 150);
    cout << "pos: " << *pos;




    int a = 0;
    Pila q;
    q.Push(10);
    q.Push(11);
    q.Push(12);
    q.Push(13);
    q.Push(14);
    q.Pop(a);
    q.Pop(a);
    q.Pop(a);
    q.Pop(a);
    //cout <<"a: " << a;
}

