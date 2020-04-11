#include<iostream>
#include<vector>
#include <chrono>
#include<algorithm>

using namespace std;

class Solution {
public:
    uint64_t timeSinceEpochMillisec() {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    int maxArea(vector<int>& height) {
        int len = height.size() - 1;

        vector<int>::iterator first = height.begin();
        vector<int>::reverse_iterator last = height.rbegin();

        int maxarea = 0;

        while(len >= 2){
            int ht = *first < *last ? *first++ : *last++;
            int area = ht * len;
            if(maxarea < area){
                maxarea = area;
            }
            len--;
        }

        if(maxarea < min(*first, *last)){
            maxarea = min(*first, *last);
        }
        return maxarea;
    }
};

int main(){

    vector<int> height = {1,8,6,2,5,4,8,3,7};
    /*vector<int> height = {1, 6, 3, 12, 15, 4, 33, 21, 6};
    vector<int> height = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> height = {1, 0, 1, 1 }*/

    Solution sl;
    long st = sl.timeSinceEpochMillisec();
    long en = sl.timeSinceEpochMillisec();
    cout << "Result = " << sl.maxArea(height) << "      Run Time: " << (en - st)  << "  MilSec" <<  endl;
}
