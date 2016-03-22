#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<windows.h>
#include<time.h>
#include<iomanip>
#include <cstdlib>
#define Size 100
using namespace std;

//全局变量
int MulDivControl = 0;            //乘除法开关（0.乘除法 1.不包含乘除法）
int MaxNum = 100;                 //数字的最大值
int MinNum = 1;                   //数字的最小值

//真分数的数据结构
typedef struct Fraction
{
	int fenzi;      //表示真分数中的分子
	int fenmu;      //表示真分数中的分母
	float result;   //表示真分数的值（分子/分母）

}Fraction;

//重写函数
void gotoxy(int x, int y)    //x为列坐标,y为行坐标
{
	COORD pos = { x, y };    //设定坐标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);    //函数句柄
	SetConsoleCursorPosition(hOut, pos);
}

/* Colors defined for SetColor(int) */
enum {
	BLACK = 0,
	DARK_BLUE = 1,
	DARK_GREEN = 2,
	TEAL = 3,
	DARK_RED = 4,
	DARK_PURPLE = 5,
	GOLD = 6,
	GREY = 7,
	DARK_WHITE = 8,
	BLUE = 9,
	GREEN = 10,
	CYAN = 11,
	RED = 12,
	PURPLE = 13,
	YELLOW = 14,
	WHITE = 15
};
//设置文本色与背景色
void SetColor(const int foreground, const int background) {

	int Color = foreground + (background * 16);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, Color);

	return;
}

//随机生成范围内的一个整数
int CreateInt()
{
	if (MaxNum < MinNum)   //最大值最小值不合法
	{
		cout << "指定的数值范围不合法！！！";
		exit(0);
	}
	int num = (rand() % (MaxNum - MinNum + 1)) + MinNum; //生成一个>=MinNum,<=MaxNum的整数

	return num;
}

//随机生成范围内一个真分数
Fraction CreateFraction()
{
	Fraction fenshu;
	int l;

	fenshu.fenmu = CreateInt();  //分母随机生成
	fenshu.fenzi = CreateInt();  //分子随机生成

	//产生合法真分数
	while (true)
	{
		if (fenshu.fenmu < fenshu.fenzi)   //若分母小于分子，两者交换
		{
			l = fenshu.fenmu;
			fenshu.fenmu = fenshu.fenzi;
			fenshu.fenzi = l;
		}
		if (fenshu.fenmu != fenshu.fenzi && fenshu.fenmu !=0)            //若分母不等于分子且分母不为零，跳出循环
			break;

		//否则
		fenshu.fenmu = CreateInt();  //分母随机生成
		fenshu.fenzi = CreateInt();  //分子随机生成

	}

	fenshu.result = fenshu.fenzi / (float)fenshu.fenmu;  //计算真分数的结果
	for (int i = 2; i < fenshu.fenzi; i++)
	{
		int j = fenshu.fenzi%i;
		int k = fenshu.fenmu%i;
		if (j == 0 && k == 0)
		{
			fenshu.fenzi = fenshu.fenzi / i;
			fenshu.fenmu = fenshu.fenmu / i;
		}
	}

	return fenshu;   //返回合法真分数

}

//随机生成运算符0-3（+-*/）
int CreateOperator()
{
	int oper;
	if (MulDivControl == 0)    //允许有乘除法
	{
		oper = rand() % 4;
		return oper;
	}
	if (MulDivControl == 1)   //不允许有乘除法
	{
		oper = rand() % 2;
		return oper;
	}

	cout << "乘除法开关指定错误！！！";
	exit(0);
}

