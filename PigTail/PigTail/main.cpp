#include<iostream>
#include<stack>
#include<time.h>
#include<stdlib.h>
#include<algorithm>
#include<Windows.h>
using namespace std;

void Menu();	//���˵�����

class PaiDui	//�ƶ���
{
public:
	int poker[52] = { 0 };	//�ƶ����� 0:���ƣ�1~13������A~K��14~26������A~K��27~39��÷��A~K��40~52����ƬA~K
	int top = 0;			//�ƶ���ǰλ��
	int heitao = 13;		//����ɫ����
	int hongtao = 13;
	int meihua = 13;
	int fangpian = 13;
	void create();			//��������ƶ�
};
void PaiDui::create()	//��������ƶ�
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 52; i++)
	{
		poker[i] = i + 1;
	}
	for (int i = 0; i < 52; i++)
	{
		int j = rand() % (52 - i) + i;
		swap(poker[i], poker[j]);
	}
}

class FangZhiQU	//��������
{
public:
	stack<int> card;
	stack<int> decor;	//��ɫ  1: ����  2������  3��÷��  4����Ƭ
};

class WanJia	//�����
{
public:
	stack<int> heitao;		//����
	stack<int> hongtao;		//����
	stack<int> meihua;		//÷��
	stack<int> fangpian;	//��Ƭ
	int total()				//��������
	{
		return heitao.size() + hongtao.size() + meihua.size() + fangpian.size();
	}
};
int result[2] = { 0 };	//Ai���Գɼ�
int rule_1 = 0;			//Ai_1����
int rule_2 = 0;			//Ai_2����
int changci = 0;		//Ai���Գ���

int Decor(int num)	//����ת���廨ɫ  ����1: ����  2������  3��÷��  4����Ƭ
{
	if (1 <= num && num <= 13)
		return 1;
	else if (14 <= num && num <= 26)
		return 2;
	else if (27 <= num && num <= 39)
		return 3;
	else
		return 4;
}
string Change(int num)	//����ת��������
{
	string s1;
	string s2;
	int decor = Decor(num);
	if (decor == 1)
		s1 = "����";
	else if (decor == 2)
		s1 = "����";
	else if (decor == 3)
		s1 = "÷��";
	else
		s1 = "��Ƭ";

	int num_2 = num % 13;
	switch (num_2)
	{
	case 1:
		s2 = "A";
		break;
	case 2:
		s2 = "2";
		break;
	case 3:
		s2 = "3";
		break;
	case 4:
		s2 = "4";
		break;
	case 5:
		s2 = "5";
		break;
	case 6:
		s2 = "6";
		break;
	case 7:
		s2 = "7";
		break;
	case 8:
		s2 = "8";
		break;
	case 9:
		s2 = "9";
		break;
	case 10:
		s2 = "10";
		break;
	case 11:
		s2 = "J";
		break;
	case 12:
		s2 = "Q";
		break;
	case 0:
		s2 = "K";
		break;
	}
	string s = s1 + s2;
	return s;
}


