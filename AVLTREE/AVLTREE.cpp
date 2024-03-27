#include <SFML/Graphics.hpp>

#include<vector>
#include <iostream>

using namespace std;

template <tnode<T>pename T>
struct node {
	T valor;
	node<T>* left;
	node<T>* right;
	node<T>* up;
	bool lor;//0 es hijo izquierdo de su padre 1 es hijo derecho de su padre
	bool red = 1;//1 rojo 0 negro
	node(T v, node<T>* u = 0) {
		valor = v;
		up = u;
	}
	T getFather() {
		if (!up) return 0;
		return up->valor;
	}
};

template <class T>
struct RBtree {
	node<T>* root = 0;
	bool insert(T v);
	bool remove(T v);
	void print();
private:
	void inOrder(node<T>* r);
	bool find(T v, node<T>**& p, node<T>**& father);
	void balance(node<T>**& father);
	void changeColor(node<T>* n);
	void redUncle(node<T>** f, bool leftFather);
	void blackUncle(node<T>**& f, bool leftChild, bool leftFather);
	node<T>* mini(node<T>* p);
	void fixRem(node<T>**& p, node<T>* q);
};

template <class T>
bool RBtree<T>::find(T v, node<T>**& p, node<T>**& father) {
	p = &root;
	father = 0;
	while (*p) {
		if (v < (*p)->valor) {
			father = p;
			p = &((*p)->left);
		}
		else {
			if (v == (*p)->valor) {
				return 1;
			}
			father = p;
			p = &((*p)->right);
		}
	}
	return 0;
}

template <class T>
bool RBtree<T>::insert(T v) {
	node<T>** p;
	node<T>** father;
	if (find(v, p, father)) return 0;
	if (father) {
		(*p) = new node<T>(v, *father);
		if ((*p)->up->left == (*p)) {
			(*p)->lor = 0;
		}
		else {
			(*p)->lor = 1;
		}
	}
	else {
		(*p) = new node<T>(v);
		(*p)->red = 0;
	}

	balance(father);
	return 1;
}

template <class T>
void RBtree<T>::changeColor(node<T>* n) {
	if (n->red)
		n->red = 0;
	else
		n->red = 1;
}

template <class T>
void RBtree<T>::redUncle(node<T>** f, bool leftFather) {
	changeColor(*f);
	changeColor((*f)->up);
	if (leftFather)
		changeColor((*f)->up->right);
	else
		changeColor((*f)->up->left);
}

