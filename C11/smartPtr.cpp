#include <memory>
#include <iostream>
using namespace std;

/*
    unique ptr
        独占所有权 轻量高效 没有额外的引用计数开销 支持移动语义  编译时绑定
    shared ptr
        共享所有权 16字节 or 8字节 开销 循环引用问题
    weak ptr 
        配合使用 解决循环引用问题 需要lock
*/

// *********  如果是shared ptr
// a ptr 是A的 引用计数 +1  其中A 中有一个B B的加1
// b ptr 是B的 引用计数 +1  其中B 中有一个A A的加1  
// 所以A B的引用计数都是2 
// 释放a ptr后 A = 1  B = 2 A不会销毁 所以B不会减
// 释放b ptr后 B = 1  A = 1 B不会销毁 所以A不会减
// *********

/*  
    如果使用weak ptr 打破循环关系 B中含有的是A的弱指针 则不会增加引用计数
    a ptr 创建后  A = 1 B = 1
    b ptr 创建后  A = 1 B = 2  调用b ptr -> dosomething 
    将weak ptr 获取shared ptr 此时 A = 2  离开作用域后 释放 A = 1
    因此当 a ptr 也离开作用域后 A = 0 A会被释放 B 也会被释放 
*/

class B;  // 前置声明

class A {
public:
    std::shared_ptr<B> b_ptr;

    void doSomething() {
        std::cout << "Doing something in A" << std::endl;
    }

    ~A() {
        std::cout << "A destructor called" << std::endl;
    }
};

class B {
public:
    std::weak_ptr<A> a_weak_ptr;

    void doSomething() {
        std::cout << "Doing something in B" << std::endl;
        // 使用 weak_ptr 的 lock() 函数获取 shared_ptr
        std::shared_ptr<A> a_ptr = a_weak_ptr.lock();
        if (a_ptr) {
            a_ptr->doSomething();
        }
    }

    ~B() {
        std::cout << "B destructor called" << std::endl;
    }
};

class D;  // 前置声明

class C {
public:
    std::shared_ptr<D> d_ptr;

    void doSomething() {
        std::cout << "Doing something in C" << std::endl;
    }

    ~C() {
        std::cout << "C destructor called" << std::endl;
    }
};

class D {
public:
    std::shared_ptr<C> c_ptr;

    void doSomething() {
        std::cout << "Doing something in D" << std::endl;
        if(c_ptr) c_ptr->doSomething();
    }

    ~D() {
        std::cout << "D destructor called" << std::endl;
    }
};

int main() {
    std::shared_ptr<A> a_ptr = std::make_shared<A>();
    std::shared_ptr<B> b_ptr = std::make_shared<B>();

    // 建立对象之间的引用关系
    a_ptr->b_ptr = b_ptr;
    b_ptr->a_weak_ptr = a_ptr;

    std::shared_ptr<C> c_ptr = std::make_shared<C>();
    std::shared_ptr<D> d_ptr = std::make_shared<D>();

    // 建立对象之间的引用关系
    c_ptr->d_ptr = d_ptr;
    d_ptr->c_ptr = c_ptr;

    // 调用 B 对象的方法，间接调用 A 对象的方法
    b_ptr->doSomething();
    d_ptr->doSomething();

    // 输出结果:
    // Doing something in B
    // Doing something in A

    return 0;
}