void Update_1(WanJia& me, WanJia& you, FangZhiQU& fangzhiqu, PaiDui& paidui, int* score)	//�÷ָ��²���1: ���ƶ�ʣ��������,
{
	int amount[4] = { paidui.heitao, paidui.hongtao, paidui.meihua, paidui.fangpian };				//�ƶѸ���ɫ������
	int shoupai[4] = { me.heitao.size(), me.hongtao.size(), me.meihua.size(), me.fangpian.size() };	//���Ƹ���ɫ������

	for (int i = 0; i < 4; i++)
	{
		if (shoupai[i] != 0)	//+4~1��
		{
			for (int j = 0; j < 4; j++)
			{
				if (amount[j] <= amount[i])
					score[i + 1] += 1;
			}
		}
	}
}
void Update_2(WanJia& me, WanJia& you, FangZhiQU& fangzhiqu, PaiDui& paidui, int* score)	//�÷ָ��²���2: ����������������
{
	int amount[4] = { you.heitao.size(), you.hongtao.size(), you.meihua.size(), you.fangpian.size() };	//���ָ���ɫ������
	int shoupai[4] = { me.heitao.size(), me.hongtao.size(), me.meihua.size(), me.fangpian.size() };		//���Ƹ���ɫ������

	for (int i = 0; i < 4; i++)
	{
		if (shoupai[i] != 0)	//+8~5��
		{
			for (int j = 0; j < 4; j++)
			{
				if (amount[j] <= amount[i])
					score[i + 1] += 1;
			}
			score[i + 1] += 4;
		}
	}
}
void Update_3(WanJia& me, WanJia& you, FangZhiQU& fangzhiqu, PaiDui& paidui, int* score)	//�÷ָ��²���3: �����������ϵ
{
	if (!fangzhiqu.decor.empty())		//�ǿղ��ж�
	{
		if (fangzhiqu.decor.top() == 1)
		{
			score[1] = 0;
			if (paidui.heitao == 0)
				score[0] += 13;
		}
		else if (fangzhiqu.decor.top() == 2)
		{
			score[2] = 0;
			if (paidui.hongtao == 0)
				score[0] += 13;
		}
		else if (fangzhiqu.decor.top() == 3)
		{
			score[3] = 0;
			if (paidui.meihua == 0)
				score[0] += 13;
		}
		else if (fangzhiqu.decor.top() == 4)
		{
			score[4] = 0;
			if (paidui.fangpian == 0)
				score[0] += 13;
		}
	}
}

int Ai(WanJia& me, WanJia& you, FangZhiQU& fangzhiqu, PaiDui& paidui, int rule)		//Ai����ѡ��  rule��ʾʹ��ʲô����  0�����У� 1���ƶ������� 2���������������� 3������������ 
{
	int score[5] = { 0 };	//5�ֲ����ĵ÷� 0�����ƶ��г�ȡ  1: �������  2���������  3�����÷��  4�������Ƭ

	//�������
	if (rule == 0)
	{
		Update_1(me, you, fangzhiqu, paidui, score);
		Update_2(me, you, fangzhiqu, paidui, score);
		Update_3(me, you, fangzhiqu, paidui, score);
	}
	else if (rule == 1)
		Update_1(me, you, fangzhiqu, paidui, score);
	else if (rule == 2)
		Update_2(me, you, fangzhiqu, paidui, score);
	else if (rule == 3)
		Update_3(me, you, fangzhiqu, paidui, score);

	//ѡ�����
	int max = score[0];
	int operation = 0;
	for (int i = 0; i < 5; i++)
	{
		if (score[i] > max)
		{
			operation = i;
			max = score[i];
		}
	}

	return operation;
}
int Person(WanJia& _1P, WanJia& _2P, FangZhiQU& fangzhiqu, PaiDui& paidui, int i)	//���˲���ѡ��
{
	int operation = 0;

	//�����Ϣ��ʾ
	cout << endl << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << " 2 P ��������     ����: " << _2P.heitao.size() << " ��  ����: " << _2P.hongtao.size() << " ��  ÷��: " << _2P.meihua.size() << " ��  ��Ƭ: " << _2P.fangpian.size() << " ��" << endl << endl;
	cout << "�ƶ���           ����: " << paidui.heitao << " ��  ����: " << paidui.hongtao << " ��  ÷��: " << paidui.meihua << " ��  ��Ƭ: " << paidui.fangpian << " ��" << endl;
	cout << "��������          �� " << fangzhiqu.card.size() << " �� ��";
	if (!fangzhiqu.card.empty())
		cout << "     �����ƶ�������  " << Change(fangzhiqu.card.top()) << endl << endl;
	else
		cout << endl << endl;
	cout << " 1 P ��������     ����: " << _1P.heitao.size() << " ��  ����: " << _1P.hongtao.size() << " ��  ÷��: " << _1P.meihua.size() << " ��  ��Ƭ: " << _1P.fangpian.size() << " ��" << endl;
	cout << "-----------------------------------------------------------------------" << endl << endl;

	//����������ʾ��Ϣ
	cout << "����ѡ��" << endl;
	cout << "     0�����ƶ��г�ȡ     1: �������     2���������     3�����÷��     4�������Ƭ" << endl;
	cout << "     ������ " << i << " P �Ĳ��� >>> ";

	for (;;)	//��������
	{
		cin >> operation;
		while (operation != 0 && operation != 1 && operation != 2 && operation != 3 && operation != 4)
		{
			cout << "     ���������� 0 ~ 4 >>> ";
			cin >> operation;
		}
		if (operation == 0)
			break;
		else if (operation == 1)
		{
			if ((i == 1 && _1P.heitao.empty()) || (i == 2 && _2P.heitao.empty()))
				cout << "     ��û�к����ƣ����������� >>> ";
			else
				break;
		}
		else if (operation == 2)
		{
			if ((i == 1 && _1P.hongtao.empty()) || (i == 2 && _2P.hongtao.empty()))
				cout << "     ��û�к����ƣ����������� >>> ";
			else
				break;
		}
		else if (operation == 3)
		{
			if ((i == 1 && _1P.meihua.empty()) || (i == 2 && _2P.meihua.empty()))
				cout << "     ��û��÷���ƣ����������� >>> ";
			else
				break;
		}
		else
		{
			if ((i == 1 && _1P.fangpian.empty()) || (i == 2 && _2P.fangpian.empty()))
				cout << "     ��û�з�Ƭ�ƣ����������� >>> ";
			else
				break;
		}
	}

	return operation;
}

