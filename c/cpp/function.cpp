//
// Created by ababa on 2026/1/22.
//
#include<iostream>
#include<string>//C中也有这个包，作用是把cpp的字符串语言向c的方向靠近
using namespace std;
int main () {
    string a = "hello world";//定义字符串a，与char定义的完全一致
    string b;
    string c;

    b = a;//通过等号来给字符串b赋上a的“值”（想不到吧虽然我也想不到）

    cout << a << " " << b << endl;//输出两个相同的字符串

    c = a + " "+ b;//用加法给字符串c赋值，甚至可以把空格（“ ”）加进去
    cout << c << endl;

    return 0;
}