#include <SFML/Graphics.hpp>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>
using namespace std;
bool** coor;
class Entity {
public:
    int posx;
    int posy;
    int tamaño;
    std::mutex myMutex;
    std::vector<std::thread> some_threads;
    sf::RectangleShape* A;
    sf::RectangleShape body;
    void movimiento();
    void unirthread();
    Entity(int x, int y, sf::Color col, int tam) : posx(x), posy(y), tamaño(tam) {
        body.setFillColor(col);
        body.setSize(sf::Vector2f(30, 30));
        A = new sf::RectangleShape[tam];
        for (int i = 0; i < tam; i++) {
            body.setPosition(posx * 30, (posy * 30) + i * 30);
            A[i] = body;
        }
    }
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
};
void Entity::unirthread() {
    some_threads.push_back(thread(&Entity::movimiento, this));
}
void Entity::movimiento() {
    // 1 arriba, 2 izquierda, 3 derecha, 4 abajo
    int numeroAleatorio;
    int tempx = posx * 30;
    int tempy = posy * 30;
    sf::Vector2f position = A[1].getPosition();
    int resX = position.x / 30;
    int resY = position.y / 30;
    if (posx < 0 or posy < 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(3, 4);
        numeroAleatorio = dis(gen);
    }
    else if (posx > 30 or posy > 30) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 2);
        numeroAleatorio = dis(gen);
    }
    else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 4);
        numeroAleatorio = dis(gen);
    }
    if (numeroAleatorio == 1 and resY != (posy - 1)) {
        //mover arriba
        myMutex.lock();
        if (!coor[posx][posy - 1]) {
            posy -= 1;
            coor[posx][posy - 1] = 1;
        }
        myMutex.unlock();
    }
    else if (numeroAleatorio == 2 and resX != (posx - 1)) {
        // Mover hacia la izquierda
        myMutex.lock();
        if (!coor[posx - 1][posy]) {
            posx -= 1;
            coor[posx - 1][posy] = 1;
        }
        myMutex.unlock();
    }
    else if (numeroAleatorio == 3 and resX != (posx + 1)) {
        // Mover hacia la derecha
        myMutex.lock();
        if (!coor[posx + 1][posy]) {
            posx += 1;
            coor[posx + 1][posy] = 1;
        }
        myMutex.unlock();
    }
    else if (numeroAleatorio == 4 and resY != (posy + 1)) {
        // Mover hacia abajo
        myMutex.lock();
        if (!coor[posx][posy + 1]) {
            posy += 1;
            coor[posx][posy + 1] = 1;
        }
        myMutex.unlock();
    }
    myMutex.lock();
    if (!(posx == tempx and posy == tempy)) {
        A[0].setPosition(posx * 30, posy * 30);
        for (int i = 1; i < tamaño; i++) {
            sf::Vector2f position = A[i].getPosition();
            int posX = position.x / 30;
            int posY = position.y / 30;
            A[i].setPosition(tempx, tempy);
            coor[tempx / 30][tempy / 30] = 0;
            tempx = posX * 30;
            tempy = posY * 30;
        }
        sf::Vector2f pfn = A[tamaño - 1].getPosition();
        int pfnX = pfn.x / 30;
        int pfnY = pfn.x / 30;
        coor[pfnX][pfnY] = 0;
    }
    myMutex.unlock();

}

class Mapa {
public:
    sf::RectangleShape* A;
    int filas;
    int columnas;
    Mapa(int fil, int colu, sf::Color col)
        : filas(fil / 30), columnas(colu / 30) {
        sf::RectangleShape temp;
        temp.setFillColor(col);
        temp.setSize(sf::Vector2f(30, 30));

        A = new sf::RectangleShape[filas * columnas];
        coor = new bool* [filas];
        for (int i = 0; i < filas; ++i) {
            coor[i] = new bool[columnas];
            for (int j = 0; j < columnas; ++j) {
                temp.setPosition(j * 30, i * 30);
                A[i * columnas + j] = temp;
                coor[i][j] = false;

            }
        }
    }
};
int main() {
    int tammapx = 900;
    int tammapy = 900;
    Mapa mp(tammapx, tammapy, sf::Color::Cyan);
    Entity gus(8, 2, sf::Color::Red, 10);
    Entity gus1(4, 4, sf::Color::White, 10);
    Entity gus2(6, 2, sf::Color::Green, 10);
    Entity gus3(7, 11, sf::Color::Magenta, 10);

    std::vector<Entity*> arr = { &gus, &gus1, &gus2, &gus3 };
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!");
    window.setFramerateLimit(6);
    int i = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        sf::RectangleShape* q = mp.A;
        for (int i = 0; i < tammapx; i++) {
            window.draw(*(q + i));
        }

        for (size_t i = 0; i < arr.size(); ++i) {
            Entity* p = arr[i];
            for (sf::RectangleShape* q = p->A; q != p->A + p->tamaño; ++q) {
                window.draw(*q);
            }
            (*p).unirthread();
        }
        window.display();
    }

    return 0;
}