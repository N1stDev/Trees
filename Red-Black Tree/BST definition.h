#pragma once

struct node {
	node* left;
	node* right;
	int data;
};

class BST {
	node* root;

	void print_(node* root);

	node* minimum(node* root);

public:
	BST();

	void del(int data);

	void push(int data);

	void print();
};