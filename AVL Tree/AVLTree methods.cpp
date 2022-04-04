#include<iostream>
#include"AVLTree definition.h"

using namespace std;

void AVLTree::left_r(node* x) {
	node* y = x->right;
	x->right = y->left;
	if (y->left != nullptr) {
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

	x->balance = x->balance - 1 - max(0, y->balance);
	y->balance = y->balance - 1 + min(0, x->balance);
}

void AVLTree::right_r(node* x) {
	node* y = x->left;
	x->left = y->right;
	if (y->right != nullptr) {
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

	x->balance = x->balance + 1 - min(0, y->balance);
	y->balance = y->balance + 1 + max(0, x->balance);
}

void AVLTree::rebalance(node* n) {
	if ((n->balance < -1) || (n->balance > 1)) {
		if (n->balance > 0) {
			if (n->right->balance < 0) {
				right_r(n->right);
				left_r(n);
			}
			else {
				left_r(n);
			}
		}
		else if (n->balance < 0) {
			if (n->left->balance > 0) {
				left_r(n->left);
				right_r(n);
			}
			else {
				right_r(n);
			}
		}
		return;
	}
	if (n->parent != nullptr) {
		if (n == n->parent->left) {
			n->parent->balance -= 1;
		}
		if (n == n->parent->right) {
			n->parent->balance += 1;
		}
		if (n->parent->balance != 0) {
			rebalance(n->parent);
		}
	}
}

void AVLTree::rebalance2(node* n) {
	if (!((n->balance == 1) || (n->balance == -1))) {
		if ((n->balance < -1) || (n->balance > 1)) {
			if (n->balance > 0) {
				if (n->right->balance < 0) {
					right_r(n->right);
					left_r(n);
				}
				else {
					left_r(n);
				}
			}
			else if (n->balance < 0) {
				if (n->left->balance > 0) {
					left_r(n->left);
					right_r(n);
				}
				else {
					right_r(n);
				}
			}
			n = n->parent;
		}
		if ((n->parent != nullptr) && (n != root)) {
			if (n == n->parent->left) {
				n->parent->balance += 1;
			}
			if (n == n->parent->right) {
				n->parent->balance -= 1;
			}
			rebalance2(n->parent);
			return;
		}
	}
}

node* AVLTree::minimum(node* n) {
	if (n->left == nullptr) {
		return n;
	}
	minimum(n->left);
}

AVLTree::AVLTree() {
	root = nullptr;
}

void AVLTree::push(int data) {
	node* n = new node;
	n->parent = nullptr;
	n->left = nullptr;
	n->right = nullptr;
	n->data = data;
	n->balance = 0;

	node* x = root, * y = nullptr;

	while (x != nullptr) {
		y = x;
		n->data < x->data ? x = x->left : x = x->right;
	}

	n->parent = y;
	if (y == nullptr) {
		root = n;
	}
	else n->data < y->data ? y->left = n : y->right = n;

	rebalance(n);
}

void AVLTree::print_(node* n) {
	if (n != nullptr) {
		cout << "Data: " << n->data << "\n" << "Balance: " << n->balance << "\n\n";
		print_(n->left);
		print_(n->right);
	}
}

void AVLTree::print() {
	print_(root);
}

void AVLTree::del(int data) {
	node* n = root;
	while (n != nullptr) {
		if (data > n->data) {
			n = n->right;
		}
		else if (data < n->data) {
			n = n->left;
		}
		else {
			if ((n->left == nullptr) && (n->right == nullptr)) {
				if (n == n->parent->right) {
					n->parent->right = nullptr;
					n->parent->balance--;
				}
				else {
					n->parent->left = nullptr;
					n->parent->balance++;
				}
				node* tmp = n->parent;
				delete n;
				rebalance2(tmp);
				break;
			}
			else if (n->right == nullptr) {
				n->data = n->left->data;
				n->balance = 0;
				if (n == n->parent->right) {
					n->parent->balance--;
				}
				else {
					n->parent->balance++;
				}
				n->left = nullptr;
				node* tmp = n->parent;
				rebalance2(tmp);
				break;
			}
			else if (n->left == nullptr) {
				n->data = n->right->data;
				n->balance = 0;
				if (n == n->parent->right) {
					n->parent->balance--;
				}
				else {
					n->parent->balance++;
				}
				n->right = nullptr;
				node* tmp = n->parent;
				rebalance2(tmp);
				break;
			}
			else {
				node* x = minimum(n->right);
				n->data = x->data;
				n = n->right;
				data = x->data;
			}
		}
	}
}