template <class T>
void RBtree<T>::blackUncle(node<T>**& f, bool leftChild, bool leftFather) {

	if (leftChild && leftFather) {//lineleft(/)

		if ((*f)->up->up) {//tiene bisabuelo?
			if ((*f)->up->up->left == (*f)->up) {//el abuelo es hijo izquierdo
				(*f)->up->up->left = (*f);//r->B
				node<T>* tmp1 = (*f)->right;//tmp1->Br
				(*f)->right = (*f)->up;//Br->C
				(*f)->up = (*f)->up->up;//Bu->r
				(*f)->right->up = *f;//Cu->B
				f = &((*f)->up->left);//f->r
				(*f)->right->left = tmp1;//Cl->Br
				if (tmp1) {//existe Br?
					tmp1->up = (*f)->right;//BRu->C
				}
			}
			else {//el abuelo es hijo derecho
				(*f)->up->up->right = (*f);//r->B
				node<T>* tmp1 = (*f)->right;//tmp1->Br
				(*f)->right = (*f)->up;//Br->C
				(*f)->up = (*f)->up->up;//Bu->r
				(*f)->right->up = *f;//Cu->B
				f = &((*f)->up->right);//f->r
				(*f)->right->left = tmp1;//Cl->Br
				if (tmp1) {//existe Br?
					tmp1->up = (*f)->right;//BRu->C
				}
			}
		}
		else {//no tiene bisabuelo
			root = (*f);//r->B
			node<T>* tmp1 = (*f)->right;//tmp1->Br
			(*f)->right = (*f)->up;//Br->C
			(*f)->up = 0;//Bu->r
			(*f)->right->up = *f;//Cu->B
			f = &root;//f->r
			(*f)->right->left = tmp1;//Cl->Br
			if (tmp1) {//existe Br?
				tmp1->up = (*f)->right;//BRu->C
			}
		}
		changeColor(*f);
		changeColor((*f)->right);
		(*f)->lor = (*f)->right->lor;
		(*f)->left->lor = 0;
		(*f)->right->lor = 1;
		if ((*f)->right->left) (*f)->right->left->lor = 0;
	}

	else if (leftChild && !leftFather) {//righttriangle(>)
		node<T>* tmp = (*f)->left->right;//tmp->Br
		(*f)->left->right = (*f);//Br->C
		if (tmp) tmp->up = (*f);//Si BRu, BRu->C
		(*f)->left->up = (*f)->up;//Bu->A
		(*f) = (*f)->left;//Ar->B
		(*f)->right->up = (*f);//Cu->B
		(*f)->right->left = tmp;//Cl->Br
		blackUncle(f, 0, 0);
	}

	else if (!leftChild && leftFather) {//lefttriangle(<)
		node<T>* tmp = (*f)->right->left;//tmp->Bl
		(*f)->right->left = (*f);//Bl->A
		if (tmp) tmp->up = (*f);//Si BLu, BLu->A
		(*f)->right->up = (*f)->up;//Bu->C
		(*f) = (*f)->right;//Cr->B
		(*f)->left->up = (*f);//Au->B
		(*f)->left->right = tmp;//Ar->Bl
		blackUncle(f, 1, 1);
	}

	else {//lineright(/)

		if ((*f)->up->up) {//tiene bisabuelo?
			if ((*f)->up->up->left == (*f)->up) {//el abuelo es hijo izquierdo
				(*f)->up->up->left = (*f);//r->B
				node<T>* tmp1 = (*f)->left;//tmp1->Bl
				(*f)->left = (*f)->up;//Bl->A
				(*f)->up = (*f)->up->up;//Bu->r
				(*f)->left->up = *f;//Au->B
				f = &((*f)->up->left);//f->r
				(*f)->left->right = tmp1;//Ar->Bl
				if (tmp1) {//existe Bl?
					tmp1->up = (*f)->left;//BRu->A
				}
			}
			else {//el abuelo es hijo derecho
				(*f)->up->up->right = (*f);//r->B
				node<T>* tmp1 = (*f)->left;//tmp1->Bl
				(*f)->left = (*f)->up;//Bl->A
				(*f)->up = (*f)->up->up;//Bu->r
				(*f)->left->up = *f;//Au->B
				f = &((*f)->up->right);//f->r
				(*f)->left->right = tmp1;//Ar->Bl
				if (tmp1) {//existe Bl?
					tmp1->up = (*f)->left;//BRu->A
				}
			}
		}
		else {//no tiene bisabuelo
			root = (*f);//r->B
			node<T>* tmp1 = (*f)->left;//tmp1->Bl
			(*f)->left = (*f)->up;//Bl->A
			(*f)->up = 0;//Bu->r
			(*f)->left->up = *f;//Au->B
			f = &root;//f->r
			(*f)->left->right = tmp1;//Ar->Bl
			if (tmp1) {//existe Bl?
				tmp1->up = (*f)->left;//BRu->A
			}
		}
		changeColor(*f);
		changeColor((*f)->left);
		(*f)->lor = (*f)->left->lor;
		(*f)->left->lor = 0;
		(*f)->right->lor = 1;
		if ((*f)->left->right) (*f)->left->right->lor = 1;
	}
}

template <class T>
void RBtree<T>::balance(node<T>**& father) {
	while (father) {
		if ((*father)->red) {//padre rojo?
			if ((*father)->left) {//tiene hijo izquierdo?
				if ((*father)->left->red) {//hijo rojo?
					if ((*father)->up->nodes[(!(*father)->lor)] && (*father)->up->nodes[(!(*father)->lor)]->red) {//tio rojo?
						redUncle(father, (!(*father)->lor));
					}
					else {//tio negro
						blackUncle(father, 1, (!(*father)->lor));
					}
				}
			}
			if ((*father)->red && (*father)->right) {//hijo derecho
				if ((*father)->right->red) {//hijo rojo?
					if ((*father)->up->nodes[(!(*father)->lor)] && (*father)->up->nodes[(!(*father)->lor)]->red) {//tio rojo?
						redUncle(father, (!(*father)->lor));
					}
					else {//tio negro
						blackUncle(father, 0, (!(*father)->lor));
					}
				}
			}
		}
		else
			return;
		if ((*father)->up && (*father)->up->up)
			father = &((*father)->up->up->nodes[(*father)->up->lor]);
		else {
			father = &root;
		}
		root->red = 0;
	}
}

template <class T>
node<T>* RBtree<T>::mini(node<T>* p) {
	while (p->left) {
		p = p->left;
	}
	return p;
}

