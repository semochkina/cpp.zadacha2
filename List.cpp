#include "Iterator.cpp"

// ������
class List {
public:
	// �������� ������� � �������, ���������� ����������
	virtual void add(int x) = 0;

	// ������� ������� ������� (true - �������, false - ������ ��� ��� ����)
	virtual bool remove() = 0;

	// ������ ������ ��������� (true - �����, false - ���)
	virtual bool find(int x) = 0;

	// �������� ������
	virtual void clear() = 0;

	// ��������� ������ �� �������
	virtual bool isEmpty() = 0;

	// ���������� ��������� � ������
	virtual int size() = 0;

	// �������� �������� �� ������ ������� ������
	virtual Iterator *iterator() = 0;

};