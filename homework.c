#include <stdio.h>
const int N=10;//定义可处理整数的最大位数
int main()
{
	int num[N]={0};//以逆序方式存放输入整数的各位数字
	int n,i;
	printf("请输入一个长度不超过%d位正整数：",N);
	scanf("%d",&n);
	i=0;
	do		//将输入整数的各位数以逆序方式存放
		{
			num[i] = n % 10;
			i++;
			n=n/10;
		}while(n>0);

	int length;   //设置一个变量存放输入整数的长度
	length=i;     //获取整数长度
	
	//设置一个标志符来控制是否允许打印，初值为
	//若一开始连续的数字是0，则不允许打印，若从非0数字开始，则可以打印
	int isPrinted=0;

	printf("\n以逆序方式输出的整数：");
	for(i=0;i<length;i++)
	{
		if(isPrinted==0)	//原先不可以打印
		{
			if(num[i]!=0)   //非0数字，改变打印状态
				isPrinted=1;
		}
		if (isPrinted)		//若为打印状态，则输出数字
			printf("%d",num[i]);
	}

	if(isPrinted==0)//最后状态还是不可以打印(可以判定输入的是0)，则逆序也输出0
		printf("%d",0);

	printf("\n\n");
	return 0;
}