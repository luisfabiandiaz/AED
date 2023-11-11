#include <iostream>
#include <queue>
#include <stack>
#include <assert.h>
using namespace std;
template <class T>
struct Node {
	T valor;
	bool Isred;
	Node<T>* right=0;
	Node<T>* left=0;
	Node<T>* Padre;
	Node(T v, Node<T>* p) {
		Isred = 1;
		valor = v;
		Padre = p;
	}
	T getFather() {
		if (!Padre) return 0;
		return Padre->valor;
	}
};
template <class T>
struct AVLTree {
	Node<T>* root;
	bool find(T v, Node<T>**& p, stack<Node<T>**>& s);
	bool insert(T v);
	void Inspeccionrojos(Node<T>* p);
	void Caso1(Node<T>* p,bool x);
	void Caso2(Node<T>* p, bool x);
	void Caso3(Node<T>* p, bool x);
	void Caso4(Node<T>* p, bool x);
	void print();
	void inOrder(Node<T>* r);
	bool Tionegro(Node<T>* p);
	void coloreo(Node<T>* p);
	AVLTree() {
		root = NULL;
	}
};
template <class T>
void AVLTree<T>::print() {
	inOrder(root);
}

template <class T>
void AVLTree<T>::inOrder(Node<T>* r) {
	if (!r) return;
	inOrder(r->left);
	if (r->Isred)
		cout << r->valor << "-" << r->getFather() << "-R  ";
	else
		cout << r->valor << "-" << r->getFather() << "-B  ";
	inOrder(r->right);
}

template <class T>
bool AVLTree<T>::find(T v, Node<T>**& p, stack<Node<T>**>& s) {
	p = &root;
	while (*p) {
		s.push(p);
		if (v < (*p)->valor) {
			p = &((*p)->left);
		}
		else {
			if (v == (*p)->valor) {
				return 1;
			}
			p = &((*p)->right);
		}
	}
	return 0;
}
template <class T>
bool AVLTree<T>::insert(T v) {
	Node<T>** p;
	stack<Node<T>**> s;
	if (find(v, p, s)) return 0;
	if (!s.empty()) {
		(*p) = new Node<T>(v, *s.top());
	}
	else {
		(*p) = new Node<T>(v, 0);
		(*p)->Isred = 0;
	}
	Inspeccionrojos(*p);
	return 1;
}
template<class T>
void AVLTree<T>::Inspeccionrojos(Node<T>* p) {
	for (;p!=root,p;p=p->Padre) {
		if (p->Isred&&p->Padre->Isred) {
			if (Tionegro(p)){
				//caso 1 si soy el hijo derecho de mi papa y mi papa es el hijo derecho de mi abuelo
				if (p->Padre->right == p && p->Padre->Padre->right == p->Padre) {
					if (p->Padre->Padre->Padre) {
						Caso1(p, 1);
					}
					else {
						Caso1(p, 0);
					}
				}
					//caso 2 lo mismo pero izquierda
				else if (p->Padre->left == p && p->Padre->Padre->left == p->Padre) {
					if (p->Padre->Padre->Padre) {
						Caso2(p, 1);
					}
					else {
						Caso2(p, 0);
					}
				}
				else if (p->Padre->left == p && p->Padre->Padre->right == p->Padre) {
					if (p->Padre->Padre->Padre) {
						Caso3(p, 1);
					}
					else {
						Caso3(p, 0);
					}
				}
				else if (p->Padre->left == p && p->Padre->Padre->right == p->Padre) {
					if (p->Padre->Padre->Padre) {
						Caso4(p, 1);
					}
					else {
						Caso4(p, 0);
					}
				}
			}
			else {
				coloreo(p);
			}
		}
	}
}
template<class T>
bool AVLTree<T>::Tionegro(Node<T>* p) {
	bool soyderecho = 0;
	if (p->Padre->Padre->right == p->Padre) {
		soyderecho = 1;
	}
	if (soyderecho) {
		if (p->Padre->Padre->left) {
			return !(p->Padre->Padre->left->Isred);
		}
		else {
			return 1;
		}
	}
	else {
		if (p->Padre->Padre->right) {
			return !(p->Padre->Padre->left->Isred);
		}
		else {
			return 1;
		}
	}
}
template<class T>
void AVLTree<T>::coloreo(Node<T>* p) {
	p->Padre->Padre->Isred = 1;
	p->Padre->Padre->left->Isred = 0;
	p->Padre->Padre->right->Isred = 0;
	root->Isred = 0;
}
template<class T>
void AVLTree<T>::Caso4(Node<T>* p, bool x) {
	Node<T>* tmp = p->left;
	p->Padre->Padre->left = p;
	p->left = p->Padre;
	p->Padre = p->left->Padre;
	p->left->Padre = p;
	p->left->right = tmp;
	p->left->right->Padre = p->left;

	Caso2(p->left, x);

}
template<class T>
void AVLTree<T>::Caso3(Node<T>* p, bool x) {
	Node<T>* tmp = p->right;
	p->Padre->Padre->right = p;
	p->right = p->Padre;
	p->Padre = p->right->Padre;
	p->right->Padre = p;
	p->right->left = tmp;
	p->right->left->Padre = p->right;

	Caso1(p->right, x);

}

