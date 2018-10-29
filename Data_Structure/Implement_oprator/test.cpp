#include"MyDoubleVector.h"
#include<iostream>
#include<iomanip>

using namespace std;

void MyDoubleVector::inputspace() {
	cout << "공간의 크기>>" << endl;
	cin >> space;
}

//공간할당 명령어
void MyDoubleVector::inputdata() {
	int i;
	for (i = 0; i<space; i++) {
		cout << i+1 << "번째 수를를 입력하시오. 입력을 중단하고 싶으면 음수 :" << endl;
		cin >> data[i];
		if (data[i] < 0) {
			data[i] = NULL;
			break;
		}
		used++;
	}
}

//데이터 입력 명령어
void MyDoubleVector::print() {
	int i;
	for (i = 0; i<used; i++)
		cout << data[i] << " ";

	cout << "할당공간 >>" << space << endl;
	cout << "사용공간 >>" << used << endl;

}
//출력명령어


int main() {
	MyDoubleVector v;//최초 생성자에서만 입력
	v.inputspace();
	v.inputdata();

	MyDoubleVector v1(v);
	v1.print();// 복사 잘되는가 테스트
	
	MyDoubleVector v2(v);
	v2.inputspace(); //v2 따로 입력
	v2.inputdata();

	v.operator+=(v1);
	v.operator+(v1);
	v.operator[](v1);
	v.operator=(v1);
	v.operator-(v1);
	v.operator*(v1);
	v.operator-();
	v.operator==(v1);
	v.operator()();
	v.reserve(10);
	v.pop_back();
	v.push_back(100);
	cout << endl<<"할당된 공간" << v.capacity();
	cout << endl << "사용한 공간" << v.size()<<endl;
	v.empty();
	v.clear();
	

}