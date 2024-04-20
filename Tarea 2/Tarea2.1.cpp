#include <iostream>
using namespace std;

class Cola {
public:
	int A[10];
	int* head = NULL;
	int* tail = NULL;
	Cola() {
		for (int* p = A; p < A + 10; p++) {
			*p = 0;
		}
	}
	bool Push(int v);
	bool Pop(int& v);
	void Print();
};
bool Cola::Push(int v) {
	if ((!head) || (*head == 0)) {
		head = A;
		tail = head;
		*head = v;
		return 1;
	}
	else {
		if (tail == (A + 9)) {
			if (*A == 0) {
				tail = A;
				*tail = v;
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			if ((tail + 1) == head) {
				return 0;
			}
			else {
				tail++;
				*tail = v;
			}
		}
	}
}
bool Cola::Pop(int& v) {
	v = *head;
	if ((!head) || (head == 0)) {
		return 0;
	}
	else {
		if (head == tail) {
			*head = 0;
			return 1;
		}
		else {
			if (head == (A + 9)) {
				*head = 0;
				head = A;
				return 1;
			}
			else {
				*head = 0;
				head++;
				return 1;
			}
		}
	}
}
void Cola::Print() {
	cout << "{";
	for (int* p = A; p != A + 10; p++) {
		cout << *p << ",";
	}
	cout << "}" << "\n";
}
int main() {
	Cola c;
	int x;
	c.Push(1);
	c.Push(2);
	c.Push(3);
	c.Push(4);
	c.Push(5);
	c.Push(6);
	c.Push(7);
	c.Push(8);
	c.Push(9);
	c.Push(10);
	c.Print();
	c.Pop(x);
	c.Pop(x);
	c.Pop(x);
	c.Pop(x);
	c.Pop(x);
	c.Pop(x);
	c.Pop(x);
	c.Pop(x);
	c.Pop(x);
	c.Pop(x);
	c.Push(1);//error
	c.Push(2);
	c.Push(3);
	c.Push(4);
	c.Push(5);
	c.Push(6);
	c.Push(7);
	c.Push(8);
	c.Push(9);
	c.Push(10);
	if (!c.Push(11)) {
		cout << "no pude";
	}
	c.Pop(x);
	c.Pop(x);
	c.Print();
	if (!c.Push(11)) {
		cout << "no pude";
	}
	c.Push(12);
	if (!c.Push(13)) {
		cout << "no pude";
	}
	c.Print();
}