#include <iostream>
using namespace std;

/*
Example of Variadic Templates.
*/
// 数量不定的模板

void print() {}
//处理最后参数为0的情况

//pack 参数包
template <typename T, typename... Types>
void print(const T &firstArg, const Types&... args)
{
    cout << firstArg << endl;
    print(args...);
}

int main()
{
    print(1, "2", 3.01);
    return 0;
}