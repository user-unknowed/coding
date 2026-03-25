#include<stdio.h>
#include <math.h>
double triangle_area(double a, double b, double c);

int main()
{
	double a,b,c;
	printf("请输入三角形边长\n");
	scanf("%lf%lf%lf",&a,&b,&c);
	printf("s = %lf", triangle_area(a,b,c));
	return 0;
}

double triangle_area(double a, double b, double c)
{
	double s, p;
	p=(a+b+c)/2;
	s=sqrt(p*(p-a)*(p-b)*(p-c));
	return (s);
}
