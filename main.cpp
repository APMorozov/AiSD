#include "iostream"
#include "LinkedList.cpp"

int main(){
	LinkedList<int> list;
	Node<int> elm1(10);
	Node<int> elm2(34);
	Node<int> elm3(54);
	list.push_tail(elm1);
	list.push_tail(elm2);
	list.push_tail(elm3);
	LinkedList<int> list2(list);
	std::cout << list2 << " -list2" << '\n';
	std::cout << list << '\n';
	Node<int> elm4(55);
	list.push_tail(elm4);
	std::cout << list << '\n';
	list = list2;
	std::cout << "list after: " << list << '\n';
	list.push_tail(elm4);
	list.push_tail(list2);
	std::cout << "list after push: " << list << '\n';
	list.pop_tail();
	std::cout << "list after pop: " << list << '\n';
	list.pop_head();
	std::cout << "list after pop head: " << list << '\n';
	list.push_head(elm4);
	std::cout << "list after push head: " << list << '\n';
	list.push_head(list2);
	std::cout << "list after push head list: " << list << '\n';
	list.delete_node(elm2);
	std::cout << "list after delete node: " << list << '\n';
	list.set_by_idx(elm2,6);
	std::cout << "list after set node by idx: " << list << '\n';
	std::cout << "mannn";
}