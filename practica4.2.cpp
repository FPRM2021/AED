#include "pch.h"
#include <iostream>

using namespace std;

inline int modulo(int a, int n) {
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
	node<T>* prev;
	node(T x) { val = x; next = nullptr; }
};

template<class T, class O>
struct clistp {
	node<T>* head;
	O o;
	clistp() { head = nullptr; };

	bool find(T x, node<T>** &p) {
		p = &head;
		if (!(*p))
			return 0;
		if (o(x, (*p)->val))
			return 0;
		if ((*p)->val == x)
			return 1;
		p = &((*p)->next);
		for (; o((**p).val, x) && (*p) != head; p = &((*p)->next));
		return *p != head && (*p)->val == x;
	}

	bool insert(T x) {
		node<T>** p;
		if (find(x, p))
			return 0;
		node<T>* t = new node<T>(x);
		if (!(*p)) {
			t->next = t;
			t->prev = t;
			(*p) = t;
			return 1;
		}
		else {
			t->next = *p;
			if (o(x, head->val)) {
				*p = t;
				p = &((*p)->next->next);
				while (*p != t->next && *p != (*p)->next)
					p = &((*p)->next);
			}
			t->prev = (*p)->prev;
			(*p)->prev = t;
			*p = t;
		}
		return 1;
	}

	bool remove(T x) {
		node<T>** p;
		if (!find(x, p))
			return 0;
		node<T>* t = *p;
		if (*p == head) {
			if (*p == (*p)->next) {
				head = nullptr;
				delete[] t;
				return 1;
			}
			else {
				*p = (*p)->next;
				(*p)->prev = t->prev;
				while (*p != t)
					p = &((*p)->next);
				*p = t->next;
				delete[] t;
				return 1;
			}
		}
		*p = (*p)->next;
		(*p)->prev = t->prev;
		delete[] t;
		return 1;
	}

	void show() {
		if (head) {
			cout << head->val << " ";
			for (node<T>* i = head->next; i != head && head; i = i->next)
				cout << i->val << " ";
			cout << endl;
			for (node<T>* i = head->prev; i != head && head; i = i->prev)
				cout << i->val << " ";
			cout << head->val << " ";
		}
	}
	~clistp() {
		node<T>*t = head->next;
		while (!(t->next)) {
			node<T>*p = head;
			head = t;
			delete[]p;
			t = t->next;
		}
		delete[]t;
	}

	/*void josephus(int n, int k) {
		for (int i = 1; i <= n; i++)
			insert(T(i));
		show();
		cout << endl;
		node<T>* c = head;
		for (int i = n - 1; i != 0; i--) {
			for (int j = k - 1; j != 0; j--)
				c = c->next;
			node<T>* p = c->next;
			remove(c->val);
			show();
			cout << endl;
			c = p;
		}
	}*/
};

int main()
{
	clistp<int, asc<int>> a;
	a.insert(1);
	a.insert(0);
	a.insert(3);
	a.insert(2);
	a.insert(4);
	a.insert(-2);
	//a.remove(-2);
	a.remove(-2);
	a.remove(3);
	a.insert(5);
	a.remove(1);
	a.remove(5);

	//a.josephus(10, 3);
	a.show();
}