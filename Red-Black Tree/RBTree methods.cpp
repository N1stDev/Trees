#include<iostream>
#include"RBTree definition.h"

using namespace std;

void RBTree::rebalance_del(node* n) {
	node* s;
	while (n != root && n->color == 0) {
		if (n == n->parent->left) {
			s = n->parent->right;
			if (s->color == 1) {
				s->color = 0;
				n->parent->color = 1;
				left_r(n->parent);
				s = n->parent->right;
			}

			if (s->left->color == 0 && s->right->color == 0) {
				s->color = 1;
				n = n->parent;
			}
			else {
				if (s->right->color == 0) {
					s->left->color = 0;
					s->color = 1;
					right_r(s);
					s = n->parent->right;
				}
				s->color = n->parent->color;
				n->parent->color = 0;
				s->right->color = 0;
				left_r(n->parent);
				n = root;
			}
		}
		else {
			s = n->parent->left;
			if (s->color == 1) {
				s->color = 0;
				n->parent->color = 1;
				right_r(n->parent);
				s = n->parent->left;
			}

			if (s->right->color == 0 && s->left->color == 0) {
				s->color = 1;
				n = n->parent;
			}
			else {
				if (s->left->color == 0) {
					s->right->color = 0;
					s->color = 1;
					left_r(s);
					s = n->parent->left;
				}
				s->color = n->parent->color;
				n->parent->color = 0;
				s->left->color = 0;
				right_r(n->parent);
				n = root;
			}
		}
	}
	n->color = 0;
}

void RBTree::rebalance_push(node* n) {
	node* u;
	while (n->parent->color == 1) {
		if (n->parent == n->parent->parent->right) {
			u = n->parent->parent->left;
			if (u->color == 1) {
				u->color = 0;
				n->parent->color = 0;
				n->parent->parent->color = 1;
				n = n->parent->parent;
			}
			else {
				if (n == n->parent->left) {
					n = n->parent;
					right_r(n);
				}
				n->parent->color = 0;
				n->parent->parent->color = 1;
				left_r(n->parent->parent);
			}
		}
		else {
			u = n->parent->parent->right;

			if (u->color == 1) {
				u->color = 0;
				n->parent->color = 0;
				n->parent->parent->color = 1;
				n = n->parent->parent;
			}
			else {
				if (n == n->parent->right) {
					n = n->parent;
					left_r(n);
				}
				n->parent->color = 0;
				n->parent->parent->color = 1;
				right_r(n->parent->parent);
			}
		}
		if (n == root) {
			break;
		}
	}
	root->color = 0;
}

void RBTree::left_r(node* x) {
	node* y = x->right;
	x->right = y->left;
	if (y->left != NULL_N) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void RBTree::right_r(node* x) {
	node* y = x->left;
	x->left = y->right;
	if (y->right != NULL_N) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	}
	else if (x == x->parent->right) {
		x->parent->right = y;
	}
	else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

void RBTree::transplant(node* x, node* y) {
	if (x->parent == nullptr) {
		root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->parent = x->parent;
}

node* RBTree::minimum(node* n) {
	while (n->left != NULL_N) {
		n = n->left;
	}
	return n;
}

RBTree::RBTree() {
	NULL_N = new node;
	NULL_N->color = 0;
	NULL_N->left = nullptr;
	NULL_N->right = nullptr;
	root = NULL_N;
}

void RBTree::push(int data) {
	node* n = new node;
	n->parent = nullptr;
	n->data = data;
	n->left = NULL_N;
	n->right = NULL_N;
	n->color = 1;

	node* y = nullptr;
	node* x = root;

	while (x != NULL_N) {
		y = x;
		if (n->data < x->data) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	n->parent = y;
	if (y == nullptr) {
		root = n;
	}
	else if (n->data < y->data) {
		y->left = n;
	}
	else {
		y->right = n;
	}

	if (n->parent == nullptr) {
		n->color = 0;
		return;
	}

	if (n->parent->parent == nullptr) {
		return;
	}
	rebalance_push(n);
}

void RBTree::del(int data) {
	node* n = root;
	node* x, * y;
	while (n != NULL_N) {
		if (n->data == data) {
			n = n;
			break;
		}
		else if (n->data < data) {
			n = n->right;
		}
		else {
			n = n->left;
		}
	}

	if (n == NULL_N) {
		return;
	}

	bool nec_color = n->color;
	if (n->left == NULL_N) {
		x = n->right;
		transplant(n, n->right);
	}
	else if (n->right == NULL_N) {
		x = n->left;
		transplant(n, n->left);
	}
	else {
		y = minimum(n->right);
		nec_color = y->color;
		x = y->right;
		if (y->parent == n) {
			x->parent = y;
		}
		else {
			transplant(y, y->right);
			y->right = n->right;
			y->right->parent = y;
		}

		transplant(n, y);
		y->left = n->left;
		y->left->parent = y;
		y->color = n->color;
	}
	delete n;
	if (nec_color == 0) {
		rebalance_del(x);
	}
}

void RBTree::print_(node* n) {
	if (n != NULL_N) {
		cout << "Data: " << n->data << "\n" << "IsRed: " << n->color << "\n\n";
		print_(n->left);
		print_(n->right);
	}
}

void RBTree::print() {
	print_(root);
}