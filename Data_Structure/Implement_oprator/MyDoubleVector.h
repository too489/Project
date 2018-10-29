#pragma once
class MyDoubleVector {
	
public:
	MyDoubleVector();//postcondition 기본생성자
	MyDoubleVector(const MyDoubleVector &Item);
	//copy constructor for deep copy
	MyDoubleVector operator=(MyDoubleVector &Item);
	//postcondition : 값을 복사하여 값들을 변경시키는 복사를 함
	MyDoubleVector operator+=(MyDoubleVector &Item);
	// postcondition :기본 벡터와 추가적인 벡터를 더하여 기존 벡터로 다시 넣음
	MyDoubleVector operator[](MyDoubleVector &Item);
	//postcondition :해당범위에 있는 요소가 출력된다,만약 범위가 벗어난다면 오류메시지 출력 그리고 종료
	MyDoubleVector operator+(const MyDoubleVector &Item);
	//precodition:the sizes of the two operands is the same.
	//postcondition :두 객체들의 벡터를 더하고 그 객체를 출력
	MyDoubleVector operator-(const MyDoubleVector &Item);
	//precodition:the sizes of the two operands is the same.
	//postcondition :두 객체들의 벡터를 빼고 그 객체를 출력
	MyDoubleVector operator* (const MyDoubleVector &Item);
	//precodition:the sizes of the two operands is the same.
	//postcondition :벡터의 곱을 구함
	void operator-();
	//postcondition :단일항일때 각 함수들의 음수들을 출력
	bool operator==(MyDoubleVector &Item);
	//postcondition 두 벡터가 같은지 같지않은지 출력
	void operator()();
	//postcondition:실수형으로 출력
	void reserve(int new_space);
	//postcondition:기존것을 저장함
	void pop_back();
	//postcondition:제일 끝에 있는것을 제거하고 끝에 공간도 하나제거
	void push_back(double x);
	//postcondition:제일 뒤에있는곳에 하나를 추가하고 공간도 하나늘림
	size_t capacity() const;
	//postcondition:공간값을 반환
	size_t size() const;
	//postcondition:사이즈값을 반환
	bool empty() const;
	//postcondition: 벡터전체를 NULL으로 채운다
	void clear();
	//postcondition: 소멸자를 이용하여 끝냄
	void inputspace();
	// 할당공간 주입
	void inputdata();
	// 데이터 주입
	void print();
	//화면에 출력함

	~MyDoubleVector();//postcondition: 소멸자 정의
	
	
private:
	double *data;
	size_t used,space=0,default_space=5;
};
