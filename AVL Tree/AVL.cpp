#include<iostream>
#include"AVLTree definition.h"

using namespace std;

int main() {

	AVLTree my_tree;

	my_tree.push(1);
	my_tree.push(2);
	my_tree.push(3);
	my_tree.push(4);
	my_tree.push(5);
	my_tree.push(6);
	my_tree.push(7);
	my_tree.push(8);

	my_tree.del(7);
	my_tree.del(8);
	my_tree.del(4);
	my_tree.del(5);

	my_tree.print();
	
	return 0;
}