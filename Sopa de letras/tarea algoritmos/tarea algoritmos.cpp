
#include <iostream>
using namespace std;
bool palindromo(char *p,int largo) {
    char* p2 = p;
    p2 += (largo-1);
    if (largo==1) {
        return true;
    }
    for (int i = 0; i < largo / 2; i++,p++,p2--) {
        if (*p!=*p2) {
            return false;
        }
    }
    return true;
}
int main(){
    char sopa[6][6] = {{'a','b','p','o','p','a'},
                       {'p','a','o','a','a','a'},
                       {'o','a','p','a','a','l'},
                       {'h','o','l','a','a','o'},
                       {'x','h','o','a','o','l'},
                       {'l','o','l','a','e','f'}};
    int filas = 6;
    int columnas = 6;
    char clave[] = {"zzzz"};
    int lclave = sizeof(clave) / sizeof(clave[0]) - 1;
    char* p3 = clave;
    int fin = 0;
    for (char(*p)[6] = sopa; p < sopa + filas; p++) {
        for (char* p2 = *p; p2 < *p + columnas; p2++) {
            if (*p2==*p3) {
                //1
                if (((p2 - *sopa) % (columnas))+(lclave - 1) < columnas) {
                    fin++;
                    int temp0 = 0;
                    while (temp0 < lclave - 1) {
                        p2++;
                        p3++;
                        temp0++;
                        if (*p2 != *p3) {
                            fin--;
                            break;
                        }
                    }
                    p2 -= temp0;
                    p3 -= temp0;
                }
                //2
                if ((p2 - *sopa) < (filas-(lclave - 1))*columnas) {

                    fin++;
                    int temp1 = 0;
                    while (temp1 < lclave - 1) {
                        p2+=columnas;
                        p3++;
                        temp1++;
                        if (*p2 != *p3) {
                            fin--;
                            break;
                        }
                    }
                    p2 -= (temp1*columnas);
                    p3 -= temp1;
                }
                //3
                if (((p2 - *sopa) % filas)>= lclave - 1) {
                    fin++;
                    int temp2 = 0;
                    while (temp2 < lclave - 1) {
                        p2--;
                        p3++;
                        temp2++;
                        if (*p2 != *p3) {
                            fin--;
                            break;
                        }
                    }
                    p2 += temp2;
                    p3 -= temp2;
                }
                //4
                if ((p2 - *sopa)/columnas >= (lclave-1)) {
                    fin++;
                    int temp3 = 0;
                    while (temp3 < lclave - 1) {
                        p2 -= columnas;
                        p3++;
                        temp3++;
                        if (*p2 != *p3) {
                            fin--;
                            break;
                        }
                    }
                    p2 += (temp3 * columnas);
                    p3 -= temp3;
                }
            }
        }
    }
    if (lclave==1) {
        cout << fin/4;
    }
    else if(palindromo(clave, lclave)){
        cout << fin / 2;
    }
    else {
        cout << fin;
    }
}