template <class T>
void RBtree<T>::fixRem(node<T>**& p, node<T>* q) {
	if ((*p) && (*p)->red) {
		(*p)->red = 0;
	}
	else {
		bool dBlack = 1;
		if (!(*p)) {
			while (dBlack) {
				if (q->left) {
					if (q->left->red) {
						node<T>** qu = &(q->left);
						if (q->left->lor) blackUncle(qu, 0, 0);
						else blackUncle(qu, 1, 1);
					}
					else {
						if (q->left->left && q->left->left->red) {//hijo rojo izquierdo
							p = &(q->left);
							if ((*p)->lor) {
								blackUncle(p, 1, 0);
								changeColor((*p)->left);
								//changeColor((*p)->right);
							}
							else {
								blackUncle(p, 1, 1);
								changeColor((*p));
								changeColor((*p)->right);
								//changeColor((*p)->left);
							}
							dBlack = 0;
						}
						else if (q->left->right && q->left->right->red) {//hijo rojo derecho
							p = &(q->left);
							if ((*p)->lor) {
								blackUncle(p, 0, 0);
								changeColor((*p));
								changeColor((*p)->left);
								//changeColor((*p)->right);
							}
							else {
								blackUncle(p, 0, 1);
								changeColor((*p)->right);
								//changeColor((*p)->left);
							}
							dBlack = 0;
						}
						else {//sin hijos rojos
							changeColor(q->left);
							if (q->red) {
								q->red = 0;
								dBlack = 0;
							}
							else {
								if (q->up) p = &(q->up->nodes[q->lor]);
								else p = &root;
							}
						}
					}
				}
				else {
					if (q->right->red) {
						node<T>** qu = &(q->right);
						if (q->right->lor) blackUncle(qu, 0, 0);
						else blackUncle(qu, 1, 1);
					}
					else {
						if (q->right->left && q->right->left->red) {//hijo rojo izquierdo
							p = &(q->right);
							if ((*p)->lor) {
								blackUncle(p, 1, 0);
								changeColor((*p)->left);
								//changeColor((*p)->right);
							}
							else {
								blackUncle(p, 1, 1);
								changeColor((*p));
								changeColor((*p)->right);
								//changeColor((*p)->left);
							}
							dBlack = 0;
						}
						else if (q->right->right && q->right->right->red) {//hijo rojo derecho
							p = &(q->right);
							if ((*p)->lor) {
								blackUncle(p, 0, 0);
								changeColor((*p));
								changeColor((*p)->left);
								//changeColor((*p)->right);
							}
							else {
								blackUncle(p, 0, 1);
								changeColor((*p)->right);
								//changeColor((*p)->left);
							}
							dBlack = 0;
						}
						else {//sin hijos rojos
							changeColor(q->right);
							if (q->red) {
								q->red = 0;
								dBlack = 0;
							}
							else {
								if (q->up) p = &(q->up->nodes[q->lor]);
								else p = &root;
							}
						}
					}
				}
			}
		}
		else {
			while (dBlack && (*p)->up) {
				if ((*p)->up->nodes[!((*p)->lor)] && (*p)->up->nodes[!((*p)->lor)]->red) {
					//hermano rojo
					node<T>** qu = &((*p)->up->nodes[!((*p)->lor)]);
					if ((*p)->up->nodes[!((*p)->lor)]->lor) blackUncle(qu, 0, 0);
					else blackUncle(qu, 1, 1);
				}
				else {
					//hermano negro
					if ((*p)->up->nodes[!((*p)->lor)]->left && (*p)->up->nodes[!((*p)->lor)]->left->red) {//hijo rojo izquierdo
						p = &((*p)->up->nodes[!((*p)->lor)]);
						if ((*p)->lor) {
							blackUncle(p, 1, 0);
							changeColor((*p)->left);
							//changeColor((*p)->right);
						}
						else {
							blackUncle(p, 1, 1);
							changeColor((*p));
							changeColor((*p)->right);
							//changeColor((*p)->left);
						}
						dBlack = 0;
					}
					else if ((*p)->up->nodes[!((*p)->lor)]->right && (*p)->up->nodes[!((*p)->lor)]->right->red) {//hijo rojo derecho
						p = &((*p)->up->nodes[!((*p)->lor)]);
						if ((*p)->lor) {
							blackUncle(p, 0, 0);
							changeColor((*p));
							changeColor((*p)->left);
							//changeColor((*p)->right);
						}
						else {
							blackUncle(p, 0, 1);
							changeColor((*p)->right);
							//changeColor((*p)->left);
						}
						dBlack = 0;
					}
					else {//sin hijos rojos
						changeColor((*p)->up->nodes[!((*p)->lor)]);
						if ((*p)->up->red) {
							(*p)->up->red = 0;
							dBlack = 0;
						}
						else {
							if ((*p)->up->up) p = &((*p)->up->up->nodes[(*p)->up->lor]);
							else p = &root;
						}
					}
				}
			}
		}
	}
}

