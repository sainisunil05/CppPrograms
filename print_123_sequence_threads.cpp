#include <iostream>
#include<thread>
#include<array>
#include<thread>
#include<deque>
#include<mutex>
#include<condition_variable>
#include<future>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include<deque>

using namespace std;
mutex mu;

condition_variable cond;
deque<int> que;

int test(int threadid)
{
    while(true)
    {
        if(threadid == 1)
        {
            unique_lock<mutex> ul(mu);
            cond.wait(ul, [&](){ if(que.back() == 1) return true;});
            cout << this_thread::get_id() <<  ":" << que.back() << endl;
            que.pop_back();
            que.push_back(2);
            cond.notify_all();
        }
        if(threadid == 2)
        {
            unique_lock<mutex> ul(mu);
            cond.wait(ul, [&](){ if(que.back() == 2) return true;});
            cout << this_thread::get_id() <<  ":" << que.back() << endl;
            que.pop_back();
            que.push_back(3);
            cond.notify_all();
        }
        if(threadid == 3)
        {
            unique_lock<mutex> ul(mu);
            cond.wait(ul, [&](){ if(que.back() == 3) return true;});
            cout << this_thread::get_id() <<  ":" << que.back() << endl;
            que.pop_back();
            que.push_back(1);
            cond.notify_all();
        }
    }
}

int main()
{
    que.push_back(1);

    thread th1 = thread(test, 1);
    thread th2 = thread(test, 2);
    thread th3 = thread(test, 3);

    th1.join();
    th2.join();
    th3.join();
}

