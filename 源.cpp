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

//ȫ�ֱ���
int MulDivControl = 0;            //�˳������أ�0.�˳��� 1.�������˳�����
int MaxNum = 100;                 //���ֵ����ֵ
int MinNum = 1;                   //���ֵ���Сֵ

//����������ݽṹ
typedef struct Fraction
{
	int fenzi;      //��ʾ������еķ���
	int fenmu;      //��ʾ������еķ�ĸ
	float result;   //��ʾ�������ֵ������/��ĸ��

}Fraction;

//��д����
void gotoxy(int x, int y)    //xΪ������,yΪ������
{
	COORD pos = { x, y };    //�趨����
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);    //�������
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
//�����ı�ɫ�뱳��ɫ
void SetColor(const int foreground, const int background) {

	int Color = foreground + (background * 16);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, Color);

	return;
}

//������ɷ�Χ�ڵ�һ������
int CreateInt()
{
	if (MaxNum < MinNum)   //���ֵ��Сֵ���Ϸ�
	{
		cout << "ָ������ֵ��Χ���Ϸ�������";
		exit(0);
	}
	int num = (rand() % (MaxNum - MinNum + 1)) + MinNum; //����һ��>=MinNum,<=MaxNum������

	return num;
}

//������ɷ�Χ��һ�������
Fraction CreateFraction()
{
	Fraction fenshu;
	int l;

	fenshu.fenmu = CreateInt();  //��ĸ�������
	fenshu.fenzi = CreateInt();  //�����������

	//�����Ϸ������
	while (true)
	{
		if (fenshu.fenmu < fenshu.fenzi)   //����ĸС�ڷ��ӣ����߽���
		{
			l = fenshu.fenmu;
			fenshu.fenmu = fenshu.fenzi;
			fenshu.fenzi = l;
		}
		if (fenshu.fenmu != fenshu.fenzi && fenshu.fenmu !=0)            //����ĸ�����ڷ����ҷ�ĸ��Ϊ�㣬����ѭ��
			break;

		//����
		fenshu.fenmu = CreateInt();  //��ĸ�������
		fenshu.fenzi = CreateInt();  //�����������

	}

	fenshu.result = fenshu.fenzi / (float)fenshu.fenmu;  //����������Ľ��
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

	return fenshu;   //���غϷ������

}

//������������0-3��+-*/��
int CreateOperator()
{
	int oper;
	if (MulDivControl == 0)    //�����г˳���
	{
		oper = rand() % 4;
		return oper;
	}
	if (MulDivControl == 1)   //�������г˳���
	{
		oper = rand() % 2;
		return oper;
	}

	cout << "�˳�������ָ�����󣡣���";
	exit(0);
}

