/*
匿名函数  
definition of inline functionality
    函数对象 | 仿函数

可以写在表达式里头 临时

[capture]()mutable throwSpec ->retType{}
*/

#include<iostream>
using namespace std;

int main(){

    //test1
    auto l = []{
        cout << "lambda" << endl;
    };
    l();

    //test2
    int id = 0;
    auto f = [&id] {
        cout << id << endl;
        ++id;
    };

    id=42;
    f();
    f();
    cout << id << endl;

    //test3
    int id2 = 0;
    auto q = [id2]() mutable {
        cout << id2 << endl;
        ++id2;
    };

    id2=42;
    q();
    q();
    cout << id << endl;
}