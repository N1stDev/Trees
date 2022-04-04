#include<iostream>
#include"BST definition.h"

using namespace std;

int main() {
	BST my_tree;

	my_tree.push(8);
	my_tree.push(6);
	my_tree.push(4);
	my_tree.push(13);
	my_tree.push(10);
	my_tree.push(100);

	my_tree.del(8);
	my_tree.del(100);
	my_tree.del(6);

	my_tree.print();

	return 0;
}