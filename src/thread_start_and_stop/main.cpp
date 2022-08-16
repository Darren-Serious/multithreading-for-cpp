#include <iostream>
#include <thread>

using namespace std;

void myprint() {
  cout << "我的线程开始执行了。。。。" << endl;
  cout << "我的线程执行结束了。。。。" << endl;
}

class TA {
  public:
    void operator()() {
      cout << "我的线程operator()开始执行了。。。。" << endl;
      cout << "我的线程operator()执行结束了。。。。" << endl;
    }
};

int main() {
  thread mytobj(myprint);
  if (mytobj.joinable()) {
    mytobj.join();
  }
  // mytobj.detach();

  TA ta;
  thread mytobj1(ta);
  mytobj1.join();

  auto mylamthread = [] {
    cout << "我的线程3开始执行了。。。。" << endl;
    cout << "我的线程3执行结束了。。。。" << endl;
  };
  thread mytobj2(mylamthread);
  mytobj2.join();

  cout << "I Love China!" << endl;
  return 0;
}
