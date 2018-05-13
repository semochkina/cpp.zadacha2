#include <iostream>
#include "ListWithBufferElement.cpp"

using namespace std;


int main() {
	ListWithBufferElement list;
	cout << "isEmpty() - " << list.isEmpty() << endl;
	cout << "size() - " << list.size() << endl;
	cin >> list;
	cout << "list - " << list << endl;

	list.iterator()->start();
	list.add(23);
	cout << "add 23 - list - " << list << endl;

	cout << "isEmpty() - " << list.isEmpty() << endl;
	cout << "size() - " << list.size() << endl;

	while (list.find(4)) list.remove();
	cout << "remove all 4 - list - " << list << endl;

	cout << "isEmpty() - " << list.isEmpty() << endl;
	cout << "size() - " << list.size() << endl;

	cin.get();
	cin.get();
	return 0;
}