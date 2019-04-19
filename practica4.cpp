#include "pch.h"
#include <iostream>
using namespace std;
inline int modulo(int a,int n) {
	int res = a - n * (a / n);
	if (res < 0)
		res += n;
	return res;
}
template<class T>
struct asc {
	bool operator()(T a, T b) {
		return a < b;
	}
};

template<class T>
struct des {
	bool operator()(T a, T b) {
		return a > b;
	}
};


template<class T>
struct node {
	T val;
	node<T>* next;
	node(T x) { val = x; next = nullptr; }
};

template<class T,class O>
struct clistp {
	node<T>* head;
	O o;
	clistp() { head = nullptr; };

	bool find(T x, node<T>* &p, node <T>* &t) {
		p = head;
		if (!p)
			return 0;

		if (o(x, p->val)) {
			t = head;
			while ((t->next)!= head) {
				t = t->next;
			}
				return 0;
		}

		t = p->next;

		if (head->val == x) {
			while (t != head) {
				p = t;
				t = t->next;
			}
			return 1;
		}

		while (t!=head && o(t->val,x)) {
			p = t;
			t = t->next;
		}
		return t!=head && t->val==x;
	}

	bool insert(T x) {
		node<T>* t;
		node<T>* p;
		if (find(x, p, t))
			return 0;
		if (!p) {
			head = new node<T>(x);
			head->next = head;
		}
		else if (o(x, p->val)) {
			head = new node<T>(x);
			head->next = p;
			t->next = head;
		}
		else if (p && t==head) {
			p->next = new node<T>(x);
			p->next->next=head;
		}
		else if (p && t!=head) {
			p->next = new node<T>(x);
			p->next->next = t;
		}
		return 1;
	}

	bool remove(T x) {
		node<T>* p;
		node<T>* t;
		if (!find(x, p, t))
			return 0;

		if (p != head && t==head) {
			head = head->next;
			p->next = head;
			delete[]t;
		}
		else if (p==head && t==head) {
			head->next= nullptr;
			head = nullptr;
			delete[]t;
		}
		else if (t->next!=head && t!=head) {
			p->next = t->next;
			delete[]t;
		}
		else if (t->next==head && t!=head) {
			p->next = head;
			delete[]t;
		}
		return 1;
	}

	void show() {
		if (head) {
			cout << head->val << " ";
			for (node<T>* i = head->next; i != head && head; i = i->next)
				cout << i->val << " ";
		}
	}
	~clistp() {
		node<T>*t= head->next;
		while (t && !(t->next)) {
			node<T>*p = head;
			head = t;
			delete[]p;
			t = t->next;
		}
		delete[]t;
	}

	void josephus(int n, int k) {
		for (int i = 1; i <= n; i++)
			insert(T(i));
		show();
		cout << endl;
		node<T>* c = head;
		for (int i = n-1; i != 0; i--) {
			for (int j = k-1; j != 0; j--)
				c = c->next;
			node<T>* p = c->next;
			remove(c->val);
			show();
			cout << endl;
			c = p;
		}
	}
};

int main()
{
	clistp<int,asc<int>> a;
	a.josephus(10, 3);
	//a.show();
}