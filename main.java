package ��������;
import java.util.Random;
import java.util.Scanner;

public class main {
	public static void main(String[] args)
	{
		System.out.println("��������Ҫ�������ٸ���������ʽ��");
		Scanner input = new Scanner(System.in);
		Scanner sc=new Scanner(System.in);
		int num=sc.nextInt();
		System.out.println("������������������ķ�Χ(min-max)��");
		int min=sc.nextInt();
		int max=sc.nextInt();
		System.out.println("�������������������ʽ����Ƿ����޸�����1����  2���ޣ���");
		int neg=sc.nextInt();
		System.out.println("�������������������ʽ����Ƿ����޳˳�����1����  2���ޣ���");
		int chengchu=sc.nextInt();
		System.out.println("�������������������ʽ����Ƿ�����������1����  2���ޣ���");
		int rem=sc.nextInt();
		System.out.println("�������������������ʽ�Ƿ������ţ�1����  2���ޣ���");
		int sem=sc.nextInt(); 		
		int zifu;
		int []   arr1 =  new  int [num+200] ;//�����һ�����������
		int []   arr2 =  new  int [num+200];//����ڶ������������
		char []   arr4 =  new  char [num+200];//�����������
		Random rand = new Random();
		
		for(int i=0;i<num+200;i++)
		{
			 arr1[i] = rand.nextInt(max-min+1)+min;//���ɵ�һ�����������
			 arr2[i] = rand.nextInt(max-min+1)+min;//���ɵ�һ�����������
			 /*�ж����޳˳���*/
			 if(chengchu==2)
				{
					 zifu = rand.nextInt(2)+1;
				}
				else
				{
					 zifu = rand.nextInt(4)+1;
				}
			if (zifu == 1)
				arr4[i] = '+';
			if (zifu == 2)
				arr4[i] = '-';
			if (zifu == 3)
				arr4[i] = '*';
			if (zifu == 4)
				arr4[i] = '/';	
	
		}
		
		
		/*�ж������ظ�*/
		for(int i=0;i<num+200;i++)
		{
			for(int j=1;j<num+200;j++)
			{
				if(arr1[i]==arr1[j])
				{
					if(arr4[i]==arr4[j])
					{
						if(arr2[i]==arr2[j])
						{
							arr2[j]=rand.nextInt(max-min+1)+min;//�������ȣ��������ɵڶ���������֤�����
						}
					}
				}
			}
		}
		
		
		/*�ж����������޸���*/
		if(neg==2)
		{
			for(int i=0;i<num+200;i++)
			{
				if(arr4[i]=='-')
				{
					int a=arr1[i]-arr2[i];
					while(a<0)//�ж�a�Ƿ�С��0����������޸�����
					{
						arr1[i] = rand.nextInt(max-min+1)+min;
						if(arr1[i]==0)
						{
							arr1[i] = rand.nextInt(max-min+1)+min;
						}
						arr2[i] = rand.nextInt(max-min+1)+min;
						{
							if(arr2[i]==0)
							{
								arr2[i] = rand.nextInt(max-min+1)+min;
							}
						}
						a=arr1[i]-arr2[i];
					}
				}
			}
		}
		
		
		/*�ж���������������*/
		if(rem==2)
		{
			for(int i=0;i<num+200;i++)
			{
				if(arr4[i]=='/')
				{
					int a=arr1[i]%arr2[i];
					while(a!=0)//�ж�a�Ƿ����0�����������������
					{
						arr1[i] = rand.nextInt(max-min+1)+min;
						arr2[i] = rand.nextInt(max-min+1)+min;
						a=arr1[i]%arr2[i];
					}
				}
			}	
		}	
		
		/*���*/
		for(int i=0;i<num;i++)
		{
			int a=rand.nextInt(3)+1;
			if(a==1)//�ж�һ��ʽ���������������ĸ�����������
			{
				int b=rand.nextInt(3)+1;
				/*�ĸ�ʽ�Ӳ��������Ƿ���������*/
				if(b==1)
				{
					System.out.println(arr1[i]+" "+arr4[i]+" "+arr2[i]+"+"+arr1[i+num]+" "+arr4[i+num]+" "+arr2[i+num]);
				}
				else
				{
					if(sem==1)
					{
						System.out.println("("+arr1[i]+" "+arr4[i]+" "+arr2[i]+")"+"+"+"("+arr1[i+num]+" "+arr4[i+num]+" "+arr2[i+num]+")");
					}
					else
					{
						System.out.println(arr1[i]+" "+arr4[i]+" "+arr2[i]+"+"+arr1[i+num]+" "+arr4[i+num]+" "+arr2[i+num]);
					}
				}
			}
			else
			{
				System.out.println(arr1[i]+" "+arr4[i]+" "+arr2[i]);
			}
		}
	}

}