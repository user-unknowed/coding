//
// Created by ababa on 2026/1/19.
//
#include<iostream>
using namespace std;
int func(int n) {
    return n*n;
}
int main() {
    int n,m;
    cout << "Enter a number: ";
    cin >> n;
    m = func(n);//引用func函数，与c一致
    cout << m << endl;
    return 0;
}