template<class T>
void AVLTree<T>::Caso2(Node<T>* p, bool x) {
	if (!x) {
		p->Padre->Isred = 0;
		p->Padre->Padre->Isred = 1;

		Node<T>* tmp = p->Padre->right;
		p->Padre->right = p->Padre->Padre;
		p->Padre->Padre->left = tmp;
		p->Padre->Padre->Padre = p->Padre;
		if (p->Padre->Padre->left) {
			p->Padre->Padre->left->Padre = p->Padre->Padre;
		}
		p->Padre->Padre = 0;
		root = p->Padre;
	}
	else {
		if (p->Padre->Padre->Padre->right == p->Padre->Padre) {
			p->Padre->Isred = 0;
			p->Padre->Padre->Isred = 1;

			p->Padre->Padre->Padre->right = p->Padre;

			Node<T>* tmp = p->Padre->right;
			Node<T>* tmp2 = p->Padre->Padre->Padre;
			p->Padre->right = p->Padre->Padre;
			p->Padre->Padre->left = tmp;
			p->Padre->Padre->Padre = p->Padre;
			if (p->Padre->Padre->left) {
				p->Padre->Padre->left->Padre = p->Padre->Padre;
			}
			p->Padre->Padre = tmp2;
		}
		else {
			p->Padre->Isred = 0;
			p->Padre->Padre->Isred = 1;

			p->Padre->Padre->Padre->left = p->Padre;

			Node<T>* tmp = p->Padre->right;
			Node<T>* tmp2 = p->Padre->Padre->Padre;
			p->Padre->right = p->Padre->Padre;
			p->Padre->Padre->left = tmp;
			p->Padre->Padre->Padre = p->Padre;
			if (p->Padre->Padre->left) {
				p->Padre->Padre->left->Padre = p->Padre->Padre;
			}
			p->Padre->Padre = tmp2;
		}
	}
	root->Isred = 0;
}
template<class T>
void AVLTree<T>::Caso1(Node<T>* p,bool x) {
	if (!x) {
		p->Padre->Isred = 0;
		p->Padre->Padre->Isred = 1;

		Node<T>* tmp = p->Padre->left;
		p->Padre->left = p->Padre->Padre;
		p->Padre->Padre->right = tmp;
		p->Padre->Padre->Padre = p->Padre;
		if (p->Padre->Padre->right) {
			p->Padre->Padre->right->Padre = p->Padre->Padre;
		}
		p->Padre->Padre = 0;
		root = p->Padre;
	}
	else {
		if(p->Padre->Padre->Padre->right==p->Padre->Padre) {
			p->Padre->Isred = 0;
			p->Padre->Padre->Isred = 1;

			p->Padre->Padre->Padre->right = p->Padre;
			Node<T>* tmp = p->Padre->left;
			Node<T>* tmp2 = p->Padre->Padre->Padre;
			p->Padre->left = p->Padre->Padre;
			p->Padre->Padre->right = tmp;
			p->Padre->Padre->Padre = p->Padre;
			if (p->Padre->Padre->right) {
				p->Padre->Padre->right->Padre = p->Padre->Padre;
			}
			p->Padre->Padre = tmp2;
		}
		else {
			p->Padre->Isred = 0;
			p->Padre->Padre->Isred = 1;

			p->Padre->Padre->Padre->left = p->Padre;
			Node<T>* tmp = p->Padre->left;
			Node<T>* tmp2 = p->Padre->Padre->Padre;
			p->Padre->left = p->Padre->Padre;
			p->Padre->Padre->right = tmp;
			p->Padre->Padre->Padre = p->Padre;
			if (p->Padre->Padre->right) {
				p->Padre->Padre->right->Padre = p->Padre->Padre;
			}
			p->Padre->Padre = tmp2;
		}
	}
	root->Isred = 0;
}

int main() {
	AVLTree<int> uwu;
	uwu.insert(200);
	uwu.print();
	cout << "\n";
	uwu.insert(150);
	uwu.print();
	cout << "\n";
	uwu.insert(250);
	uwu.print();
	cout << "\n";
	uwu.insert(300);
	uwu.print();
	cout << "\n";
	uwu.insert(225);
	uwu.print();
	cout << "\n";
	uwu.insert(230);
	uwu.print();
	cout << "\n";
	uwu.insert(215);
	uwu.print();
	cout << "\n";
	uwu.insert(214);
	uwu.print();
	cout << "\n";

	return 0;
}
