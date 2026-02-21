#include <stdio.h>  
  
int main() {  
    int a, b, c, gcd, lcm;  
      
    printf("请输入两个整数:\n");  
     scanf("%d %d", &a, &b);  
     /* 保存原始输入，以便后面计算最小公倍数（LCM）时使用
         不改变原有辗转相除计算 GCD 的逻辑 */
     int orig_a = a, orig_b = b;
     c = a % b;  
    while (c != 0) {  
        a = b;  
        b = c;  
        c = a % b;  
    }  
    
    gcd = b;  
    printf("最大公约数是: %d\n", gcd);  
    
    /* 使用保存的原始值计算 LCM：LCM = orig_a / gcd * orig_b */
    lcm = (orig_a / gcd) * orig_b;
    printf("最小公倍数是: %d\n", lcm);
        
    return 0;  
}