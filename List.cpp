#include "Iterator.cpp"

// Список
class List {
public:
	// добавить элемент в позицию, отмеченную итератором
	virtual void add(int x) = 0;

	// удалить текущий элемент (true - удалили, false - список уже был пуст)
	virtual bool remove() = 0;

	// искать первое вхождение (true - нашли, false - нет)
	virtual bool find(int x) = 0;

	// очистить список
	virtual void clear() = 0;

	// проверить список на пустоту
	virtual bool isEmpty() = 0;

	// количество елементов в списке
	virtual int size() = 0;

	// получить итератор на первый елемент списка
	virtual Iterator *iterator() = 0;

};