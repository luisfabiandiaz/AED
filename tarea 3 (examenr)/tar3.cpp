#include <iostream>
using namespace std;
class XVector
{
public:
    int size;
    int** map;
    int size_map, size_vec;
    int** final;
    //int* ini, * fin;
    XVector(int size_map, int size_vec);
    ~XVector();
    void push_back(int v);
    void push_front(int v);
    int& operator [](int v) {
        if (final == map + (size_map - 1)) 
        {
            if (*(*final + (size_vec - 1))!=0) 
            {
            int **tmp = new int*[size_map*2];
            int** o = tmp;
            for (int** i = map; i < map+size_map; i++,o++)
                {*o = *i;}
            final = tmp + (size_map);
            map = tmp;
            size_map = size_map * 2;

            *final = new int[size_vec];
            for (int* i = *final; i < *final + size_vec; i++)
                {
                    *i = 0;
                }
            }
        }
        else 
        {
            if (size % size_vec == 0 and size!=0) {
                final++;
                *final = new int [size_vec];
                for (int* i = *final; i < *final+size_vec; i++)
                {
                    *i = 0;
                }
            }
        }
        int vec_ind = v / size_vec;
        if (vec_ind == 0) return *(*map + v);
       
        return *(*(map + vec_ind) + (v-(vec_ind *size_vec)));

    }
};

XVector::XVector(int sm, int sv)
{
    size_map = sm;
    size_vec = sv;
    size = 0;
    map = new int* [size_map];
    final = map;
    *map = new int[size_vec];
    //ini = *map;
    //fin = nullptr;
}

XVector::~XVector()
{}

void XVector::push_back(int v) {
    operator[](size) = v;
    size++;
}
void XVector::push_front(int v) {
    operator[](size) = 0;
    int tmp = 0;
    for (int** i = map; i != final; i++)
    {
        for (int* owo = *i; owo != (*i) + size_vec; owo++) {
            int tmp2 = *owo;
            *owo = tmp;
            tmp = tmp2;
        }
    }
    operator[](0) = v;
}

void print(XVector* p)
{ //no modificar esta funci�n
    for (int i = 0; i < p->size; i++)
        std::cout << (*p)[i] << " ";
    std::cout << "\n";
}

int main()
{
    //no modificar esta funci�n main
    XVector v(4, 3);
    v.push_back(3); v.push_back(8); v.push_back(1);
    v.push_back(4); v.push_back(9); v.push_back(6);
    v.push_back(7);
    print(&v);
    v.push_front(5);
    v.push_front(2);
    print(&v);
    v.push_front(11); v.push_front(17);
    v.push_back(22);
    print(&v);
    v.push_front(33); 
    v.push_back(77);
    v.push_back(5); 
    v.push_back(2); 
    v.push_back(11); 
    v.push_back(17);
    print(&v);
}