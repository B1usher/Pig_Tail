#include<iostream>
#include<stack>
#include<time.h>
#include<stdlib.h>
#include<algorithm>
#include<Windows.h>
using namespace std;

void Menu();	//主菜单声明

class PaiDui	//牌堆类
{
public:
	int poker[52] = { 0 };	//牌堆牌序 0:无牌；1~13：黑桃A~K；14~26：红桃A~K；27~39：梅花A~K；40~52：方片A~K
	int top = 0;			//牌顶当前位置
	int heitao = 13;		//各花色数量
	int hongtao = 13;
	int meihua = 13;
	int fangpian = 13;
	void create();			//创建随机牌堆
};
void PaiDui::create()	//创建随机牌堆
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

class FangZhiQU	//放置区类
{
public:
	stack<int> card;
	stack<int> decor;	//花色  1: 黑桃  2：红桃  3：梅花  4：方片
};

class WanJia	//玩家类
{
public:
	stack<int> heitao;		//黑桃
	stack<int> hongtao;		//红桃
	stack<int> meihua;		//梅花
	stack<int> fangpian;	//方片
	int total()				//手牌总数
	{
		return heitao.size() + hongtao.size() + meihua.size() + fangpian.size();
	}
};
int result[2] = { 0 };	//Ai测试成绩
int rule_1 = 0;			//Ai_1策略
int rule_2 = 0;			//Ai_2策略
int changci = 0;		//Ai测试场数