void Judge(int num, int decor_1, WanJia& P, FangZhiQU& fangzhiqu, int mod, int i)	//���������Ƿ��ջ��ж�
{
	int decor_2 = fangzhiqu.decor.top();	//ԭ����������ɫ
	int poker = 0;
	int decor = 0;

	//�ȷ���
	fangzhiqu.card.push(num);
	fangzhiqu.decor.push(decor_1);

	//�����ж�
	if (decor_1 == decor_2)		//��ԭ����������ɫ��ͬ
	{
		//��ʾ
		if (mod != 3)
		{
			cout << "     " << i << " P ����һ�� " << Change(fangzhiqu.card.top()) << " ��������������������" << endl;
			cout << "---------------------------------------------" << endl << endl;
		}

		//����
		while (!fangzhiqu.card.empty())
		{
			//������������
			poker = fangzhiqu.card.top();
			fangzhiqu.card.pop();
			decor = fangzhiqu.decor.top();
			fangzhiqu.decor.pop();

			//����ѹ����
			if (decor == 1)
				P.heitao.push(poker);
			else if (decor == 2)
				P.hongtao.push(poker);
			else if (decor == 3)
				P.meihua.push(poker);
			else
				P.fangpian.push(poker);
		}
	}
	else	//��ԭ����������ɫ��ͬ
	{
		if (mod != 3)
		{
			cout << "     " << i << " P ������һ�� " << Change(fangzhiqu.card.top()) << endl;
			cout << "---------------------------------------------" << endl << endl;
		}
	}
}