//生成算式
bool CreateEquation(int BracketControl, int AddSubControl_negative, int MulDivControl_remainder, string &equation_end, float &result_end)
{
	int num = 0;      //记录算式中数字个数
	int i, j, k;        //做随机种子
	float result;   //记录算式结果
	int oper_num = 0; //算式中操作数的个数（随机生成）
	Fraction opr1, opr2;  //记录生成的操作数
	string equation = "";     //记录中间算式
	equation_end = ""; //记录整个算式
	bool AddSub = false, MulDiv = false;  //记录算式中是否含有加减乘除
	int option = 2; //乘除设定
	stringstream ss;  //缓冲区
	bool oneNumSingal = false;  //记录是否为但操作数
	//bool fractionSingal = false;//记录是否为分数

	oper_num = rand() % 10 + 1;   //随机产生算式中操作数的个数(2-10)

	//算式中可以出现括号*******************************************************
	if (BracketControl == 0)
	{
		//生成一个基本算式****************************

		i = rand() % 2;   //生成随机数0/1，分别代表生成的基本算式第一个操作数为整数/真分数
		if (i == 0)  //第一个操作数是整数
		{
			opr1.result = CreateInt();
			ss << opr1.result;
			equation_end += ss.str();
			ss.str("");
		}
		else         //第一个操作数是真分数
		{
			opr1 = CreateFraction();
			ss << opr1.fenzi;
			equation_end += ss.str();
			ss.str("");
			equation_end += "/";
			ss << opr1.fenmu;
			equation_end += ss.str();
			ss.str("");
		}

		//同理生成第二个操作数
		i = rand() % 2;   //生成随机数0/1，分别代表生成的基本算式第二个操作数为整数/真分数
		if (i == 0)  //第二个操作数是整数
		{
			opr2.result = CreateInt();
			ss << opr2.result;
			equation += ss.str();
			ss.str("");
		}
		else         //第二个操作数是真分数
		{
			opr2 = CreateFraction();
			ss << opr2.fenzi;
			equation += ss.str();
			ss.str("");
			equation += "/";
			ss << opr2.fenmu;
			equation += ss.str();
			ss.str("");
			
		}
		num += 2;
		j = CreateOperator();
		//根据运算符计算基本算式的结果，设置equation_end，result_end
		if (j == 0)
		{
			equation_end += " ＋ ";
			result_end = opr1.result + opr2.result;
			AddSub = true;
		}
		else if (j == 1)
		{
			equation_end += " － ";
			result_end = opr1.result - opr2.result;
			AddSub = true;
		}
		else if (j == 2)
		{
			equation_end += " × ";
			result_end = opr1.result * opr2.result;
			MulDiv = true;
		}
		else if (j == 3)
		{
			if (opr2.result == 0) //除零操作
				return false;

			equation_end += " ÷ ";
			result_end = opr1.result / opr2.result;
			MulDiv = true;
		}
		else
		{
			cout << "error!";
			exit(0);
		}

		equation_end += equation;


		//基本算式生成完毕************************

		//由基本算式生成最终算式******************
		while (num < oper_num - 1)
		{
			equation = "";

			i = rand() % 2;
			if (i == 0)         //生成随机操作数
			{
				j = rand() % 2;

				if (j == 0)  //操作数是整数
				{
					opr1.result = CreateInt();
					result = opr1.result;
					ss << opr1.result;
					equation += ss.str();
					ss.str("");
					num++;
				}
				else         //操作数是真分数
				{
					opr1 = CreateFraction();
					result = opr1.result;
					ss << opr1.fenzi;
					equation += ss.str();
					ss.str("");
					equation += "/";
					ss << opr1.fenmu;
					equation += ss.str();
					ss.str("");
					num++;
				}
				oneNumSingal = true;
			}
			if (i == 1)        //生成随机算式
			{
				j = rand() % 2;   //生成随机数0/1，分别代表生成的基本算式第一个操作数为整数/真分数
				if (j == 0)  //第一个操作数是整数
				{
					opr1.result = CreateInt();
					ss << opr1.result;
					equation += ss.str();
					ss.str("");
				}
				else         //第一个操作数是真分数
				{
					opr1 = CreateFraction();
					ss << opr1.fenzi;
					equation += ss.str();
					ss.str("");
					equation += "/";
					ss << opr1.fenmu;
					equation += ss.str();
					ss.str("");
				}

				//同理生成第二个操作数
				j = rand() % 2;   //生成随机数0/1，分别代表生成的基本算式第二个操作数为整数/真分数
				if (j == 0)  //第二个操作数是整数
				{
					opr2.result = CreateInt();
					ss << opr2.result;
				}
				else         //第二个操作数是真分数
				{
					opr2 = CreateFraction();
					ss << opr2.fenzi;
					ss << "/";
					ss << opr2.fenmu;
				}
				num += 2;
				j = CreateOperator();
				//根据运算符计算基本算式的结果，设置equation，result
				if (j == 0)
				{
					equation += " ＋ ";
					result = opr1.result + opr2.result;
					AddSub = true;
				}
				else if (j == 1)
				{
					equation += " － ";
					result = opr1.result - opr2.result;
					AddSub = true;
				}
				else if (j == 2)
				{
					equation += " × ";
					result = opr1.result * opr2.result;
					MulDiv = true;
				}
				else if (j == 3)
				{
					if (opr2.result == 0) //除零操作
						return false;

					equation += " ÷ ";
					result = opr1.result / opr2.result;
					MulDiv = true;
				}
				else
				{
					cout << "error!";
					exit(0);
				}

				equation += ss.str();
				ss.str("");
			}
			//结合
			j = CreateOperator();
			if (j == 0)
			{
				equation_end = equation_end + " ＋ " + equation;
				result_end = result_end + result;
				AddSub = true;
			}
			else if (j == 1)
			{
				if (oneNumSingal)
					equation_end = equation_end + " － " + equation;
				else
					equation_end = equation_end + " － (" + equation + ")";
				result_end = result_end - result;
					AddSub = true;
			}
			else if (j == 2)
			{
				if (oneNumSingal)
					equation_end = "(" + equation_end + ") × " + equation + "";
				else
					equation_end = "(" + equation_end + ") × (" + equation + ")";

				result_end = result_end * result;
				MulDiv = true;
			}
			else
			{
				if (result == 0)
					return false;
				if (oneNumSingal)
					equation_end = "(" + equation_end + ") ÷ " + equation + "";
				else
					equation_end = "(" + equation_end + ") ÷ (" + equation + ")";

				result_end = result_end / result;
				MulDiv = true;
			}
			oneNumSingal = false;

		}
	}
	//算式中不可以出现括号*******************************************************
	if (BracketControl == 1)
	{
		int arry_1[9], m = 0, n = 0;    //记录运算符
		float arry_2[10];   //记录操作数

		i = rand() % 2;   //生成随机数0/1，分别代表生成的算式第一个操作数为整数/真分数
		if (i == 0)  //第一个操作数是整数
		{
			opr1.result = CreateInt();
			ss << opr1.result;
			equation_end += ss.str();
			ss.str("");
		}
		else         //第一个操作数是真分数
		{
			opr1 = CreateFraction();
			ss << opr1.fenzi;
			equation_end += ss.str();
			ss.str("");
			equation_end += "/";
			ss << opr1.fenmu;
			equation_end += ss.str();
			ss.str("");
		}
		arry_2[n] = opr1.result;
		n++;

		//同理生成第二个操作数
		i = rand() % 2;   //生成随机数0/1，分别代表生成的基本算式第二个操作数为整数/真分数
		if (i == 0)  //第二个操作数是整数
		{
			opr2.result = CreateInt();
			ss << opr2.result;
			equation += ss.str();
			ss.str("");
		}
		else         //第二个操作数是真分数
		{
			opr2 = CreateFraction();
			ss << opr2.fenzi;
			equation += ss.str();
			ss.str("");
			equation += "/";
			ss << opr2.fenmu;
			equation += ss.str();
			ss.str("");

		}
		arry_2[n] = opr2.result;
		n++;

		num += 2;
		j = CreateOperator();
		arry_1[m] = j;
		m++;
		//根据运算符计算基本算式的结果，设置equation_end，result_end
		if (j == 0)
		{
			equation_end += " ＋ ";
			AddSub = true;
		}
		else if (j == 1)
		{
			equation_end += " － ";
			AddSub = true;
		}
		else if (j == 2)
		{
			equation_end += " × ";
			result = arry_2[n - 2] * arry_2[n - 1];
			arry_2[n - 2] = result;
			n--;
			m--;
			MulDiv = true;
		}
		else if (j == 3)
		{
			if (opr2.result == 0) //除零操作
				return false;

			equation_end += " ÷ ";
			result = arry_2[n - 2] / arry_2[n - 1];
			arry_2[n - 2] = result;
			n--;
			m--;
			MulDiv = true;
		}
		else
		{
			cout << "error!";
			exit(0);
		}
		equation_end += equation;

		while (num < oper_num)
		{
			equation = "";
			i = rand() % 2;   //生成随机数0/1，分别代表为整数/真分数
			if (i == 0)  //第一个操作数是整数
			{
				opr1.result = CreateInt();
				ss << opr1.result;
				equation += ss.str();
				ss.str("");
			}
			else         //第一个操作数是真分数
			{
				opr1 = CreateFraction();
				ss << opr1.fenzi;
				equation += ss.str();
				ss.str("");
				equation += "/";
				ss << opr1.fenmu;
				equation += ss.str();
				ss.str("");
			}
			arry_2[n] = opr1.result;
			n++;
			num++;

			j = CreateOperator();
			arry_1[m] = j;
			m++;
			if (j == 0)
			{
				equation_end = equation_end + " ＋ " + equation;
				AddSub = true;
			}
			else if (j == 1)
			{
				equation_end = equation_end + " － " + equation;
				AddSub = true;
			}
			else if (j == 2)
			{
				equation_end = equation_end + " × " + equation;
				result = arry_2[n - 2] * arry_2[n - 1];
				arry_2[n - 2] = result;
				n--;
				m--;
				MulDiv = true;
			}
			else
			{
				equation_end = equation_end + " ÷ " + equation;
				result = arry_2[n - 2] / arry_2[n - 1];
				arry_2[n - 2] = result;
				n--;
				m--;
				MulDiv = true;
			}

		}
		//计算算式结果
		result_end = arry_2[0];
		for (i = 0; i <= m; i++)
		{
			if (arry_1[i] == 0)
				result_end = result_end + arry_2[i + 1];
			if (arry_1[i] == 1)
				result_end = result_end - arry_2[i + 1];
		}


	}
	//加减有无负数
	if (AddSub == true && AddSubControl_negative == 1)
	{
		if (result_end < 0)
			return false;
	}
	//乘除有无余数
	if (MulDiv == true && MulDivControl_remainder == 1)
	{
		if ((int)(result_end * 10000) % 10000 != 0)
			return false;
	}
	return true;
}

