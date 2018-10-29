#include"MyDoubleVector.h"
#include<iostream>
#include<iomanip>

using namespace std;

MyDoubleVector::MyDoubleVector() {
	data = new double[default_space];
	space = default_space;
	used = 0;
}

MyDoubleVector::MyDoubleVector(const MyDoubleVector &Item) {
	data = new double[Item.space];
	space = Item.space;
	used = Item.used;
	copy(Item.data, (Item.data) + used, data);
}//�ٸ� ���Ͱ� ���ڰ��� ���ö� deep Copy�� �����ϴ� ������

MyDoubleVector MyDoubleVector::operator=(MyDoubleVector &Item) {
	double *new_data;
	if (this == &Item)
		return *this;
	if (space != Item.space)
	{
		new_data = new double[Item.space];
		delete[] data;
		data = new_data;
		space = Item.space;
	}
	used = Item.used;
	copy(Item.data, (Item.data) + used, data);
	return *this;
}
// ���� �����Ͽ� ������ �����Ű�� ���縦 ��
MyDoubleVector MyDoubleVector::operator+=(MyDoubleVector &addend) {
	if (used + addend.used > space)
		reserve(used + addend.used);
	copy(addend.data, addend.data + addend.used, data + used);
	used += addend.used;
	return addend;
}

MyDoubleVector MyDoubleVector::operator[](MyDoubleVector &Item)
{
	int n;
	cout << "Requests position" << endl;
	cin >> n;
	if (n <= used&&n > 0)
		cout << data[n-1];
	else {
		cout << "you inputs integers that is out of range" << endl;
		exit(-1);
	}

}

//�ش������ �ִ� ��Ұ� ��µȴ�,���� ������ ����ٸ� �����޽��� ��� �׸��� ����
MyDoubleVector MyDoubleVector::operator+(const MyDoubleVector &Item)
{
	int i;
	MyDoubleVector Plus(Item);// spaceũ�⸦ �������ֱ� ���� item�� ����

	if (space == Item.space)
	{
		for (i = 0; i < space; i++) {
			Plus.data[i] = data[i] + Item.data[i];
		}
		for (i = 0; i < space; i++)
			if (Plus.data[i] != NULL)
				Plus.used = i;
	}
	return Plus;
}
//�� ��ü���� ���͸� ���ϰ� �� ��ü�� ���
MyDoubleVector MyDoubleVector:: operator-(const MyDoubleVector &Item) {
	int i;
	MyDoubleVector Minor(Item);// spaceũ�⸦ �������ֱ� ���� item�� ����

	if (space == Item.space)
	{
		for (i = 0; i < space; i++) {
			Minor.data[i] = data[i] - Item.data[i];
		}
		for (i = 0; i < space; i++)
			if (Minor.data[i] != NULL)
				Minor.used = i;
	}
	return Minor;
}

//�� ��ü���� ���͸� ���� �� ��ü�� ���
MyDoubleVector MyDoubleVector :: operator*(const MyDoubleVector &Item)
{
	int i;
	MyDoubleVector dot(Item);// spaceũ�⸦ �������ֱ� ���� item�� ����

	if (space == Item.space)
	{
		for (i = 0; i < space; i++) {
			dot.data[i] = data[i] * Item.data[i];
		}
		for (i = 0; i < space; i++)
			if (dot.data[i] != NULL)
				dot.used = i;
	}
	return dot;
}
//������ ���� ����
void MyDoubleVector :: operator-() {
	int i;
	for (i = 0; i < used; i++)
	{
		data[i] *= -1;
		
	}
	
}

//�������϶� �� ���ڵ��� negation�� ���

bool MyDoubleVector:: operator==(MyDoubleVector &Item)
{

	if (space == Item.space)
	{
		int i;
		for (i = 0; i < space; i++)
		{
			if (data[i] != Item.data[i])
				return false;
			else
				return true;
		}

	}
}

////�� ���Ͱ� ������ ���������� ���
void MyDoubleVector:: operator() () {
	(double)used;
	(double)space;
	(double)default_space;
}
//�׺��Ͱ����� �Ǽ������� ���//�׺��Ͱ����� �Ǽ������� ���
void MyDoubleVector::pop_back()
{
	data[used] = NULL;
	--used;
	--space;
}
void MyDoubleVector::push_back(double x)
{
	++used;
	++space;
	data[used + 1] = x;
}

size_t MyDoubleVector::capacity() const
{
	return space;
}

size_t MyDoubleVector::size() const {
	return used;
}
bool MyDoubleVector::empty() const
{
	if (space != 0) {
		int i;
		for (i = 0; i < space; i++)
		{
			data[i] = NULL;
		}
		return true;
	}
	else
		return false;
}

void MyDoubleVector::clear()
{
	MyDoubleVector::~MyDoubleVector();
	space = NULL;
	used = NULL;
}

void MyDoubleVector::reserve(int new_space) {
	double *larger_array;
	if (new_space == space) return;
	if (new_space < used)
		new_space = used;

	larger_array = new double[new_space];
	copy(data, data + used, larger_array);
	delete[] data;
	data = larger_array;
	space = new_space;
}

MyDoubleVector::~MyDoubleVector() { }
