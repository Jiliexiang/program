//��1301-2�� 20132971 ������
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
			//���������
			a = rand() % 100;
			b = rand() % 100;
			d1 = rand() % 100;
			d2 = rand() % 100;
			d3 = rand() % 100;
			d4 = rand() % 100;
			n = rand() % 3;//����1��2��1�з�����2�޷���
			k = rand() % 4;//����1��2��3��1Ϊa�Ƿ�����2Ϊb�Ƿ�����3Ϊa��b���Ƿ���
			c = rand() % 100;//�����������
			c = c % 4;
			if (c == 1)
				m = '+';
			if (c == 2)
				m = '-';
			if (c == 3)
				m = '*';
			if (c == 0)
				m = '/';
			//���
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