//信1301-2班 20132971 纪烈翔
//2016/3/6
#include "iostream" 
#include "time.h"
using namespace std;
void main()
{
	int a,b,c,i,n,k,d1,d2,d3,d4;
	char m;
	srand((int)time(NULL));
		for (i = 0; i < 30; i++)
		{
			//生成随机数
			a = rand() % 100;
			b = rand() % 100;
			d1 = rand() % 100;
			d2 = rand() % 100;
			d3 = rand() % 100;
			d4 = rand() % 100;
			n = rand() % 3;//生成1或2，1有分数，2无分数
			k = rand() % 4;//生成1，2或3，1为a是分数，2为b是分数，3为a，b都是分数
			c = rand() % 100;//生成运算符号
			c = c % 4;
			if (c == 1)
				m = '+';
			if (c == 2)
				m = '-';
			if (c == 3)
				m = '*';
			if (c == 0)
				m = '/';
			//输出
			if (n == 1)
			{
				if (k == 1)
				{
					if (d1>=d2)
						cout << d2 << "/" << d1 << "  " << m << "  " << b << "=" << endl;
					else
						cout << d1 << "/" << d2 << "  " << m << "  " << b << "=" << endl;
				}
				if (k == 2)
				{
					if (d3>=d4)
						cout << a << "  " << m << "  " << d4 << "/" << d3 << "=" << endl;
					else
						cout << a << "  " << m << "  " << d3 << "/" << d4 << "=" << endl;
				}
				if (k == 3)
				{
					if (d1 >= d2)
					{
						if (d3 >= d4)
							cout << d2 << "/" << d1 << "  " << m << "  " << d4 << "/" << d3 << "=" << endl;
						else
							cout << d2 << "/" << d1 << "  " << m << "  " << d3 << "/" << d4 << "=" << endl;
					}
					else
					{
						if (d3 >= d4)
							cout << d1 << "/" << d2 << "  " << m << "  " << d4 << "/" << d3 << "=" << endl;
						else
							cout << d1 << "/" << d2 << "  " << m << "  " << d3 << "/" << d4 << "=" << endl;
					}
				}
			}
			else
			cout << a << "  " << m << "  " << b << "=" << endl;
		}

}