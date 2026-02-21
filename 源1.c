#include <stdio.h>
int c, a=4 ; 
int func1(int a , int b);
int main() 
{ //断点①
	int b=2, p=0; 
	c=1; 
	p=func1(b, a); //断点②
	printf("a=%d, b=%d, c=%d, p=%d\n",a,b,c,p); //断点⑤
	return 0;
}

int func1(int a , int b) 
{  
	c=a*b; //断点③
	a=b-1;
	b++; 
	return (a+b+1); //断点④
}