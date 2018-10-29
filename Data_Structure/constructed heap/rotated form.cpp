#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<string.h>
#include<iomanip>
#include<queue>
#include<cstdlib>

using namespace std;
static int TotalSize = 0;

class node {
	/*교재에 있는 코드를 참조하여 노드를 만들었습니다*/
public:
	/*init_data라는 초기값을 받아와서 생성자를 구현해줬습니다*/
	node(const char& init_data, node* init_left = NULL, node* init_right = NULL) {
		set_data(init_data);
		left_field = init_left;
		right_field = init_right;
	}
	/*data를 얻고싶을 때 쓰기위해 data 구현*/
	char& data() { return data_field; }
	/*노드의 왼쪽 자식 노드를 호출해주는 명령어를 구현*/
	node*& left() { return left_field; }
	/*오른쪽 노드를 호출해주는 명령어 구현*/
	node*& right() { return right_field; }
	/*데이터를 설정해주는 함수 구현*/
	void set_data(const char& new_data) { data_field = new_data; }
	/*왼쪽 자식을 설정해주는 함수 구현*/
	void set_left(node* new_left) { left_field = new_left; }
	/*오른쪽 자식을 설정해주는 함수 구현*/
	void set_right(node* new_right) { right_field = new_right; }
private:
	char data_field;
	node* left_field;
	node* right_field;
	/*프라이빗 데이터 값 지정*/
};
node* newnode(char entry) {    /*노드를 새로 만들고 초기화 해주는 함수*/
	node* temp = new node(entry, NULL, NULL);
	return temp;
}
void heap_delete(node* denode) {	/*노드를 초기화 해주는 함수 구현*/
	if (denode != NULL) {
		heap_delete(denode->left());
		heap_delete(denode->right());
		delete denode;
		denode = NULL;
		denode = { '\0' };
		}
}
void heap_clear(node* denode) {
	/*노드의 데이터 값을 지워주는 함수 호출*/
	if (denode != NULL) {
		denode->data()=NULL;
	}
}
node* heap_insert(node* innode, char entry) {
	/*힙을 삽입해주는 함수를 구현하였습니다 만약 왼쪽과 오른쪽 노드가 비었을때 값설정*/
	if (innode == NULL) {
		new node(entry, NULL, NULL);
		return new node(entry, NULL, NULL);
	}
	/*각각 좌우 노드를 설정해 주었습니다*/
	else if (innode->left() == NULL) {
		innode->set_left(heap_insert(innode->left(), entry));
	}
	else if (innode->right() == NULL)
	{
		innode->set_right(heap_insert(innode->right(), entry));
	}

	return innode;
}
/*노드의 값을 프린터 해주는 함수를 구현*/
void treePrint(node* root, int depth)
{
	if (root != NULL) {
		treePrint(root->right(), depth + 1);
		cout << setw(2 * depth) << "" << root->data() << endl;
		treePrint(root->left(), depth + 1);
	}
}