//������ʽ
bool CreateEquation(int BracketControl, int AddSubControl_negative, int MulDivControl_remainder, string &equation_end, float &result_end)
{
	int num = 0;      //��¼��ʽ�����ָ���
	int i, j, k;        //���������
	float result;   //��¼��ʽ���
	int oper_num = 0; //��ʽ�в������ĸ�����������ɣ�
	Fraction opr1, opr2;  //��¼���ɵĲ�����
	string equation = "";     //��¼�м���ʽ
	equation_end = ""; //��¼������ʽ
	bool AddSub = false, MulDiv = false;  //��¼��ʽ���Ƿ��мӼ��˳�
	int option = 2; //�˳��趨
	stringstream ss;  //������
	bool oneNumSingal = false;  //��¼�Ƿ�Ϊ��������
	//bool fractionSingal = false;//��¼�Ƿ�Ϊ����

	oper_num = rand() % 10 + 1;   //���������ʽ�в������ĸ���(2-10)

	//��ʽ�п��Գ�������*******************************************************
	if (BracketControl == 0)
	{
		//����һ��������ʽ****************************

		i = rand() % 2;   //���������0/1���ֱ�������ɵĻ�����ʽ��һ��������Ϊ����/�����
		if (i == 0)  //��һ��������������
		{
			opr1.result = CreateInt();
			ss << opr1.result;
			equation_end += ss.str();
			ss.str("");
		}
		else         //��һ���������������
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

		//ͬ�����ɵڶ���������
		i = rand() % 2;   //���������0/1���ֱ�������ɵĻ�����ʽ�ڶ���������Ϊ����/�����
		if (i == 0)  //�ڶ���������������
		{
			opr2.result = CreateInt();
			ss << opr2.result;
			equation += ss.str();
			ss.str("");
		}
		else         //�ڶ����������������
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
		//������������������ʽ�Ľ��������equation_end��result_end
		if (j == 0)
		{
			equation_end += " �� ";
			result_end = opr1.result + opr2.result;
			AddSub = true;
		}
		else if (j == 1)
		{
			equation_end += " �� ";
			result_end = opr1.result - opr2.result;
			AddSub = true;
		}
		else if (j == 2)
		{
			equation_end += " �� ";
			result_end = opr1.result * opr2.result;
			MulDiv = true;
		}
		else if (j == 3)
		{
			if (opr2.result == 0) //�������
				return false;

			equation_end += " �� ";
			result_end = opr1.result / opr2.result;
			MulDiv = true;
		}
		else
		{
			cout << "error!";
			exit(0);
		}

		equation_end += equation;


		//������ʽ�������************************

		//�ɻ�����ʽ����������ʽ******************
		while (num < oper_num - 1)
		{
			equation = "";

			i = rand() % 2;
			if (i == 0)         //�������������
			{
				j = rand() % 2;

				if (j == 0)  //������������
				{
					opr1.result = CreateInt();
					result = opr1.result;
					ss << opr1.result;
					equation += ss.str();
					ss.str("");
					num++;
				}
				else         //�������������
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
			if (i == 1)        //���������ʽ
			{
				j = rand() % 2;   //���������0/1���ֱ�������ɵĻ�����ʽ��һ��������Ϊ����/�����
				if (j == 0)  //��һ��������������
				{
					opr1.result = CreateInt();
					ss << opr1.result;
					equation += ss.str();
					ss.str("");
				}
				else         //��һ���������������
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

				//ͬ�����ɵڶ���������
				j = rand() % 2;   //���������0/1���ֱ�������ɵĻ�����ʽ�ڶ���������Ϊ����/�����
				if (j == 0)  //�ڶ���������������
				{
					opr2.result = CreateInt();
					ss << opr2.result;
				}
				else         //�ڶ����������������
				{
					opr2 = CreateFraction();
					ss << opr2.fenzi;
					ss << "/";
					ss << opr2.fenmu;
				}
				num += 2;
				j = CreateOperator();
				//������������������ʽ�Ľ��������equation��result
				if (j == 0)
				{
					equation += " �� ";
					result = opr1.result + opr2.result;
					AddSub = true;
				}
				else if (j == 1)
				{
					equation += " �� ";
					result = opr1.result - opr2.result;
					AddSub = true;
				}
				else if (j == 2)
				{
					equation += " �� ";
					result = opr1.result * opr2.result;
					MulDiv = true;
				}
				else if (j == 3)
				{
					if (opr2.result == 0) //�������
						return false;

					equation += " �� ";
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
			//���
			j = CreateOperator();
			if (j == 0)
			{
				equation_end = equation_end + " �� " + equation;
				result_end = result_end + result;
				AddSub = true;
			}
			else if (j == 1)
			{
				if (oneNumSingal)
					equation_end = equation_end + " �� " + equation;
				else
					equation_end = equation_end + " �� (" + equation + ")";
				result_end = result_end - result;
					AddSub = true;
			}
			else if (j == 2)
			{
				if (oneNumSingal)
					equation_end = "(" + equation_end + ") �� " + equation + "";
				else
					equation_end = "(" + equation_end + ") �� (" + equation + ")";

				result_end = result_end * result;
				MulDiv = true;
			}
			else
			{
				if (result == 0)
					return false;
				if (oneNumSingal)
					equation_end = "(" + equation_end + ") �� " + equation + "";
				else
					equation_end = "(" + equation_end + ") �� (" + equation + ")";

				result_end = result_end / result;
				MulDiv = true;
			}
			oneNumSingal = false;

		}
	}
	//��ʽ�в����Գ�������*******************************************************
	if (BracketControl == 1)
	{
		int arry_1[9], m = 0, n = 0;    //��¼�����
		float arry_2[10];   //��¼������

		i = rand() % 2;   //���������0/1���ֱ�������ɵ���ʽ��һ��������Ϊ����/�����
		if (i == 0)  //��һ��������������
		{
			opr1.result = CreateInt();
			ss << opr1.result;
			equation_end += ss.str();
			ss.str("");
		}
		else         //��һ���������������
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

		//ͬ�����ɵڶ���������
		i = rand() % 2;   //���������0/1���ֱ�������ɵĻ�����ʽ�ڶ���������Ϊ����/�����
		if (i == 0)  //�ڶ���������������
		{
			opr2.result = CreateInt();
			ss << opr2.result;
			equation += ss.str();
			ss.str("");
		}
		else         //�ڶ����������������
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
		//������������������ʽ�Ľ��������equation_end��result_end
		if (j == 0)
		{
			equation_end += " �� ";
			AddSub = true;
		}
		else if (j == 1)
		{
			equation_end += " �� ";
			AddSub = true;
		}
		else if (j == 2)
		{
			equation_end += " �� ";
			result = arry_2[n - 2] * arry_2[n - 1];
			arry_2[n - 2] = result;
			n--;
			m--;
			MulDiv = true;
		}
		else if (j == 3)
		{
			if (opr2.result == 0) //�������
				return false;

			equation_end += " �� ";
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
			i = rand() % 2;   //���������0/1���ֱ����Ϊ����/�����
			if (i == 0)  //��һ��������������
			{
				opr1.result = CreateInt();
				ss << opr1.result;
				equation += ss.str();
				ss.str("");
			}
			else         //��һ���������������
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
				equation_end = equation_end + " �� " + equation;
				AddSub = true;
			}
			else if (j == 1)
			{
				equation_end = equation_end + " �� " + equation;
				AddSub = true;
			}
			else if (j == 2)
			{
				equation_end = equation_end + " �� " + equation;
				result = arry_2[n - 2] * arry_2[n - 1];
				arry_2[n - 2] = result;
				n--;
				m--;
				MulDiv = true;
			}
			else
			{
				equation_end = equation_end + " �� " + equation;
				result = arry_2[n - 2] / arry_2[n - 1];
				arry_2[n - 2] = result;
				n--;
				m--;
				MulDiv = true;
			}

		}
		//������ʽ���
		result_end = arry_2[0];
		for (i = 0; i <= m; i++)
		{
			if (arry_1[i] == 0)
				result_end = result_end + arry_2[i + 1];
			if (arry_1[i] == 1)
				result_end = result_end - arry_2[i + 1];
		}


	}
	//�Ӽ����޸���
	if (AddSub == true && AddSubControl_negative == 1)
	{
		if (result_end < 0)
			return false;
	}
	//�˳���������
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
	cout << setw(47) << "����ʽ����" << endl << endl;
	cout << setw(22) << "�����ʽ�������ã�" << endl << endl;
	cout << "            <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << "            <<                    1.��ʽ����                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    2.�����ʽ                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    3.���ſ���                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    4.��������                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    5.��������                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    6.�˳�����                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    7.�����ֵ                           <<" << endl;
	cout << "            <<                                                         <<" << endl;
	cout << "            <<                    8.��С��ֵ                           <<" << endl;
	cout << "            <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

	SetColor(BLUE,BLACK);
	switch (i)
	{
	case 0:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".��ʽ����";
			  break;
	}
	case 1:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".�����ʽ ";
			  break;
	}
	case 2:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".���ſ��� ";
			  break;
	}
	case 3:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".�������� ";
			  break;
	}
	case 4:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".�������� ";
			  break;
	}
	case 5:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".�˳����� ";
			  break;
	}
	case 6:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".�����ֵ ";
			  break;
	}
	case 7:
	{
			  gotoxy(34, 5 + i * 2);
			  cout << i + 1 << ".��С��ֵ ";
			  break;
	}
	}
	SetColor(YELLOW,BLACK);
	gotoxy(25, 22);
	cout << "�������趨��";
	cin >> l;
	SetColor(WHITE, BLACK);
	return l;
}

