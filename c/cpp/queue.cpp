//
// Created by ababa on 2026/2/8.
//
#include<iostream>
#include<queue>//记得加，这个是实现队列的必要条件
using namespace std;
int main() {
    queue<int> q;//定义队列，内容为整型数，后记为q
    q.push(1);//入队（把数字向队首方向加入
    q.push(3);
    q.push(2);
    int font=q.front();//查询队首
    int count=q.size();//查询队长
    bool empty=q.empty();//查询队列是否为空队列
    cout<<font<<endl;
    cout<<count<<endl;
    cout<<empty<<endl;
    for(int i=0;i<3;i++) {
        cout<<q.front()<<endl;
        q.pop();//出队（让数字向队尾方向退出，方向务必记牢
    }
    for(int i=0;i<4;i++) {
        cout<<q.front()<<endl;
        q.pop();//出队的时候如果大于队列内元素总数，则会展示一个随机三位数或者报错（？
    }
    cout<<endl;
    return 0;
}
//其实单向队列如水杯，只有一个口