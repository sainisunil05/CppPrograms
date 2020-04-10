#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class lesscomp
{
public:
  bool operator() (const int& lhs, const int&rhs) const
  {
    return (lhs>rhs);
  }
};
class morecomp
{
public:
  bool operator() (const int& lhs, const int&rhs) const
  {
    return (lhs<rhs);
  }
};


class MedianFinder {
    typedef std::priority_queue<int,std::vector<int>,lesscomp> mypq_type_less;
    typedef std::priority_queue<int,std::vector<int>,morecomp> mypq_type_more;

    mypq_type_less first;
    mypq_type_more second;
public:
    MedianFinder() {
    }

    void addNum(int num) {
        if(first.empty()){
            first.push(num);
        }
        else if(num < first.top()){
            if(first.size() < second.size()){
                int top = second.top();
                second.pop();
                first.push(top);
            }
            second.push(num);
        }
        else{
            if(first.size() > second.size()){
                int top = first.top();
                first.pop();
                second.push(top);
            }
            first.push(num);
        }
        
        if(!first.empty() && !second.empty() && first.top() < second.top()){
            int temp = first.top();
            first.pop();
            first.push(second.top());
            second.pop();
            second.push(temp);
        }

    }

    double findMedian() {
        if(first.size() == second.size() && (!first.empty() && !second.empty())){
            return (double(first.top()) + double(second.top()) ) / 2;
        }
        else if(first.size() > second.size()){
            return double(first.top());
        }
        else if(second.size() > first.size()){
            return double(second.top());
        }
        else{
            return 0;
        }
    }

};

int main(){
MedianFinder mf;
mf.addNum(40);
cout << mf.findMedian() << "  ";
mf.addNum(12);
cout << mf.findMedian() << "  ";
mf.addNum(16);
cout << mf.findMedian() << "  ";
mf.addNum(14);
cout << mf.findMedian() << "  ";
mf.addNum(35);

cout << endl;
}
