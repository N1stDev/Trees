#pragma once

struct node {
	int data;
	bool color;
	node* parent;
	node* left;
	node* right;
};

class RBTree {
	node* root;
	node* NULL_N;
	
	void rebalance_del(node* n);

	void rebalance_push(node* n);

	void left_r(node* x);

	void right_r(node* x);

	void transplant(node* x, node* y);

	node* minimum(node* n);

	void print_(node* n);

public:
	RBTree();

	void push(int data);

	void del(int data);

	void print();
};