int menu(int i)
{
	int l;
	system("cls");
	cout << setw(47) << "简单算式生成" << endl << endl;
	cout << setw(22) << "请对算式进行设置：" << endl << endl;
	cout << "            <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << "            <<                    1.算式个数                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    2.输出方式                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    3.括号开关                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    4.负数开关                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    5.余数开关                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    6.乘除开关                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    7.最大数值                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    8.最小数值                           <<" << endl;
	cout << "            <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

	SetColor(BLUE,BLACK);
	switch (i)
	{
	case 0:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".算式个数";
			  break;
	}
	case 1:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".输出方式 ";
			  break;
	}
	case 2:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".括号开关 ";
			  break;
	}
	case 3:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".负数开关 ";
			  break;
	}
	case 4:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".余数开关 ";
			  break;
	}
	case 5:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".乘除开关 ";
			  break;
	}
	case 6:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".最大数值 ";
			  break;
	}
	case 7:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".最小数值 ";
			  break;
	}
	}
	SetColor(YELLOW,BLACK);
	gotoxy(25, 22);
	cout << "请输入设定：";
	cin >> l;
	SetColor(WHITE, BLACK);
	return l;
}

int main()
{
	//初始化变量
	int ProblemNumber = 30;           //表示要生成的题目的个数
	int OutWay = 0;                   //输出方式（0.屏幕打印 1.输出到文件）
	int BracketControl = 1;           //括号开关（0.含括号 1.不含括号）
	int AddSubControl_negative = 1;   //加减有无负数（0.可以有 1.不可以有）
	int MulDivControl_remainder = 1;  //乘除有无余数（0.可以有 1.不可以有）
	string equation[Size];            //存储算式
	float result[Size];
	srand(time(0));                 //随机函数做时间种子
	int arry[8];
	int i = 0,m;
	float answer;
	int answer_correct = 0;       //答题正确数
	//stringstream ss;

	for (i = 0; i < 8; i++)
	{
		arry[i] = menu(i);
		if (i == 7)
		{
			if (arry[i] >= arry[i - 1])
			{
				i--;
				system("cls");
				cout << "输入错误！！！"<<endl;
				cout << "提示： 输入的最小值不合法！！";
				system("pause");
			}
		}
		else if (i == 0)
		 {
			if (arry[i] <= 0)
			{
				i--;
				system("cls");
				cout << "输入错误！！！"<<endl;
				cout << "提示： 输入的个数要不小于1.";
				system("pause");
			}
		}
		else if (i != 6)
		{
			if (arry[i] != 0 && arry[i] != 1)
			{
				system("cls");
				i--;
				cout << "输入错误！！！"<<endl;
				cout << "提示： 输入的数值 0 代表默认存在，1 代表不存在。比括号控制中 0 代表有括号， 1 代表没有括号;输出方式中 0 代表屏幕打印 ，1 代表输出到文件。 ";
				system("pause");
			
			}
		}

	}
	BracketControl = arry[2];
	AddSubControl_negative = arry[3];
	MulDivControl_remainder = arry[4];
	MulDivControl = arry[5];
	MaxNum = arry[6];
	MinNum = arry[7];
	ProblemNumber = arry[0];
	OutWay = arry[1];
	system("cls");
	for (i = 0; i < ProblemNumber; i++)
	{
		m = 0;
		if (CreateEquation(BracketControl, AddSubControl_negative, MulDivControl_remainder, equation[i], result[i]))//算式合法
		{
			for (int j = 0; j < i; j++)
			{
				if (equation[i] == equation[j]) //算式重复
					m = 1;
			}

			if (m == 1) //重复
			{
				i--;
			}
			else
			{
				cout <<endl<< "第" << i + 1 << "题： " << equation[i] << " = ";
				cin >> answer;
				if ((int)(answer * 100) == (int)(result[i] * 100)) //结果正确
				{
					answer_correct++;
					SetColor(GREEN, BLACK);
					cout << "  正确！！" << endl;
					SetColor(WHITE, BLACK);
				}
				else
				{
					SetColor(RED, BLACK);
					cout << "  错误！！正确答案为：" << result[i] << endl;
					SetColor(WHITE, BLACK);
				}
			}
		}
		else  //算式不合法
			i--;
	}
	SetColor(GREEN, BLACK);
	cout <<endl<< "回答正确的题目数为：";
	SetColor(YELLOW, BLACK);
	cout<<answer_correct;
	SetColor(WHITE, BLACK);
	system("pause");
	if (OutWay == 1)
	{
		system("cls");
		ofstream file("题目");
		if (!file)
		{
			cout << "无法输出到文件！！！";
			exit(0);
		}
		for (int i = 0; i < ProblemNumber; i++)
		{
			file << "第" << i + 1 << "题  ";
			for (int j = 0; j < equation[i].length(); j++)
				file << equation[i][j];
			file << "=" << endl;
		}
		cout << "题目已写入该项目文件夹中！！（文件名：题目）" << endl;

		ofstream answer("参考答案");
		if (!answer)
		{
			cout << "无法输出到文件！！！";
			exit(0);
		}
		for (int i = 0; i < ProblemNumber; i++)
		{
			answer << "第" << i + 1 << "题  ";
			for (int j = 0; j < equation[i].length(); j++)
				answer << equation[i][j];
			answer << "=" << result[i] << endl;
		}
		cout << "答案已写入该项目文件夹中！（文件名：参考答案）" << endl;
	}
	return 0;
}

