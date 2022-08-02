#include<iostream>
#include"RBTree definition.h"

int main() {
	RBTree my_tree;

	my_tree.push(13);
	my_tree.push(8);
	my_tree.push(17);
	my_tree.push(1);
	my_tree.push(11);
	my_tree.push(15);
	my_tree.push(25);
	my_tree.push(6);
	my_tree.push(22);
	my_tree.push(27);

	my_tree.del(15);
	my_tree.del(1);
	my_tree.del(22);
	my_tree.del(13);

	my_tree.print();

	return 0;
}