#include <stdio.h>
int main()
{
	int i,j£¬k=1,n=1;
	for(n;n<=9;++n)
	{
		if(k==n)
		{
			printf("\n")£»
		}
		else
		{
			for (i=1;i<=9;i++)
			{
				for (j=1;j<=9;j++)
				{
				printf("%d*%d=%2d ",i,j,i*j);
				k++;
				}
				printf("\n");
			}
		}
	}
	return 0;
}
