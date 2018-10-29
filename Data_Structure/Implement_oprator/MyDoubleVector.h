#pragma once
class MyDoubleVector {
	
public:
	MyDoubleVector();//postcondition �⺻������
	MyDoubleVector(const MyDoubleVector &Item);
	//copy constructor for deep copy
	MyDoubleVector operator=(MyDoubleVector &Item);
	//postcondition : ���� �����Ͽ� ������ �����Ű�� ���縦 ��
	MyDoubleVector operator+=(MyDoubleVector &Item);
	// postcondition :�⺻ ���Ϳ� �߰����� ���͸� ���Ͽ� ���� ���ͷ� �ٽ� ����
	MyDoubleVector operator[](MyDoubleVector &Item);
	//postcondition :�ش������ �ִ� ��Ұ� ��µȴ�,���� ������ ����ٸ� �����޽��� ��� �׸��� ����
	MyDoubleVector operator+(const MyDoubleVector &Item);
	//precodition:the sizes of the two operands is the same.
	//postcondition :�� ��ü���� ���͸� ���ϰ� �� ��ü�� ���
	MyDoubleVector operator-(const MyDoubleVector &Item);
	//precodition:the sizes of the two operands is the same.
	//postcondition :�� ��ü���� ���͸� ���� �� ��ü�� ���
	MyDoubleVector operator* (const MyDoubleVector &Item);
	//precodition:the sizes of the two operands is the same.
	//postcondition :������ ���� ����
	void operator-();
	//postcondition :�������϶� �� �Լ����� �������� ���
	bool operator==(MyDoubleVector &Item);
	//postcondition �� ���Ͱ� ������ ���������� ���
	void operator()();
	//postcondition:�Ǽ������� ���
	void reserve(int new_space);
	//postcondition:�������� ������
	void pop_back();
	//postcondition:���� ���� �ִ°��� �����ϰ� ���� ������ �ϳ�����
	void push_back(double x);
	//postcondition:���� �ڿ��ִ°��� �ϳ��� �߰��ϰ� ������ �ϳ��ø�
	size_t capacity() const;
	//postcondition:�������� ��ȯ
	size_t size() const;
	//postcondition:������� ��ȯ
	bool empty() const;
	//postcondition: ������ü�� NULL���� ä���
	void clear();
	//postcondition: �Ҹ��ڸ� �̿��Ͽ� ����
	void inputspace();
	// �Ҵ���� ����
	void inputdata();
	// ������ ����
	void print();
	//ȭ�鿡 �����

	~MyDoubleVector();//postcondition: �Ҹ��� ����
	
	
private:
	double *data;
	size_t used,space=0,default_space=5;
};
