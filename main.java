package 四则运算;
import java.util.Random;
import java.util.Scanner;

public class main {
	public static void main(String[] args)
	{
		System.out.println("请输入需要产生多少个四则运算式：");
		Scanner input = new Scanner(System.in);
		Scanner sc=new Scanner(System.in);
		int num=sc.nextInt();
		System.out.println("请输入你想产生的数的范围(min-max)：");
		int min=sc.nextInt();
		int max=sc.nextInt();
		System.out.println("请输入你想产生的运算式结果是否有无负数（1：有  2：无）：");
		int neg=sc.nextInt();
		System.out.println("请输入你想产生的运算式结果是否有无乘除法（1：有  2：无）：");
		int chengchu=sc.nextInt();
		System.out.println("请输入你想产生的运算式结果是否有无余数（1：有  2：无）：");
		int rem=sc.nextInt();
		System.out.println("请输入你想产生的运算式是否有括号（1：有  2：无）：");
		int sem=sc.nextInt(); 		
		int zifu;
		int []   arr1 =  new  int [num+200] ;//保存第一个随机生成数
		int []   arr2 =  new  int [num+200];//保存第二个随机生成数
		char []   arr4 =  new  char [num+200];//保存运算符号
		Random rand = new Random();
		
		for(int i=0;i<num+200;i++)
		{
			 arr1[i] = rand.nextInt(max-min+1)+min;//生成第一个随机生成数
			 arr2[i] = rand.nextInt(max-min+1)+min;//生成第一个随机生成数
			 /*判断有无乘除法*/
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
		
		
		/*判断有无重复*/
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
							arr2[j]=rand.nextInt(max-min+1)+min;//如果都相等，重新生成第二个数，保证不相等
						}
					}
				}
			}
		}
		
		
		/*判断运算结果有无负数*/
		if(neg==2)
		{
			for(int i=0;i<num+200;i++)
			{
				if(arr4[i]=='-')
				{
					int a=arr1[i]-arr2[i];
					while(a<0)//判断a是否小于0，（结果有无负数）
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
		
		
		/*判断运算结果有无余数*/
		if(rem==2)
		{
			for(int i=0;i<num+200;i++)
			{
				if(arr4[i]=='/')
				{
					int a=arr1[i]%arr2[i];
					while(a!=0)//判断a是否等于0，（结果有无余数）
					{
						arr1[i] = rand.nextInt(max-min+1)+min;
						arr2[i] = rand.nextInt(max-min+1)+min;
						a=arr1[i]%arr2[i];
					}
				}
			}	
		}	
		
		/*输出*/
		for(int i=0;i<num;i++)
		{
			int a=rand.nextInt(3)+1;
			if(a==1)//判断一个式子有两个数还是四个数参与运算
			{
				int b=rand.nextInt(3)+1;
				/*四个式子参与运算是否有无括号*/
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