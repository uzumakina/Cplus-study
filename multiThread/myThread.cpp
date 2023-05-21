/*
void join()	等待线程结束并清理资源（会阻塞）
bool joinable()	返回线程是否可以执行join函数
void detach()	将线程与调用其的线程分离，彼此独立执行（此函数必须在线程创建时立即调用，且调用此函数会使其不能被join）
std::thread::id get_id()	获取线程id
thread& operator=(thread &&rhs)	见移动构造函数
（如果对象是joinable的，那么会调用std::terminate()结果程序）
*/
#include <iostream>
#include <thread>
using namespace std;

void doit() { cout << "World!" << endl; }

void countnumber(int id, unsigned int n) {
	for (unsigned int i = 1; i <= n; i++);
	cout << "Thread " << id << " finished!" << endl;
}
void testAsync() {
	thread th[10];
	for (int i = 0; i < 10; i++)
		th[i] = thread(countnumber, i, 100000000);
	for (int i = 0; i < 10; i++)
		th[i].join();
}

int n = 0;
void count() {
	for (int i = 1; i <= 100000; i++)
		n++;
}

int m=0;
#include<mutex>
mutex mtx;
void countMutex() {
	for (int i = 1; i <= 100000; i++) {
        mtx.lock();
        m++;
        mtx.unlock();
    }
}

int main() {
	// 这里的线程a使用了 C++11标准新增的lambda函数
	thread a([]{
		cout << "Hello, " << flush;
	}), b(doit);
    // 定义后就开始执行 而不是使用join  join是为了阻塞并回收资源
    //testAsync();
    a.join();
	b.join();


    //如果不加锁会出问题，理想情况以下输出结果应该是10000000
    thread th[100];
	for (thread &x : th)
		x = thread(count);
	for (thread &x : th)
		x.join();
	cout << n << endl;
    //解决方法 使用互斥锁
    thread thMux[100];
	for (thread &x : thMux)
		x = thread(countMutex);
	for (thread &x : thMux)
		x.join();
	cout << m << endl;
	return 0;
}


/*
同步（Synchronous）和异步（Asynchronous）是用于描述两种不同的执行模式或通信方式。

同步指的是程序按照顺序逐步执行，每个操作都会等待前一个操作完成后再进行。在同步模式下，调用者会主动等待被调用的操作完成，然后才能继续执行后续的操作。

异步指的是程序执行操作时不需要等待结果返回，而是继续执行后续操作。在异步模式下，调用者可以继续执行其他任务，而不必等待被调用的操作完成。
被调用的操作通常会在后台或另一个线程中执行，并在完成后通过回调或其他机制通知调用者。

以下是同步和异步的一些特点和区别：

同步：
调用者需要主动等待操作的完成。
顺序执行，按照调用顺序依次执行。
阻塞调用者线程，直到操作完成或超时。
通常易于理解和编写，但可能会导致程序的响应性下降。

异步：
调用者无需等待操作的完成，可以继续执行其他任务。
可以并发执行多个操作。
不会阻塞调用者线程，可以提高程序的响应性和吞吐量。
需要一定的编程复杂性，包括回调函数、异步任务的管理和错误处理等。

选择同步或异步的方式取决于具体的需求和场景。同步适合简单的顺序执行，操作之间有依赖关系且需要等待结果的情况。
异步适合并发执行多个操作，提高程序的并发性和响应性，特别是在需要处理大量IO操作或长时间运行的任务时。
*/