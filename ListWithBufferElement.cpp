#include <iosfwd>
#include <iostream>
#include "List.cpp"

// —труктура €вл€юща€с€ звеном списка
struct Node {
	// «начение value будет передаватьс€ в список
	int value;
	// ”казатели на адреса следующего и предыдущего элементов списка
	Node *next, *prev;

	Node() {
		next = prev = this;
	}
};

// класс-реализаци€ списка (закольцованный список с буферным элементом)
class ListWithBufferElement : public List {
	// буферный элемент
	Node bufferNode;
	// количество элементов
	int count = 0;

	class IteratorRealization : public Iterator {
		// буферный элемент
		Node *bufferNode2;
		// текущий элемент
		Node *currNode;

	public:
		IteratorRealization(Node *bufferNode) : bufferNode2(bufferNode) {
			start();
		}

		Node *curr() {
			return currNode;
		}

		void start() override {
			currNode = bufferNode2->next;
		}

		int getValue() override {
			return currNode->value;
		}

		void next() override {
			if (currNode != bufferNode2) currNode = currNode->next;
		}

		bool finish() override {
			return currNode == bufferNode2;
		}
	};

	// итератор
	IteratorRealization *iter;

	void init() {
		bufferNode.prev = bufferNode.next = &bufferNode;
		iter = new IteratorRealization(&bufferNode);
		//        std::cout << "init() " << *this << "\n";
	}

	void copyList(ListWithBufferElement &other) {
		if (!other.isEmpty()) {
			for (Node *node = other.bufferNode.next; node != &other.bufferNode; node = node->next)
				add(node->value);
		}
	}

	void moveList(ListWithBufferElement &other) {
		if (!other.isEmpty()) {
			Node *otherNode = &other.bufferNode;
			bufferNode.prev = otherNode->prev;
			bufferNode.next = otherNode->next;
			count = other.count;

			// чистим 
			otherNode->prev = otherNode->next = otherNode;
			other.count = 0;
		}
	}

public:
	ListWithBufferElement() {
		init();
	}

	// конструктор - копировани€
	ListWithBufferElement(ListWithBufferElement &other) {
		init();
		copyList(other);
	}

	// конструктор - перемещение
	ListWithBufferElement(ListWithBufferElement &&other) {
		init();
		moveList(other);
	}

	// оператор присваивани€ (lvalue-ссылка на экземпл€р этого же класса)
	ListWithBufferElement &operator=(ListWithBufferElement &other) {
		if (this != &other) {
			clear();
			copyList(other);
		}
		return *this;
	}

	// оператор перемещени€ (rvalue-ссылка на экземпл€р этого же класса)
	ListWithBufferElement &operator=(ListWithBufferElement &&other) {
		if (this != &other) {
			clear();
			// перемещаем
			moveList(other);
		}
		return *this;
	}

	~ListWithBufferElement() {
		clear();
		delete iter;
	}


	void add(int x) override {
		Node *curr = iter->curr();

		Node *newNode = new Node;
		newNode->value = x;
		newNode->prev = curr->prev;
		newNode->next = curr;

		curr->prev->next = newNode;
		curr->prev = newNode;

		count++;
	}

	bool remove() override {
		if (iter->finish()) return false;

		Node *curr = iter->curr();

		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;

		delete curr;

		count--;
		return true;
	}

	bool find(int x) override {
		iter->start();
		while (!iter->finish()) {
			if (iter->getValue() == x) {
				return true;
			}
			iter->next();
		}
		return false;
	}

	void clear() override {
		//        std::cout << "clear()" << *this << "\n";
		if (!isEmpty()) {
			// очищаем список
			for (Node *node = bufferNode.next; node != &bufferNode;) {
				Node *node2 = node;
				node = node->next;
				delete node2;
			}
			bufferNode.prev = bufferNode.next = &bufferNode;
			count = 0;
			iter->start();
		}
	}

	bool isEmpty() override {
		return count == 0;
	}

	int size() override {
		return count;
	}

	Iterator *iterator() override {
		iter->start();
		return iter;
	}

	friend std::ostream &operator<<(std::ostream &os, const ListWithBufferElement &element) {
		os << " count: " << element.count << "   elements";
		for (Node *node = element.bufferNode.next; node != &element.bufferNode; node = node->next)
			os << ", " << node->value;
		return os;
	}

	friend std::istream &operator>>(std::istream &is, ListWithBufferElement &element) {
		std::cout << "add 3 values:\n";
		for (int i = 0; i < 3; i++) {
			std::cout << "mas[" << i << "] > ";
			int m;
			is >> m;
			element.add(m);
		}
		return is;
	}
};
