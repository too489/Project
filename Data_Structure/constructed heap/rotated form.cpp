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
	/*���翡 �ִ� �ڵ带 �����Ͽ� ��带 ��������ϴ�*/
public:
	/*init_data��� �ʱⰪ�� �޾ƿͼ� �����ڸ� ����������ϴ�*/
	node(const char& init_data, node* init_left = NULL, node* init_right = NULL) {
		set_data(init_data);
		left_field = init_left;
		right_field = init_right;
	}
	/*data�� ������ �� �������� data ����*/
	char& data() { return data_field; }
	/*����� ���� �ڽ� ��带 ȣ�����ִ� ��ɾ ����*/
	node*& left() { return left_field; }
	/*������ ��带 ȣ�����ִ� ��ɾ� ����*/
	node*& right() { return right_field; }
	/*�����͸� �������ִ� �Լ� ����*/
	void set_data(const char& new_data) { data_field = new_data; }
	/*���� �ڽ��� �������ִ� �Լ� ����*/
	void set_left(node* new_left) { left_field = new_left; }
	/*������ �ڽ��� �������ִ� �Լ� ����*/
	void set_right(node* new_right) { right_field = new_right; }
private:
	char data_field;
	node* left_field;
	node* right_field;
	/*�����̺� ������ �� ����*/
};
node* newnode(char entry) {    /*��带 ���� ����� �ʱ�ȭ ���ִ� �Լ�*/
	node* temp = new node(entry, NULL, NULL);
	return temp;
}
void heap_delete(node* denode) {	/*��带 �ʱ�ȭ ���ִ� �Լ� ����*/
	if (denode != NULL) {
		heap_delete(denode->left());
		heap_delete(denode->right());
		delete denode;
		denode = NULL;
		denode = { '\0' };
		}
}
void heap_clear(node* denode) {
	/*����� ������ ���� �����ִ� �Լ� ȣ��*/
	if (denode != NULL) {
		denode->data()=NULL;
	}
}
node* heap_insert(node* innode, char entry) {
	/*���� �������ִ� �Լ��� �����Ͽ����ϴ� ���� ���ʰ� ������ ��尡 ������� ������*/
	if (innode == NULL) {
		new node(entry, NULL, NULL);
		return new node(entry, NULL, NULL);
	}
	/*���� �¿� ��带 ������ �־����ϴ�*/
	else if (innode->left() == NULL) {
		innode->set_left(heap_insert(innode->left(), entry));
	}
	else if (innode->right() == NULL)
	{
		innode->set_right(heap_insert(innode->right(), entry));
	}

	return innode;
}
/*����� ���� ������ ���ִ� �Լ��� ����*/
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
	/*���� ���� �Է¹ޱ����ؼ� char������ buf��� �������ڸ� �ϳ� �����Ͽ����ϴ�
	�׷��� i�� ������ ������ ���� �Է¹ޱ����Ͽ� heapNum��� �迭�� �������־����ϴ�*/
	char buf;
	char heapNum[150] = { '\0' };
	/*150���� ��� �����͸� �����Ͽ� ��Ʈ���� �����Ͽ��־����ϴ�*/
	node* nd[150] = { '\0' };
	/*�б��������� �о�ӽ��ϴ�*/
	ifstream input("input.txt", ios::in);
	input >> TotalSize;/*ù���ڸ� �޾Ƽ� ������� �������־����ϴ�*/

	for (i = 0; i < TotalSize; ) {
		/*�ѱ��� �ѱ��� �޾ƿԽ��ϴ�
		�׷��� ���� I�� �߰��� �Ǹ� �״������ڸ� �о���� ���� �����Ͽ����ϴ�*/
		input >> buf;
		if (buf == 'I') {
			input >> buf;     
			heapNum[i++] = buf;
		}
	}
	int sel;
	/*�������� ���ô� ���� ����<�ҹ���<�빮�� ���� ������ֱ����� ����ġ ���� ť�� ������ ���
	�� ���� ���İ��� �Ϲ� ť�� ��ҽ��ϴ� */
	priority_queue<int> pq0, pqa, pqA;/*�빮�ڿ� �ҹ��ڵ��� ���� �Էµ� �켱���� ť�� ����*/
	int pq0_size = 0, pqa_size = 0, pqA_size = 0;
	for (i = 0; i < TotalSize; i++) {     /*�ѱ��� �ѱ��ھ� ���� �´� ť�� �־�����ϴ�*/
		cout << "heap "<<i<<":" << heapNum[i] << endl;
		if (97 <= (int)heapNum[i])
			sel = 2;
		else if (65 <= (int)heapNum[i])      //�빮��
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
		case(3)://�빮����
			pqA.push(heapNum[i]);
			break;
		}
	}
	/*�׸��� ť�� �ϳ� ����� ���� ���ϴ� ������� �����ϱ� ���� ū������� ť�� ����־����ϴ�*/
	queue<char> Q;
	while (!pqA.empty()) { //�빮��
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

	node* root = NULL;/*��Ʈ ��带 Null������ �����Ͽ����ϴ�*/
	nd[0] = heap_insert(root, Q.front());/*��Ʈ��忡 ť���� ���ڸ� ���� �־� �־����ϴ�*/
	Q.pop();
	/*�̰��� 1���� ���� �� 3��° �������� ���� �������־����ϴ�*/
	for (i = 0; i<2; i++) {
		heap_insert(nd[0], Q.front());
		Q.pop();
	}
	nd[1] = nd[0]->left();
	nd[2] = nd[0]->right();
	for (i = 1; !Q.empty(); ) {
		/*4��° ������ for���� �̿��Ͽ� ť�� �������� �ݺ��ؼ� ���� �����Ͽ����ϴ�*/
		if (!Q.empty()) {
			if (Q.front() == 'd' || Q.front() == 'D') {
				/*�Է¹޴ٰ� d��� ���ڿ��� ���ý� root�� ����� ���� �����ϰ�
				���� �������� ������ ���� ��Ʈ��忡 �����Ѵ���
				������ ����ִ� ��带 ���������־����ϴ�.
				�׷��� ���� reheapification downward�� ������ �־� ������ ���߾����ϴ�*/
				heap_clear(nd[0]);
				Q.pop();
				int ncount;
				ncount = TotalSize - Q.size();
				/*��Ʈ��带 �����ִ� �ڵ��Դϴ�*/
				nd[0]->data() = nd[ncount - 2]->data();
				heap_delete(nd[ncount - 2]);
				if (!Q.empty()) {
					/*������ �Է��Ҷ� d�� �������� �� ������ �Է��ϴ� right����
					������Ÿ� �����Ͽ� �ٽ� ������ right���� �Է����ִ� �ڵ带
					��������ϴ�*/
					--i;
					nd[i]->right() = NULL;
					nd[i] = heap_insert(nd[i], Q.front());
					Q.pop();
					nd[2 * i + 2] = nd[i]->right();
					++i;
				}
				/*�����ڵ�� �������� ���¼������� reheapification downward ���ִ�
				�ڵ��Դϴ�*/
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
		if (!Q.empty()) { /*���� d�� �ȳ������� ���ʺ��� ���� ä���־����ϴ�*/
			nd[i] = heap_insert(nd[i], Q.front());
			Q.pop();
			nd[2 * i + 1] = nd[i]->left();
		}
			if (!Q.empty()) { 
				/*�������� �Ȱ��� �ڵ带 �ɾ��� ������ ���� �迭�Ҷ� �ϳ��ϳ� ��带 ����� �̾��ִ� �ڵ带
				�ۼ��ϴ� ���� ���ʰ� �������� ��ũ�� ���� �ɾ����ϴ� 
				�׷��ٺ��� ���� d�� �Է¹޾�����  ������ ���� �����Ǿ�����
				�׳���ڸ��� �ٽ� ���� �Է¹ޱ����� ���ʰ� �������� ���� �����Ͽ����ϴ�*/
				if (Q.front() == 'd' || Q.front() == 'D') {
					heap_clear(nd[0]);
					Q.pop();
					int ncount;
					ncount = TotalSize - Q.size();
					nd[0]->data() = nd[ncount - 2]->data();
					heap_delete(nd[ncount - 2]);
					if (!Q.empty()) { 
						/*������ �ڽ��� ����� �� ������ ������ ���� �Է¹��� �����ڽ��� upward�Ǳ� ������
						�� �� ��忡 ���� �־��ִ� �ڵ带 ���� �ɾ����ϴ�*/
						--i; nd[i]->left() = NULL;
						nd[i] = heap_insert(nd[i], Q.front());
						Q.pop();
						nd[2 * i + 1] = nd[i]->left();
						++i;
					}
					/*�̰� ���� �����Ǿ����� downward rihification�� ���Ͽ� �������־����ϴ�*/
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

						//�ƴϸ� �ϰ� �빮�� A= 60~90�̸�
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
			/*d�� ������ �ʾ����� ���������� �����U�� ��带 ��ũ��������ϴ�*/
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