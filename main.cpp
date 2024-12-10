#include "iostream"
#include "LinkedList.cpp"

LinkedList<std::string> get_path_list(int elm) {
	std::cout << "Input path: ";
	char input[400];
	char token[50];
	char delimiter = '\\';
	LinkedList<std::string> list;
	std::cin.getline(input, 200); 


	char* ptr = strtok(input, &delimiter);

	while (ptr != nullptr) { 
		strncpy(token, ptr, 50 - 1);
		token[50 - 1] = '\0'; 
		std::string str(token);
		Node<std::string> elm(str);
		list.push_tail(elm);
		std::cout << str << std::endl;
		ptr = strtok(nullptr, &delimiter);
	}
	std::cout << list << '\n';
	return list;

}

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
	std::cout << "mannn" << '\n';
	LinkedList<std::string> listx;
	listx = get_path_list(4);
	int res = system("chcp 65001 > nul");
	listx.open_file();

	LinkedList<int> rand_list(5);
	std::cout << "Rand list CTOR " << rand_list << '\n';

}