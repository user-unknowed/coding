//
// Created by ababa on 2026/1/21.
//
#include<iostream>
using namespace std;
int main() {
    int a1[10];//初始化数组a（只能输入数字，否则会乱码）
    char b[8]={'h','e','l','l','o','c','p','p',};//初始化字符串b
    char c[10];//初始化字符串c
    char d[20];

    cout << "please enter your name:";
    cin.getline(d,19);//‘get’同理，属于特殊的字符串输入方式（一口气

    cout << "please enter 10 numbers:";
    for(int i=0;i<10;i++) {
        cin >> a1[i];
    }//输入其中数字(或者字母)(逐个，唯一？)
    for(int i=0;i<10;i++) {
        cout << "the "<< i << " number is:" << a1[i] << endl;
    }//输出数字

    cout << endl;
    cout << "then...";
    for(int i=0;i<10;i++) {
        cout << b[i];
    }//输出字符串（逐个

    cin >> c;//输入字符串（一口气
    cout << c << endl;//输出（一口气

    cout <<  d;//输入字符串（一口气

    return 0;
}
