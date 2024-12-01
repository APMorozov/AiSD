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
	std::cout << list << '\n';


	std::cout << "mannn";
}