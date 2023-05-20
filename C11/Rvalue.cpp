// 右值 左值    operator=  的左右侧  | 临时对象 将亡值
// 不必要的copy  unnecessary 临时对象 放到容器去 移动构造
// right hand side object is an rvalue, then left hand can steal resources
// 完美转发 perfect forwarding

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class c{
    int num;
public:
    c() {}
    c(int x) : num(x) {}
    c(const c& c1){
        num = c1.num;
        cout << "copy assignment" << endl;
    }
    c operator=(const c& c1){
        cout << "lvalue" << endl;
    }
    c operator=(const c&& c1){
        cout << "rvalue" << endl;
    }
};


int main() {
    // insert(...,&x)   copy  重新分配一块内存 复制过来
    // insert(...,&&x)  move  把指针拷贝过来 指过去 （浅拷贝） 把原来的打断  不能继续使用  
    vector<c> vec;
    c c1(1);
    cout << "copy ctor" << endl;
    vec.push_back(c1);
    cout << "move ctor" << endl;
    vec.push_back(move(c1));


    c c2;
    c2 = c1;
    c c3;
    c3 = c(3);
}