int main() {

	int i = 0, Hcount = 0;
	/*한자 한자 입력받기위해서 char형으로 buf라는 변수인자를 하나 생성하였습니다
	그러고 i를 제외한 값들을 따로 입력받기위하여 heapNum라는 배열을 생성해주었습니다*/
	char buf;
	char heapNum[150] = { '\0' };
	/*150개의 노드 포인터를 생성하여 힙트리에 설정하여주었습니다*/
	node* nd[150] = { '\0' };
	/*읽기전용으로 읽어왓습니다*/
	ifstream input("input.txt", ios::in);
	input >> TotalSize;/*첫글자만 받아서 사이즈로 지정해주었습니다*/

	for (i = 0; i < TotalSize; ) {
		/*한글자 한글자 받아왔습니다
		그러고 만약 I가 발견이 되면 그다음글자를 읽어오는 것을 구현하였습니다*/
		input >> buf;
		if (buf == 'I') {
			input >> buf;     
			heapNum[i++] = buf;
		}
	}
	int sel;
	/*과제에서 보시다 시피 숫자<소문자<대문자 순을 만들어주기위해 스위치 문과 큐를 적절히 섞어서
	그 최종 정렬값을 일반 큐에 담았습니다 */
	priority_queue<int> pq0, pqa, pqA;/*대문자와 소문자들이 각각 입력될 우선순위 큐를 구현*/
	int pq0_size = 0, pqa_size = 0, pqA_size = 0;
	for (i = 0; i < TotalSize; i++) {     /*한글자 한글자씩 각자 맞는 큐에 넣어줬습니다*/
		cout << "heap "<<i<<":" << heapNum[i] << endl;
		if (97 <= (int)heapNum[i])
			sel = 2;
		else if (65 <= (int)heapNum[i])      //대문자
			sel = 3;
		else
			sel = 1;



		switch (sel) {
		case(1):
			pq0.push(heapNum[i]);
			break;
		case(2):
			pqa.push(heapNum[i]);
			break;
		case(3)://대문자임
			pqA.push(heapNum[i]);
			break;
		}
	}
	/*그리고 큐를 하나 만들어 저희가 원하는 순서대로 정렬하기 위해 큰순서대로 큐에 집어넣었습니다*/
	queue<char> Q;
	while (!pqA.empty()) { //대문자
		Q.push(pqA.top());
		pqA.pop();
	}
	while (!pqa.empty()) {
		Q.push(pqa.top());
		pqa.pop();
	}
	while (!pq0.empty()) {
		Q.push(pq0.top());
		pq0.pop();
	}

	node* root = NULL;/*루트 노드를 Null값으로 설정하였습니다*/
	nd[0] = heap_insert(root, Q.front());/*루트노드에 큐에서 한자를 빼와 넣어 주었습니다*/
	Q.pop();
	/*이것을 1행의 인자 즉 3번째 노드까지는 직접 지정해주었습니다*/
	for (i = 0; i<2; i++) {
		heap_insert(nd[0], Q.front());
		Q.pop();
	}
	nd[1] = nd[0]->left();
	nd[2] = nd[0]->right();
	for (i = 1; !Q.empty(); ) {
		/*4번째 노드부터 for문을 이용하여 큐가 빌때까지 반복해서 힙을 구현하였습니다*/
		if (!Q.empty()) {
			if (Q.front() == 'd' || Q.front() == 'D') {
				/*입력받다가 d라는 문자열이 나올시 root의 노드의 값을 삭제하고
				제일 마지막에 들어오는 값을 루트노드에 설정한다음
				마지막 비어있는 노드를 삭제시켜주었습니다.
				그러고 난뒤 reheapification downward을 진행해 주어 정렬을 맞추었습니다*/
				heap_clear(nd[0]);
				Q.pop();
				int ncount;
				ncount = TotalSize - Q.size();
				/*루트노드를 없애주는 코드입니다*/
				nd[0]->data() = nd[ncount - 2]->data();
				heap_delete(nd[ncount - 2]);
				if (!Q.empty()) {
					/*왼쪽을 입력할때 d가 나왔으면 그 전까지 입력하던 right값이
					비어질거를 예상하여 다시 그전의 right값을 입력해주는 코드를
					만들었습니다*/
					--i;
					nd[i]->right() = NULL;
					nd[i] = heap_insert(nd[i], Q.front());
					Q.pop();
					nd[2 * i + 2] = nd[i]->right();
					++i;
				}
				/*다음코드는 과제에서 나온순서데로 reheapification downward 해주는
				코드입니다*/
				int l, q;
				for (q = 2, l = 1; nd[q-1] != NULL;)
				{
					int root;
					root = nd[l - 1]->data();
					int child;
					child = nd[q - 1]->data();

					if (0 <= root && root <= 9)
					{
						if (root < child)
							swap(nd[q - 1]->data(), nd[l - 1]->data());
						else
							break;
					}

					
					else if (65 <= root && root <= 90)
					{
						if (0 <= child && child <= 90)
						{
							if (child > root)
							{
								swap(nd[q - 1]->data(), nd[l - 1]->data());

							}
							else
								break;
						}
						else
							break;
					}
					else
					{
						if (65 <= child && child <= 90)
							swap(nd[q - 1]->data(), nd[l - 1]->data());
						else {
							if (child > root)
							{
								swap(nd[q - 1]->data(), nd[l - 1]->data());

							}
							else
								break;
						}
					}
					q = q * 2;
					l = l * 2;
				}
			}
		}
		if (!Q.empty()) { /*만약 d가 안나왔으면 왼쪽부터 힙을 채워주었습니다*/
			nd[i] = heap_insert(nd[i], Q.front());
			Q.pop();
			nd[2 * i + 1] = nd[i]->left();
		}
			if (!Q.empty()) { 
				/*위에서와 똑같은 코드를 심어준 이유는 힙을 배열할때 하나하나 노드를 만들고 이어주는 코드를
				작성하다 보니 왼쪽과 오른쪽의 링크를 따로 심었습니다 
				그러다보니 만약 d를 입력받았을때  그전에 값이 삭제되었을때
				그노드자리에 다시 값을 입력받기위해 왼쪽과 오른쪽을 나눠 설정하였습니다*/
				if (Q.front() == 'd' || Q.front() == 'D') {
					heap_clear(nd[0]);
					Q.pop();
					int ncount;
					ncount = TotalSize - Q.size();
					nd[0]->data() = nd[ncount - 2]->data();
					heap_delete(nd[ncount - 2]);
					if (!Q.empty()) { 
						/*오른쪽 자식을 만들기 전 오류가 났으면 전에 입력받은 왼쪽자식이 upward되기 때문에
						그 빈 노드에 값을 넣어주는 코드를 따로 심었습니다*/
						--i; nd[i]->left() = NULL;
						nd[i] = heap_insert(nd[i], Q.front());
						Q.pop();
						nd[2 * i + 1] = nd[i]->left();
						++i;
					}
					/*이것 또한 삭제되었을때 downward rihification을 위하여 설정해주었습니다*/
					int l, q;
					for (q = 2, l = 1; nd[i] != '\0';)
					{
						int root;
						root = nd[l - 1]->data();
						int child;
						child = nd[q - 1]->data();

						if (0 <= root && root <= 9)
						{
							if (root < child)
								swap(nd[q - 1]->data(), nd[l - 1]->data());
							else
								break;
						}

						//아니면 니가 대문자 A= 60~90이면
						else if (65 <= root && root <= 90)
						{
							if (0 <= child && child <= 90)
							{
								if (child > root)
								{
									swap(nd[q - 1]->data(), nd[l - 1]->data());

								}
								else
									break;
							}
							else
								break;
						}
						else
						{
							if (65 <= child && child <= 90)
								swap(nd[q - 1]->data(), nd[l - 1]->data());
							else {
								if (child > root)
								{
									swap(nd[q - 1]->data(), nd[l - 1]->data());

								}
								else
									break;
							}
						}
						q = q * 2;
						l = l * 2;
					}
				}
			}
			/*d가 들어오지 않았으면 정상적으로 오른쪾에 노드를 링크시켜줬습니다*/
			if (!Q.empty()) { 
				nd[i] = heap_insert(nd[i], Q.front());
				Q.pop();
				nd[2 * i + 2] = nd[i]->right();
			}
			i++;
		}
	treePrint(nd[0], 0);
	system("pause");
	return 0;
}