void Operation(WanJia& P, FangZhiQU& fangzhiqu, PaiDui& paidui,int operation, int mod, int i)	//����ִ��  operation����0�����ƶ��г�ȡ  1: �������  2���������  3�����÷��  4�������Ƭ
{
	int num = 0;	//��ֵ
	int decor = 0;	//��ɫ

	//ѡ����
	if (operation == 0)			//���ƶ��г�ȡ
	{
		if (mod != 3)
		{
			cout << endl << endl << "---------------------------------------------" << endl;
			cout << "     " << i << " P ѡ����� " << endl;
		}

		num = paidui.poker[paidui.top];
		paidui.top++;

		decor = Decor(num);
		if (decor == 1)
			paidui.heitao--;
		else if (decor == 2)
			paidui.hongtao--;
		else if (decor == 3)
			paidui.meihua--;
		else
			paidui.fangpian--;
	}
	else if (operation == 1)	//�������
	{
		if (mod != 3)
		{
			cout << endl << endl << "---------------------------------------------" << endl;
			cout << "     " << i << " P ѡ������ " << endl;
		}
		
		num = P.heitao.top();
		P.heitao.pop();
		decor = 1;
	}
	else if (operation == 2)	//�������
	{
		if (mod != 3)
		{
			cout << endl << endl << "---------------------------------------------" << endl;
			cout << "     " << i << " P ѡ������ " << endl;
		}
		
		num = P.hongtao.top();
		P.hongtao.pop();
		decor = 2;
	}
	else if (operation == 3)	//���÷��
	{
		if (mod != 3)
		{
			cout << endl << endl << "---------------------------------------------" << endl;
			cout << "     " << i << " P ѡ���÷�� " << endl;
		}
		
		num = P.meihua.top();
		P.meihua.pop();
		decor = 3;
	}
	else						//�����Ƭ
	{
		if (mod != 3)
		{
			cout << endl << endl << "---------------------------------------------" << endl;
			cout << "     " << i << " P ѡ���Ƭ " << endl;
		}
		
		num = P.fangpian.top();
		P.fangpian.pop();
		decor = 4;
	}
	
	//����
	if (fangzhiqu.card.empty())	//������Ϊ�գ�����
	{
		fangzhiqu.card.push(num);
		fangzhiqu.decor.push(decor);
		if (mod != 3)
		{
			cout << "     " << i << " P ������һ�� " << Change(fangzhiqu.card.top()) << endl;
			cout << "---------------------------------------------" << endl << endl;
		}
	}
	else						//��������Ϊ�գ��ж��Ƿ�����
		Judge(num, decor, P, fangzhiqu, mod, i);
}

void Game(int mod)	//��ս  mod=1:���� mod=2:�˻� mod=3:����
{
	WanJia _1P;
	WanJia _2P;
	FangZhiQU fangzhiqu;
	PaiDui paidui;
	paidui.create();

	for (int i = 1; i == 1 || i == 2; i++)	//���жԾ�   i��ʾ�����i����
	{
		int operation = 0;	//����ֵ  0�����ƶ��г�ȡ  1: �������  2���������  3�����÷��  4�������Ƭ

		//����ѡ��
		if (mod == 1)		//����
		{
			if (i == 1)
				operation = Person(_1P, _2P, fangzhiqu, paidui, i);
			else
				operation = Person(_1P, _2P, fangzhiqu, paidui, i);
		}
		else if (mod == 2)	//�˻�
		{
			if (i == 1)
				operation = Person(_1P, _2P, fangzhiqu, paidui, i);
			else
				operation = Ai(_2P, _1P, fangzhiqu, paidui, 0);
		}
		else	//��������
		{
			if (i == 1)
				operation = Ai(_1P, _2P, fangzhiqu, paidui, rule_1);
			else
				operation = Ai(_2P, _1P, fangzhiqu, paidui, rule_2);
		}
		
		//����ִ��
		if (i == 1)		//1P����
			Operation(_1P, fangzhiqu, paidui, operation, mod, i);
		else			//2P����
			Operation(_2P, fangzhiqu, paidui, operation, mod, i);
		
		//�����ж�
		if (paidui.top >= 52 && mod != 3)
		{
			//�����Ϣ��ʾ
			cout << endl << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "���2��������     ����: " << _2P.heitao.size() << " ��  ����: " << _2P.hongtao.size() << " ��  ÷��: " << _2P.meihua.size() << " ��  ��Ƭ: " << _2P.fangpian.size() << " ��" << endl << endl;
			cout << "�ƶ���          ����: " << paidui.heitao << " ��  ����: " << paidui.hongtao << " ��  ÷��: " << paidui.meihua << " ��  ��Ƭ: " << paidui.fangpian << " ��" << endl;
			cout << "��������         �� " << fangzhiqu.card.size() << " �� ��";
			if (!fangzhiqu.card.empty())
				cout << "     �ƶ�������  " << Change(fangzhiqu.card.top()) << endl << endl;
			else
				cout << endl << endl;
			cout << "���1��������     ����: " << _1P.heitao.size() << " ��  ����: " << _1P.hongtao.size() << " ��  ÷��: " << _1P.meihua.size() << " ��  ��Ƭ: " << _1P.fangpian.size() << " ��" << endl;
			cout << "-----------------------------------------------------------------------" << endl << endl;

			if (_1P.total() < _2P.total())
				cout << endl << endl << "       ���1��ʤ" << endl << endl;
			else
				cout << endl << endl << "       ���2��ʤ" << endl << endl;
			break;
		}
		if (mod == 3 && paidui.top >= 52)
		{
			changci--;
			if (_1P.total() < _2P.total())
				result[0]++;
			else
				result[1]++;
			break;
		}

		//���ת��
		if (i == 2)		
			i -= 2;
	}

	if (mod != 3)	//�ص��˵�
		Menu();
	else			//Ai����
	{
		if (changci > 0)
		{
			Sleep(1000);	//��Ҫ�ȴ�1��ʹ�ƶ����
			Game(3);
		}
		else
		{
			cout << endl << endl << "       �㷨��� " << rule_1 << " ��ʤ��" << result[0] << " ��" << endl;
			cout << endl << endl << "       �㷨��� " << rule_2 << " ��ʤ��" << result[1] << " ��" << endl;
			Menu();
		}
	}
}

