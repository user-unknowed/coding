#include <stdio.h>
int main()
{
	int a=10;
	int result=(10>18) &&(a++>5);
	printf("a=%d\nresult=%d",a,result);
	return 0;
}