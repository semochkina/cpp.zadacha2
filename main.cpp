#include <iostream>
#include "ListWithBufferElement.cpp"

using namespace std;


int main() {
    ListWithBufferElement list;
    list.add(1);
    list.add(9);
    list.add(4);
    list.add(6);

//	list.print(std::cout);
	cout << ">>> " << list << endl;

    cin.get();
    return 0;
}