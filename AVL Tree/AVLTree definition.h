#pragma once

struct node {
	int data;
	int balance;
	node* left;
	node* right;
	node* parent;
};

class AVLTree {
	node* root;

	void left_r(node* x);

	void right_r(node* x);

	void rebalance(node* n);

	void rebalance2(node* n);
	
	node* minimum(node* n);

	void print_(node* n);

public:
	AVLTree();

	void push(int data);

	void print();

	void del(int data);
};
