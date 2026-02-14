#include<stdio.h>
int main()
{
	int array[6];
	int tmp=0,i;
	printf("input numbers:\n");
	scanf("%d",&array[6]);
	for(i=5;i<=0;i--)
	{
		if(array[i]<array[i-1])
		{
			array[i]=tmp;
			array[i]=array[i-1];
			array[i-1]=tmp;
		}
	}
	printf("array[6]=%d",array[6]);
	return 0;
}