#include"MyDoubleVector.h"
#include<iostream>
#include<iomanip>

using namespace std;

void MyDoubleVector::inputspace() {
	cout << "������ ũ��>>" << endl;
	cin >> space;
}

//�����Ҵ� ��ɾ�
void MyDoubleVector::inputdata() {
	int i;
	for (i = 0; i<space; i++) {
		cout << i+1 << "��° ������ �Է��Ͻÿ�. �Է��� �ߴ��ϰ� ������ ���� :" << endl;
		cin >> data[i];
		if (data[i] < 0) {
			data[i] = NULL;
			break;
		}
		used++;
	}
}

//������ �Է� ��ɾ�
void MyDoubleVector::print() {
	int i;
	for (i = 0; i<used; i++)
		cout << data[i] << " ";

	cout << "�Ҵ���� >>" << space << endl;
	cout << "������ >>" << used << endl;

}
//��¸�ɾ�


int main() {
	MyDoubleVector v;//���� �����ڿ����� �Է�
	v.inputspace();
	v.inputdata();

	MyDoubleVector v1(v);
	v1.print();// ���� �ߵǴ°� �׽�Ʈ
	
	MyDoubleVector v2(v);
	v2.inputspace(); //v2 ���� �Է�
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
	cout << endl<<"�Ҵ�� ����" << v.capacity();
	cout << endl << "����� ����" << v.size()<<endl;
	v.empty();
	v.clear();
	

}