int Decor(int num)	//数字转具体花色  返回1: 黑桃  2：红桃  3：梅花  4：方片
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
string Change(int num)	//数字转具体牌型
{
	string s1;
	string s2;
	int decor = Decor(num);
	if (decor == 1)
		s1 = "黑桃";
	else if (decor == 2)
		s1 = "红桃";
	else if (decor == 3)
		s1 = "梅花";
	else
		s1 = "方片";

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


void Update_1(WanJia& me, WanJia& you, FangZhiQU& fangzhiqu, PaiDui& paidui, int* score)	//得分更新策略1: 按牌堆剩余牌数量,
{
	int amount[4] = { paidui.heitao, paidui.hongtao, paidui.meihua, paidui.fangpian };				//牌堆各花色牌数量
	int shoupai[4] = { me.heitao.size(), me.hongtao.size(), me.meihua.size(), me.fangpian.size() };	//手牌各花色牌数量

	for (int i = 0; i < 4; i++)
	{
		if (shoupai[i] != 0)	//+4~1分
		{
			for (int j = 0; j < 4; j++)
			{
				if (amount[j] <= amount[i])
					score[i + 1] += 1;
			}
		}
	}
}
void Update_2(WanJia& me, WanJia& you, FangZhiQU& fangzhiqu, PaiDui& paidui, int* score)	//得分更新策略2: 按对手手牌数量排
{
	int amount[4] = { you.heitao.size(), you.hongtao.size(), you.meihua.size(), you.fangpian.size() };	//对手各花色牌数量
	int shoupai[4] = { me.heitao.size(), me.hongtao.size(), me.meihua.size(), me.fangpian.size() };		//手牌各花色牌数量

	for (int i = 0; i < 4; i++)
	{
		if (shoupai[i] != 0)	//+8~5分
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
void Update_3(WanJia& me, WanJia& you, FangZhiQU& fangzhiqu, PaiDui& paidui, int* score)	//得分更新策略3: 按与放置区关系
{
	if (!fangzhiqu.decor.empty())		//非空才判断
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

int Ai(WanJia& me, WanJia& you, FangZhiQU& fangzhiqu, PaiDui& paidui, int rule)		//Ai操作选择  rule表示使用什么策略  0：所有； 1：牌堆数量； 2：对手手牌数量； 3：放置区顶牌 
{
	int score[5] = { 0 };	//5种操作的得分 0：从牌堆中抽取  1: 打出黑桃  2：打出红桃  3：打出梅花  4：打出方片

	//计算分数
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

	//选择操作
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
int Person(WanJia& _1P, WanJia& _2P, FangZhiQU& fangzhiqu, PaiDui& paidui, int i)	//真人操作选择
{
	int operation = 0;

	//相关信息提示
	cout << endl << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << " 2 P 的手牌有     黑桃: " << _2P.heitao.size() << " 张  红桃: " << _2P.hongtao.size() << " 张  梅花: " << _2P.meihua.size() << " 张  方片: " << _2P.fangpian.size() << " 张" << endl << endl;
	cout << "牌堆有           黑桃: " << paidui.heitao << " 张  红桃: " << paidui.hongtao << " 张  梅花: " << paidui.meihua << " 张  方片: " << paidui.fangpian << " 张" << endl;
	cout << "放置区有          共 " << fangzhiqu.card.size() << " 张 牌";
	if (!fangzhiqu.card.empty())
		cout << "     其中牌顶的牌是  " << Change(fangzhiqu.card.top()) << endl << endl;
	else
		cout << endl << endl;
	cout << " 1 P 的手牌有     黑桃: " << _1P.heitao.size() << " 张  红桃: " << _1P.hongtao.size() << " 张  梅花: " << _1P.meihua.size() << " 张  方片: " << _1P.fangpian.size() << " 张" << endl;
	cout << "-----------------------------------------------------------------------" << endl << endl;

	//操作输入提示信息
	cout << "操作选择：" << endl;
	cout << "     0：从牌堆中抽取     1: 打出黑桃     2：打出红桃     3：打出梅花     4：打出方片" << endl;
	cout << "     请输入 " << i << " P 的操作 >>> ";

	for (;;)	//操作输入
	{
		cin >> operation;
		while (operation != 0 && operation != 1 && operation != 2 && operation != 3 && operation != 4)
		{
			cout << "     请输入数字 0 ~ 4 >>> ";
			cin >> operation;
		}
		if (operation == 0)
			break;
		else if (operation == 1)
		{
			if ((i == 1 && _1P.heitao.empty()) || (i == 2 && _2P.heitao.empty()))
				cout << "     你没有黑桃牌，请重新输入 >>> ";
			else
				break;
		}
		else if (operation == 2)
		{
			if ((i == 1 && _1P.hongtao.empty()) || (i == 2 && _2P.hongtao.empty()))
				cout << "     你没有红桃牌，请重新输入 >>> ";
			else
				break;
		}
		else if (operation == 3)
		{
			if ((i == 1 && _1P.meihua.empty()) || (i == 2 && _2P.meihua.empty()))
				cout << "     你没有梅花牌，请重新输入 >>> ";
			else
				break;
		}
		else
		{
			if ((i == 1 && _1P.fangpian.empty()) || (i == 2 && _2P.fangpian.empty()))
				cout << "     你没有方片牌，请重新输入 >>> ";
			else
				break;
		}
	}

	return operation;
}

void Judge(int num, int decor_1, WanJia& P, FangZhiQU& fangzhiqu, int mod, int i)	//放置区牌是否收回判断
{
	int decor_2 = fangzhiqu.decor.top();	//原放置区顶花色
	int poker = 0;
	int decor = 0;

	//先放牌
	fangzhiqu.card.push(num);
	fangzhiqu.decor.push(decor_1);

	//收牌判断
	if (decor_1 == decor_2)		//与原放置区顶花色相同
	{
		//提示
		if (mod != 3)
		{
			cout << "     " << i << " P 由于一张 " << Change(fangzhiqu.card.top()) << " 收起了整个放置区的牌" << endl;
			cout << "---------------------------------------------" << endl << endl;
		}

		//收牌
		while (!fangzhiqu.card.empty())
		{
			//放置区弹出牌
			poker = fangzhiqu.card.top();
			fangzhiqu.card.pop();
			decor = fangzhiqu.decor.top();
			fangzhiqu.decor.pop();

			//手牌压入牌
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
	else	//与原放置区顶花色不同
	{
		if (mod != 3)
		{
			cout << "     " << i << " P 放置了一张 " << Change(fangzhiqu.card.top()) << endl;
			cout << "---------------------------------------------" << endl << endl;
		}
	}
}

void Operation(WanJia& P, FangZhiQU& fangzhiqu, PaiDui& paidui, int operation, int mod, int i)	//操作执行  operation等于0：从牌堆中抽取  1: 打出黑桃  2：打出红桃  3：打出梅花  4：打出方片
{
	int num = 0;	//牌值
	int decor = 0;	//花色

	//选择牌
	if (operation == 0)			//从牌堆中抽取
	{
		if (mod != 3)
		{
			cout << endl << endl << "---------------------------------------------" << endl;
			cout << "     " << i << " P 选择抽牌 " << endl;
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
	else if (operation == 1)	//打出黑桃
	{
		if (mod != 3)
		{
			cout << endl << endl << "---------------------------------------------" << endl;
			cout << "     " << i << " P 选择打黑桃 " << endl;
		}

		num = P.heitao.top();
		P.heitao.pop();
		decor = 1;
	}
	else if (operation == 2)	//打出红桃
	{
		if (mod != 3)
		{
			cout << endl << endl << "---------------------------------------------" << endl;
			cout << "     " << i << " P 选择打红桃 " << endl;
		}

		num = P.hongtao.top();
		P.hongtao.pop();
		decor = 2;
	}
	else if (operation == 3)	//打出梅花
	{
		if (mod != 3)
		{
			cout << endl << endl << "---------------------------------------------" << endl;
			cout << "     " << i << " P 选择打梅花 " << endl;
		}

		num = P.meihua.top();
		P.meihua.pop();
		decor = 3;
	}
	else						//打出方片
	{
		if (mod != 3)
		{
			cout << endl << endl << "---------------------------------------------" << endl;
			cout << "     " << i << " P 选择打方片 " << endl;
		}

		num = P.fangpian.top();
		P.fangpian.pop();
		decor = 4;
	}

	//放牌
	if (fangzhiqu.card.empty())	//放置区为空，放牌
	{
		fangzhiqu.card.push(num);
		fangzhiqu.decor.push(decor);
		if (mod != 3)
		{
			cout << "     " << i << " P 放置了一张 " << Change(fangzhiqu.card.top()) << endl;
			cout << "---------------------------------------------" << endl << endl;
		}
	}
	else						//放置区不为空，判断是否收牌
		Judge(num, decor, P, fangzhiqu, mod, i);
}

void Game(int mod)	//对战  mod=1:人人 mod=2:人机 mod=3:机机
{
	WanJia _1P;
	WanJia _2P;
	FangZhiQU fangzhiqu;
	PaiDui paidui;
	paidui.create();

	for (int i = 1; i == 1 || i == 2; i++)	//进行对局   i表示：玩家i操作
	{
		int operation = 0;	//操作值  0：从牌堆中抽取  1: 打出黑桃  2：打出红桃  3：打出梅花  4：打出方片

		//操作选择
		if (mod == 1)		//人人
		{
			if (i == 1)
				operation = Person(_1P, _2P, fangzhiqu, paidui, i);
			else
				operation = Person(_1P, _2P, fangzhiqu, paidui, i);
		}
		else if (mod == 2)	//人机
		{
			if (i == 1)
				operation = Person(_1P, _2P, fangzhiqu, paidui, i);
			else
				operation = Ai(_2P, _1P, fangzhiqu, paidui, 0);
		}
		else	//机机测试
		{
			if (i == 1)
				operation = Ai(_1P, _2P, fangzhiqu, paidui, rule_1);
			else
				operation = Ai(_2P, _1P, fangzhiqu, paidui, rule_2);
		}

		//操作执行
		if (i == 1)		//1P操作
			Operation(_1P, fangzhiqu, paidui, operation, mod, i);
		else			//2P操作
			Operation(_2P, fangzhiqu, paidui, operation, mod, i);

		//结束判断
		if (paidui.top >= 52 && mod != 3)
		{
			//相关信息提示
			cout << endl << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "玩家2的手牌有     黑桃: " << _2P.heitao.size() << " 张  红桃: " << _2P.hongtao.size() << " 张  梅花: " << _2P.meihua.size() << " 张  方片: " << _2P.fangpian.size() << " 张" << endl << endl;
			cout << "牌堆有          黑桃: " << paidui.heitao << " 张  红桃: " << paidui.hongtao << " 张  梅花: " << paidui.meihua << " 张  方片: " << paidui.fangpian << " 张" << endl;
			cout << "放置区有         共 " << fangzhiqu.card.size() << " 张 牌";
			if (!fangzhiqu.card.empty())
				cout << "     牌顶的牌是  " << Change(fangzhiqu.card.top()) << endl << endl;
			else
				cout << endl << endl;
			cout << "玩家1的手牌有     黑桃: " << _1P.heitao.size() << " 张  红桃: " << _1P.hongtao.size() << " 张  梅花: " << _1P.meihua.size() << " 张  方片: " << _1P.fangpian.size() << " 张" << endl;
			cout << "-----------------------------------------------------------------------" << endl << endl;

			if (_1P.total() < _2P.total())
				cout << endl << endl << "       玩家1获胜" << endl << endl;
			else
				cout << endl << endl << "       玩家2获胜" << endl << endl;
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

		//玩家转换
		if (i == 2)
			i -= 2;
	}

	if (mod != 3)	//回到菜单
		Menu();
	else			//Ai测试
	{
		if (changci > 0)
		{
			Sleep(1000);	//需要等待1秒使牌堆随机
			Game(3);
		}
		else
		{
			cout << endl << endl << "       算法序号 " << rule_1 << " 获胜：" << result[0] << " 场" << endl;
			cout << endl << endl << "       算法序号 " << rule_2 << " 获胜：" << result[1] << " 场" << endl;
			Menu();
		}
	}
}

void ZaiXian()	//在线对战
{
	cout << "未开发" << endl;
	Menu();
}

void Menu()	//主菜单
{
	//菜单提示
	int mod = 0;
	cout << endl << "模式选择：" << endl;
	cout << "     1: 本地对战     2：人机对战     3：在线对战     4：Ai比赛     5：退出" << endl;
	cout << "     请输入想要玩的模式 >>> ";
	cin >> mod;

	//输入提示
	while (mod != 1 && mod != 2 && mod != 3 && mod != 4 && mod != 5)
	{
		cout << "     请输入数字 1 ~ 5 >>> ";
		cin >> mod;
	}

	//模式选择 1: 本地对战     2：人机对战     3：在线对战     4：Ai比赛     5：退出
	if (mod == 1)
		Game(1);
	else if (mod == 2)
		Game(2);
	else if (mod == 3)
		ZaiXian();
	else if (mod == 4)
	{
		result[0] = result[1] = 0;	//获胜场次置零
		cout << "请输入Ai策略序号" << endl;
		cout << "     0：所有； 1：牌堆数量； 2：对手手牌数量； 3：放置区顶牌" << endl;
		cout << "     1 P 策略序号 >>> ";
		while (cin >> rule_1)
		{
			if (!(0 <= rule_1 && rule_1 <= 3))
				cout << "     请输入数字 0 ~ 3 >>> ";
			else
				break;
		}
		cout << "     0：所有； 1：牌堆数量； 2：对手手牌数量； 3：放置区顶牌" << endl;
		cout << "     2 P 策略序号 >>> ";
		while (cin >> rule_2)
		{
			if (!(0 <= rule_2 && rule_2 <= 3))
				cout << "     请输入数字 0 ~ 3 >>> ";
			else
				break;
		}
		cout << "     请输入比赛场次 >>> ";
		while (cin >> changci)
		{
			if (!(0 < changci && changci <= 10))
				cout << "     由于随机算法的原因，过大的场次会导致等待时间过久，请输入数字 1 ~ 10 >>> ";
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
	system("pause");
	return 0;
}