void ZaiXian()	//���߶�ս
{
	cout << "δ����" << endl;
	Menu();
}

void Menu()	//���˵�
{
	//�˵���ʾ
	int mod = 0;
	cout << endl << "ģʽѡ��" << endl;
	cout << "     1: ���ض�ս     2���˻���ս     3�����߶�ս     4��Ai����     5���˳�" << endl;
	cout << "     ��������Ҫ���ģʽ >>> ";
	cin >> mod;

	//������ʾ
	while (mod != 1 && mod != 2 && mod != 3 && mod != 4 && mod != 5)
	{
		cout << "     ���������� 1 ~ 5 >>> ";
		cin >> mod;
	}
	
	//ģʽѡ�� 1: ���ض�ս     2���˻���ս     3�����߶�ս     4��Ai����     5���˳�
	if (mod == 1)
		Game(1);
	else if (mod == 2)
		Game(2);
	else if (mod == 3)
		ZaiXian();
	else if (mod == 4)
	{
		result[0] = result[1] = 0;	//��ʤ��������
		cout << "������Ai�������" << endl;
		cout << "     0�����У� 1���ƶ������� 2���������������� 3������������" << endl;
		cout << "     1 P ������� >>> ";
		while (cin >> rule_1)
		{
			if (!(0 <= rule_1 && rule_1 <= 3))
				cout << "     ���������� 0 ~ 3 >>> ";
			else
				break;
		}
		cout << "     0�����У� 1���ƶ������� 2���������������� 3������������" << endl;
		cout << "     2 P ������� >>> ";
		while (cin >> rule_2)
		{
			if (!(0 <= rule_2 && rule_2 <= 3))
				cout << "     ���������� 0 ~ 3 >>> ";
			else
				break;
		}
		cout << "     ������������� >>> ";
		while (cin >> changci)
		{
			if (!(0 < changci && changci <= 10))
				cout << "     ��������㷨��ԭ�򣬹���ĳ��λᵼ�µȴ�ʱ����ã����������� 1 ~ 10 >>> ";
			else
				break;
		}
		Game(3);
	}
	else
		exit(0);
}

int main()
{
	Menu();
	return 0;
}