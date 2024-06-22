#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
	int val;
	int alt;
	Node* right;
	Node* left;
	Node* padre;
	Node(int n, Node* r, Node* l, Node* p) {
		alt = 1;
		val = n;
		right = r;
		left = l;
		padre = p;
	}
};

class AVLtree {
public:
	int tam;
	Node* root = NULL;
	bool Insert(int x);
	bool Delete(int x);
	bool Find(Node**& x, Node*& P, int y);
	void Print(Node* root);
	void Valanceo(Node* x);
	void Inorder(Node* x, vector<int>& arrIn);
	void Levels(Node* n, vector<int>& levels);
	void Posorder(Node* x, vector<int>& arrPos);
};
void AVLtree::Inorder(Node* x, vector<int>& arrIn) {
	if (!x) return;
	Inorder(x->left, arrIn);
	arrIn.push_back((x)->val);
	Inorder(x->right, arrIn);
}
void AVLtree::Levels(Node* n, vector<int>& levels) {
	{
		if (!n) return;
		queue<Node*> q;
		q.push({ n });
		while (!q.empty())
		{
			Node* pp = q.front();
			Node* nn = pp;
			if (nn->left) {
				q.push({ nn->left });
			}
			if (nn->right) {
				q.push({ nn->right});
			}
			levels.push_back(nn->val);
			q.pop();
		}
	}
}
void AVLtree::Posorder(Node* x, vector<int>& arrPos) {
	if (!x) return;
	arrPos.push_back((x)->val);
	Posorder(x->left, arrPos);
	Posorder(x->right, arrPos);
}
void AVLtree::Print(Node* root) {
	vector<int> arrIn;
	vector<int> levels;
	Inorder(root, arrIn);
	Levels(root, levels);
	for (auto i = levels.begin(); i != levels.end();) {
		for (auto i2 = arrIn.begin(); i2 != arrIn.end(); ++i2) {
			if (i != levels.end()) {
				if (*i == *i2) {
					cout << *i2;
					++i;
				}
				else {
					cout << "   ";
				}
			}
		}
		cout << "\n";
	}
}
bool AVLtree::Find(Node**& x, Node*& P, int y) {
	x = &root;
	while ((*x)) {
		if (y > (*x)->val) {
			P = *x;
			x = &(*x)->right;
		}
		else if (y < (*x)->val) {
			P = *x;
			x = &(*x)->left;
		}
		else {
			return 1;
		}
	}
	return 0;
}
void AVLtree::Valanceo(Node* x) {
	while (x) {
		if (x->padre) {
			if (x->padre->alt <= x->alt) {
				x->padre->alt = x->alt + 1;
			}
		}
		int le = (x->left == nullptr ? 0 : x->left->alt);
		int ri = (x->right == nullptr ? 0 : x->right->alt);
		if (ri - le == 2) {
			le = (x->right->left == nullptr ? 0 : x->right->left->alt);
			ri = (x->right->right == nullptr ? 0 : x->right->right->alt);
			if (ri - le == 1) {//caso 1
				x->alt = x->alt - 2;
				x->right->padre = x->padre;
				if (x == root) {
					root = x->right;
				}
				else {
					if (x->padre->right == x) {
						x->padre->right = x->right;
					}
					else {
						x->padre->left = x->right;
					}
				}
				if (x->right->left) {
					x->right->left->padre = x;
				}
				Node* tmp = x->right->left;
				x->right->left = x;
				x->padre = x->right;
				x->right = tmp;

			}
			else if (ri - le == -1) {//caso 4
				x->alt = x->alt - 2;
				x->right->alt = x->right->alt - 1;
				x->right->left->alt = x->right->alt + 1;
				Node* tmpl = x->right->left->right;
				Node* tmpr = x->right->left->left;
				x->right->left->padre = x->padre;
				if (x == root) {
					root = x->right->left;
				}
				else {
					if (x->padre->left == x) {
						x->padre->left = x->right->left;
					}
					else {
						x->padre->right = x->right->left;
					}
				}
				x->padre = x->right->left;
				x->padre->left = x;
				x->padre->right = x->right;
				x->padre->right->padre = x->padre;
				if (tmpl) {
					tmpl->padre = x->padre->right;
					tmpl->padre->left = tmpl;
				}
				if (tmpr) {
					tmpr->padre = x;
					tmpr->padre->right = tmpr;
				}
			}
		}
		if (ri - le == -2) {
			le = (x->left->left == nullptr ? 0 : x->left->left->alt);
			ri = (x->left->right == nullptr ? 0 : x->left->right->alt);
			if (ri - le == 1) {//caso 3
				x->alt = x->alt - 2;
				x->left->alt = x->left->alt - 1;
				x->left->right->alt = x->left->alt + 1;
				Node* tmpl = x->left->right->left;
				Node* tmpr = x->left->right->right;
				x->left->right->padre = x->padre;
				if (x == root) {
					root = x->left->right;
				}
				else {
					if (x->padre->right == x) {
						x->padre->right = x->left->right;
					}
					else {
						x->padre->left = x->left->right;
					}
				}
				x->padre = x->left->right;
				x->padre->right = x;
				x->padre->left = x->left;
				x->padre->left->padre = x->padre;
				if (tmpl) {
					tmpl->padre = x->padre->left;
					tmpl->padre->right = tmpl;
				}
				if (tmpr) {
					tmpr->padre = x;
					tmpr->padre->left = tmpr;
				}
			}
			else if (ri - le == -1) {//caso2
				x->alt = x->alt - 2;
				x->left->padre = x->padre;
				if (x == root) {
					root = x->left;
				}
				else {
					if (x->padre->left == x) {
						x->padre->left = x->left;
					}
					else {
						x->padre->right = x->left;
					}
				}
				if (x->left->right) {
					x->left->right->padre = x;
				}
				Node* tmp = x->left->right;
				x->left->right = x;
				x->padre = x->left;
				x->left = tmp;
			}
		}
		x = x->padre;
	}


}
bool AVLtree::Insert(int x) {
	if (!root) {
		root = new Node(x, NULL, NULL, NULL);
	}
	else {
		Node** tmp;
		Node* P;
		if (Find(tmp, P, x)) {
			return 0;
		}
		else {
			(*tmp) = new Node(x, NULL, NULL, P);
			Valanceo(*tmp);
			return 1;
		}
	}
}

int main() {
	AVLtree uwu;
	uwu.Insert(800);
	uwu.Insert(700);
	uwu.Insert(600);
	uwu.Insert(500);
	uwu.Insert(400);
	uwu.Insert(300);
	uwu.Insert(200);
	uwu.Insert(100);


	//uwu.Print(uwu.root);

	uwu.Print(uwu.root);
}