template <class T>
bool RBtree<T>::remove(T v) {
	node<T>** p = &root;
	node<T>** father;
	if (!find(v, p, father)) return 0;
	bool originalColor = (*p)->red;
	node<T>* q = (*p)->up;
	if ((*p)->left) {
		if ((*p)->right) {
			//función remover con 2 hijos
			node<T>* mi = mini((*p)->right);
			originalColor = mi->red;
			(*p)->valor = mi->valor;
			mi->up->nodes[mi->lor] = mi->right;
			if (mi->right) {
				mi->right->up = mi->up;
				mi->right->lor = mi->lor;
			}
			p = &(mi->up->left);
			q = mi->up;
			delete mi;
		}
		else {
			//función remover con solo hijo izquierdo
			node<T>* tmp = (*p);
			if ((*p)->up) {
				(*p)->left->up = (*p)->up;
				(*p)->left->lor = (*p)->lor;
				(*p)->up->nodes[(*p)->lor] = (*p)->left;
				delete tmp;
			}
			else {
				(*p)->left->up = 0;
				root = (*p)->left;
				delete tmp;
			}
		}
	}
	else {
		node<T>* tmp = (*p);
		if ((*p)->up) {
			if ((*p)->right) {
				(*p)->right->up = (*p)->up;
				(*p)->right->lor = (*p)->lor;
			}
			(*p)->up->nodes[(*p)->lor] = (*p)->right;
			delete tmp;
		}
		else {
			if ((*p)->right) {
				(*p)->right->up = 0;
			}
			root = (*p)->right;
			delete tmp;
		}
	}
	if (!originalColor) fixRem(p, q);
	return 1;
}

template <class T>
void RBtree<T>::print() {
	inOrder(root);
}

template <class T>
void RBtree<T>::inOrder(node<T>* r) {
	if (!r) return;
	inOrder(r->left);
	if (r->red)
		cout << r->valor << "-" << r->getFather() << "-R-" << r->lor << "  ";
	else
		cout << r->valor << "-" << r->getFather() << "-B-" << r->lor << "  ";
	inOrder(r->right);
}

template <class T>
void inOr(node<T>* r, std::vector<node<T>*>& vec1) {
	if (!r) return;
	inOr(r->left, vec1);
	vec1.push_back(r);
	inOr(r->right, vec1);
}

template <class T>
void preOr(node<T>* r, std::vector<node<T>*>& vec2) {
	if (!r) return;
	vec2.push_back(r);
	preOr(r->left, vec2);
	preOr(r->right, vec2);
}

int main() {
	RBtree<int> t1;
	vector<node<int>*> vec1;
	vector<node<int>*> vec2;

	/*for (int i = 1; i <= 100; i++)
		t1.insert(i * 10);*/

	t1.insert(50);

	t1.insert(25);
	t1.insert(13);
	t1.insert(1);

	t1.insert(55);
	t1.insert(60);
	t1.insert(65);

	t1.insert(80);
	t1.insert(70);

	/*t1.remove(80);
	t1.remove(55);
	t1.remove(50);
	t1.remove(13);*/

	//t1.print();

	inOr(t1.root, vec1);
	preOr(t1.root, vec2);

	int n = vec1.size();

	int ancho = 1000;

	std::string s;

	int X = 0;
	int node<T> = 0;
	sf::RenderWindow window(sf::VideoMode(ancho, ancho), "SFML works!");
	sf::CircleShape shape(ancho / n / 4);
	shape.setFillColor(sf::Color::Red);

	sf::Text texto;


	sf::Font fuente;
	if (!fuente.loadFromFile("ARIAL.ttf")) {
		std::cout << "GG";
	}

	texto.setFont(fuente);
	texto.setFillColor(sf::Color::Cnode<T>an);
	texto.setCharacterSize(ancho / n / 4);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.tnode<T>pe == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		/*X = 0;
		node<T> = 0;*/
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (vec1[i] == vec2[j]) {
					X = i * ancho / n;
					node<T> = j * ancho / n;
					shape.setPosition(X, node<T>);
					texto.setPosition(X + ancho / n / 8, node<T> +ancho / n / 8);
					if (vec1[i]->red) {
						shape.setFillColor(sf::Color::Red);
					}
					else {
						shape.setFillColor(sf::Color::Black);
					}
					s = to_string(vec1[i]->valor);
					texto.setString(s);
					window.draw(shape);
					window.draw(texto);
				}
			}
		}
		window.displanode<T>();
	}

	return 0;
}