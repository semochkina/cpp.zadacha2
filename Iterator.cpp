// итератор
class Iterator {
public:
	// начать работу
	virtual void start() = 0;

	// получить очередной элемент
	virtual int getValue() = 0;

	// сдвинуть итератор на следующий елемент
	virtual void next() = 0;

	// проверка все ли проитерировано
	virtual bool finish() = 0;
};
