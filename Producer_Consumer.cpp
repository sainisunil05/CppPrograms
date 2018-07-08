#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <condition_variable>

/*This program is to create Producer and Consumer threads.
  Producer threads will write data into the queue and Consumer threads
  will consume the data from queue. Queue size is fixed, and
  when queue is queue is empty consumer will do some thing else.
  Similarly when queue is full producer will do something else
  */

using namespace std;

class Producer_Consumer
{
    mutex mu;
    condition_variable cond_var;
    deque<int> que;
    int que_size;
public:
    Producer_Consumer(int _size)
    {
        que_size = _size;
    }
    void Producer()
    {
        while(true)
        {
            //Lock the mutex before writing to the queue
            unique_lock<mutex> lk(mu);
            //If queue is full then do not lock the mutex, do something else
            cond_var.wait(lk, [this](){
                      if(this->que.size() == que_size)
                        {
                            cout << "Queue is full, do something else" << endl;
                            this_thread::sleep_for(chrono::milliseconds(1000));
                        }
                        else
                        {
                            return true;
                        }
                      });
            //Push data to the queue
            que.push_back(10);
            cond_var.notify_all(); //Notify other threads waiting for the mutex
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }


    void Consumer()
    {
        while(true)
        {
            //Lock the mutex before removing from the queue
            unique_lock<mutex> lk(mu);
            //If queue is empty then do not lock the mutex, do something else
            cond_var.wait(lk, [this](){
                      if(this->que.empty())
                        {
                            cout << "Queue is empty, do something else" << endl;
                            this_thread::sleep_for(chrono::milliseconds(1000));
                        }
                        else
                        {
                            return true;
                        }
                      });
            cout << que.front() << endl;
            //Remove data from the queue
            que.pop_front();
            cond_var.notify_all();
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }
};

int main()
{
    Producer_Consumer prod_consumer(4);
    thread producer_1(&Producer_Consumer::Producer, &prod_consumer);
    thread producer_2(&Producer_Consumer::Producer, &prod_consumer);

    thread consumer_1(&Producer_Consumer::Consumer, &prod_consumer);
    thread consumer_2(&Producer_Consumer::Consumer, &prod_consumer);
    thread consumer_3(&Producer_Consumer::Consumer, &prod_consumer);

    // DO something

    producer_1.join();
    producer_2.join();

    consumer_1.join();
    consumer_2.join();
    consumer_3.join();

    /*Here we have 2 producers and 3 consumer so queue will be empty at sometime and then
      consumer threads will do something else. Similarly if producers threads are more than
      consumer threads then queue will be full at sometime and producer threads will
      do something else
    */
}
