#include <stdio.h>
int main( )
{
	int i, j, m, n,sum;
	i = 3;
	j = 7;
	printf("i=%d,j=%d\n",i,j);//Î»ÖÃ1
	m = ++i;//m=4,i=4
	printf("i=%d,m=%d\n",i,m);//Î»ÖÃ2
	n = j++;//n=7,j=8
	printf("j=%d,n=%d\n",j,n);//Î»ÖÃ3
	sum = (i++)+(++j)+(m--)+(--n);
	printf ("i=%d, j=%d, m=%d, n=%d, sum=%d\n",i,j,m,n,sum);//i=5, j=9, m=3, n=6, sum=23
	return 0;
}

