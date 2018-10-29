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
}//다른 벡터가 인자값에 들어올때 deep Copy만 실행하는 생성자

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
// 값을 복사하여 값들을 변경시키는 복사를 함
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

//해당범위에 있는 요소가 출력된다,만약 범위가 벗어난다면 오류메시지 출력 그리고 종료
MyDoubleVector MyDoubleVector::operator+(const MyDoubleVector &Item)
{
	int i;
	MyDoubleVector Plus(Item);// space크기를 같게해주기 위해 item을 복사

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
//두 객체들의 벡터를 더하고 그 객체를 출력
MyDoubleVector MyDoubleVector:: operator-(const MyDoubleVector &Item) {
	int i;
	MyDoubleVector Minor(Item);// space크기를 같게해주기 위해 item을 복사

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

//두 객체들의 벡터를 빼고 그 객체를 출력
MyDoubleVector MyDoubleVector :: operator*(const MyDoubleVector &Item)
{
	int i;
	MyDoubleVector dot(Item);// space크기를 같게해주기 위해 item을 복사

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
//벡터의 곱을 구함
void MyDoubleVector :: operator-() {
	int i;
	for (i = 0; i < used; i++)
	{
		data[i] *= -1;
		
	}
	
}

//단일항일때 각 인자들의 negation을 출력

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

////두 벡터가 같은지 같지않은지 출력
void MyDoubleVector:: operator() () {
	(double)used;
	(double)space;
	(double)default_space;
}
//그벡터값들을 실수형으로 출력//그벡터값들을 실수형으로 출력
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