int main()
{
	//��ʼ������
	int ProblemNumber = 30;           //��ʾҪ���ɵ���Ŀ�ĸ���
	int OutWay = 0;                   //�����ʽ��0.��Ļ��ӡ 1.������ļ���
	int BracketControl = 1;           //���ſ��أ�0.������ 1.�������ţ�
	int AddSubControl_negative = 1;   //�Ӽ����޸�����0.������ 1.�������У�
	int MulDivControl_remainder = 1;  //�˳�����������0.������ 1.�������У�
	string equation[Size];            //�洢��ʽ
	float result[Size];
	srand(time(0));                 //���������ʱ������
	int arry[8];
	int i = 0,m;
	float answer;
	int answer_correct = 0;       //������ȷ��
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
				cout << "������󣡣���"<<endl;
				cout << "��ʾ�� �������Сֵ���Ϸ�����";
				system("pause");
			}
		}
		else if (i == 0)
		 {
			if (arry[i] <= 0)
			{
				i--;
				system("cls");
				cout << "������󣡣���"<<endl;
				cout << "��ʾ�� ����ĸ���Ҫ��С��1.";
				system("pause");
			}
		}
		else if (i != 6)
		{
			if (arry[i] != 0 && arry[i] != 1)
			{
				system("cls");
				i--;
				cout << "������󣡣���"<<endl;
				cout << "��ʾ�� �������ֵ 0 ����Ĭ�ϴ��ڣ�1 �������ڡ������ſ����� 0 ���������ţ� 1 ����û������;�����ʽ�� 0 ������Ļ��ӡ ��1 ����������ļ��� ";
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
		if (CreateEquation(BracketControl, AddSubControl_negative, MulDivControl_remainder, equation[i], result[i]))//��ʽ�Ϸ�
		{
			for (int j = 0; j < i; j++)
			{
				if (equation[i] == equation[j]) //��ʽ�ظ�
					m = 1;
			}

			if (m == 1) //�ظ�
			{
				i--;
			}
			else
			{
				cout <<endl<< "��" << i + 1 << "�⣺ " << equation[i] << " = ";
				cin >> answer;
				if ((int)(answer * 100) == (int)(result[i] * 100)) //�����ȷ
				{
					answer_correct++;
					SetColor(GREEN, BLACK);
					cout << "  ��ȷ����" << endl;
					SetColor(WHITE, BLACK);
				}
				else
				{
					SetColor(RED, BLACK);
					cout << "  ���󣡣���ȷ��Ϊ��" << result[i] << endl;
					SetColor(WHITE, BLACK);
				}
			}
		}
		else  //��ʽ���Ϸ�
			i--;
	}
	SetColor(GREEN, BLACK);
	cout <<endl<< "�ش���ȷ����Ŀ��Ϊ��";
	SetColor(YELLOW, BLACK);
	cout<<answer_correct;
	SetColor(WHITE, BLACK);
	system("pause");
	if (OutWay == 1)
	{
		system("cls");
		ofstream file("��Ŀ");
		if (!file)
		{
			cout << "�޷�������ļ�������";
			exit(0);
		}
		for (int i = 0; i < ProblemNumber; i++)
		{
			file << "��" << i + 1 << "��  ";
			for (int j = 0; j < equation[i].length(); j++)
				file << equation[i][j];
			file << "=" << endl;
		}
		cout << "��Ŀ��д�����Ŀ�ļ����У������ļ�������Ŀ��" << endl;

		ofstream answer("�ο���");
		if (!answer)
		{
			cout << "�޷�������ļ�������";
			exit(0);
		}
		for (int i = 0; i < ProblemNumber; i++)
		{
			answer << "��" << i + 1 << "��  ";
			for (int j = 0; j < equation[i].length(); j++)
				answer << equation[i][j];
			answer << "=" << result[i] << endl;
		}
		cout << "����д�����Ŀ�ļ����У����ļ������ο��𰸣�" << endl;
	}
	return 0;
}

