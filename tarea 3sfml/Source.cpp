#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <vector>
int tamx=1000;
int aumx = 0;
sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");
struct CBinTreeNode
{
    CBinTreeNode(int v)
    {
        value = v;
        nodes[0] = nodes[1] = 0;
    }
    sf::RectangleShape figura;
    sf::Text texto;
    CBinTreeNode* nodes[2];
    int value;
};

class CBinTree
{
public:
    CBinTree();
    void Print();
    int size=0;
    int sizemapx=1000;
    int sizemapy = 1000;
    bool Insert(int x);
    bool Remove(int x);
private:
    bool Find(int x, CBinTreeNode**& p);
    CBinTreeNode** Rep(CBinTreeNode** p);
    void InOrder(CBinTreeNode* n);
    void InOrderc(CBinTreeNode* n);
    void Levels(CBinTreeNode* n);
    CBinTreeNode* root;
};

CBinTree::CBinTree()
{
    root = 0;
}

bool CBinTree::Find(int x, CBinTreeNode**& p)
{
    for (p = &root; *p && (*p)->value != x;
        p = &((*p)->nodes[x > (*p)->value]));
    return *p != 0;
}

bool CBinTree::Insert(int x)
{
    CBinTreeNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinTreeNode(x);
    size = size + 1;
    return 1;
}

void CBinTree::InOrder(CBinTreeNode* n)
{
    if (!n) return;
    InOrder(n->nodes[0]);
    std::cout << n->value << " ";
    InOrder(n->nodes[1]);
}

void CBinTree::InOrderc(CBinTreeNode* n)
{
    if (!n) return;
    InOrderc(n->nodes[0]);

    window.draw(n->figura);
    window.draw(n->texto);

    InOrderc(n->nodes[1]);
}

void CBinTree::Levels(CBinTreeNode* n)
{
    if (!n) return;
    std::queue<std::pair<CBinTreeNode*, int>> q;
    q.push({ n,0 });
    int l = 0;
    while (!q.empty())
    {
        int last = l;
        std::pair<CBinTreeNode*, int> pp = q.front();
        CBinTreeNode* nn = pp.first;
        l = pp.second;
        if (nn->nodes[0]) {
            q.push({ nn->nodes[0],l + 1 });
        }
        if (nn->nodes[1]) {
            q.push({ nn->nodes[1],l + 1 });
        }
        if (last != l) { 
            std::cout << "\n"; 
            tamx = tamx / 2;
            sizemapx = tamx;
            sizemapy = sizemapy + 50;
            aumx = sizemapx*2;
        }
        nn->figura.setFillColor(sf::Color::Red);
        nn->figura.setSize(sf::Vector2f(30, 30));
        nn->figura.setPosition(sizemapx/2,sizemapy-990);
        sizemapx += aumx;
        std::cout << nn->value << "(" << l << ") ";
        q.pop();
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        InOrderc(n);
        window.display();
    }

}

void CBinTree::Print()
{
    Levels(root);
    std::cout << "\n";
}

void VecInsert(CBinTree* t, int* v, int size)
{
    if (size == 1) {
        t->Insert(*v);
    }
    else if (size == 0) {
        return;
    }
    else {
        if (size % 2 == 0) {
            t->Insert(*(v + (size / 2)));
            VecInsert(t, (v + (size / 2) + 1), (size / 2) - 1);
            VecInsert(t, v, size / 2);
        }
        else {
            t->Insert(*(v + (size / 2)));
            VecInsert(t, (v + (size / 2) + 1), size / 2);
            VecInsert(t, v, size / 2);
        }
    }
}

int main()
{
    CBinTree t;
    int v[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    VecInsert(&t, v, 16);
    t.Print();
}
