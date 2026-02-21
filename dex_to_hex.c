#include <stdio.h>

// 函数声明：将十进制数转换为十六进制数并输出
void dec_to_hex(int n);

/**
 * 主函数
 * 功能：接收用户输入的十进制数，调用dec_to_hex函数将其转换为十六进制并显示结果
 */
int main()
{
	int n; // 存储用户输入的十进制数
	
	printf("Enter n: "); // 提示用户输入
	scanf("%d", &n);     // 读取用户输入的十进制数
	
	printf("\n十进制数：%d 转换为十六进制数是：", n);
	dec_to_hex(n);        // 调用dec_to_hex函数进行转换
	
	return 0;
}

/**
 * dec_to_hex函数
 * 参数：n - 需要转换的十进制整数
 * 功能：将十进制整数转换为十六进制表示并输出
 */
void dec_to_hex(int n)
{
	char num[20]; // 用于存储十六进制数字符的数组
	int rem, i = 0, j; // rem存储余数, i是数组索引, j用于逆序输出
	
	// 处理0的特殊情况
	if (n == 0) {
		printf("0");
		return;
	}
	
	// 循环计算十六进制位
	// 算法原理：反复除以16，获取余数作为十六进制位
	do
	{
		rem = n % 16;   // 计算余数
		n = n / 16;     // 更新n为商
		
		// 根据余数确定对应的十六进制字符
		if (rem < 10)
			// 0-9的情况，直接加上字符'0'的ASCII值
			num[i] = rem + '0';
		else
			// 10-15的情况，先减去10再加上字符'A'的ASCII值
			num[i] = rem - 10 + 'A';
		
		i++; // 索引递增
	} while (n > 0); // 当商大于0时继续循环
	
	// 逆序输出字符数组num中的元素
	// 因为计算过程中十六进制位是逆序存储的
	for (j = i - 1; j >= 0; j--)
		printf("%c", num[j]);
}