#include <iostream>
using namespace std;
#include <list>
#include <vector>
template <class NN,class EE>
class CGraph {
public:
    typedef CGraph<NN, EE> G;
    typedef CNode<G> Node;
    typedef CEdge<G> Edge;
    typedef NN N;
    typedef EE E;

    vector<Node*> nodes;
    insert(N n, E e, Node* B, bool d) {

    }
    void insNode(N n) {

    }
    void insArista(Node *A,Node *B,E e,bool d) {

    }
};

template <class G>
class CNode {
    typedef G::N N;
    typedef G::Edge Edge;

    N value;
    list<Edge *> Edge;
};


template <class G>
class CEdge {
    typedef G::E E;
    typedef G::Node Node;

    E value;
    Node* Nodes[2];
    bool dir;
};



int main()
{
    std::cout << "Hello World!\n";
}
