#include <iostream>
#include <thread>

using namespace std;

class A {
  public:
    int m_i;
    // 类型转换构造函数，可以把一个int转换成一个类对象
    A(int a) :m_i(a) {cout << "A::A(int a)构造函数执行" << this << " thread_id = " << this_thread::get_id() << endl;}
    A(const A &a) :m_i(a.m_i) {cout << "A::A(const A)拷贝构造函数执行" << this << " thread_id = " << this_thread::get_id() << endl;}
    ~A() {cout << "A::~A()析构函数执行" << this << " thread_id = " << this_thread::get_id() << endl;}
    void thread_work(int num) {
      cout << "子线程thread_work执行" << this << " thread_id = " << this_thread::get_id() << endl;
    }
    void operator()(int num) {
      cout << "子线程()执行" << this << " thread_id = " << this_thread::get_id() << endl;
    }
};


//void myprint(const int i, const A pmybuf) {   // 会多一次拷贝构造
void myprint(const int i, const A &pmybuf) {
  cout << "子线程myprint的参数地址为" << &pmybuf << " thread_id = " << this_thread::get_id() << endl;
  return;
}

void myprint1(A &pmybuf) {
  pmybuf.m_i = 199;
  cout << "子线程myprint1的参数地址为" << &pmybuf << " thread_id = " << this_thread::get_id() << endl;
  return;
}

void myprint2(unique_ptr<int> pzn) {
  cout << "子线程myprint2的参数地址为" << pzn << " thread_id = " << this_thread::get_id() << endl;
  return;
}

int main() {
  cout << "主线程id是" << " thread_id = " << this_thread::get_id() << endl; 

  int mvar = 1;
  int mysecondpar = 12;
  thread mytobj(myprint, mvar, A(mysecondpar)); // 使用临时对象
  //thread mytobj(myprint, mvar, mysecondpar); 

  mytobj.join();
  //mytobj.detach();

  A myobj(mvar);
  thread mytobj1(myprint1, std::ref(myobj));

  mytobj1.join();
  cout << "myobj.m_i = " << myobj.m_i << endl;

  unique_ptr<int> myp(new int(100));
  cout << "&myp = " << myp << endl;
  thread mytobj2(myprint2, std::move(myp));

  mytobj2.join();
  cout << "&myp = " << myp << endl;

  A myobj1(10);
  thread mytobj3(&A::thread_work, myobj1, 15); // 用成员函数指针作线程函数
  thread mytobj4(myobj1, 15);

  mytobj3.join();
  mytobj4.join();
  cout << "I Love China!" << endl;
  return 0;
}
