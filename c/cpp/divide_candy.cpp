//
// Created by ababa on 2026/1/25.
//
#include<iostream>
using namespace std;
int main() {
    int n;
    int count=0;
    cin>>n;
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n-i;j++) {
           count++;
        }
    }//暴力双重枚举，count=(n-1)*(n-2)/n
    cout << count;
    return 0;
}
