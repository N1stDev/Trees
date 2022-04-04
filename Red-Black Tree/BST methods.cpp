#include<iostream>
#include"BST definition.h"

using namespace std;

void BST::print_(node* n) {
	if (n != nullptr) {
		cout << "Data: " << n->data << "\n\n";
		print_(n->left);
		print_(n->right);
	}
}

node* BST::minimum(node* n) {
	if (n->left == nullptr) {
		return n;
	}
	minimum(n->left);
}

void BST::del(int data) {
	node* n = root, *y = nullptr;

	while (n != nullptr) {
		if (data > n->data) {
			y = n;
			n = n->right;
		}
		else if (data < n->data) {
			y = n;
			n = n->left;
		}
		else {
			if ((n->left == nullptr) && (n->right == nullptr)) {
				if (y == nullptr) {
					root = nullptr;
				}
				else {
					n == y->left ? y->left = nullptr : y->right = nullptr;
				}
				break;
			}
			else if (n->right == nullptr) {
				n->data = n->left->data;
				n->left = nullptr;
				break;
			}
			else if (n->left == nullptr) {
				n->data = n->right->data;
				n->right = nullptr;
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

void BST::push(int data) {
	node* n = new node;
	n->left = nullptr;
	n->right = nullptr;
	n->data = data;

	node* x = root, * y=nullptr;
	while (x != nullptr) {
		y = x;
		n->data < x->data ? x = x->left : x = x->right;
	}
	
	if (y == nullptr) {
		root = n;
	}
	else n->data < y->data ? y->left = n : y->right = n;
}

void BST::print() {
	print_(root);
}

BST::BST() {
	root = nullptr;
}