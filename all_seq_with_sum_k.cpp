#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
#include <set>
#include<map>

#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<int, int> prevSum;

public:

    int subarraySum(vector<int>& nums, int k)
    {
        prevSum.clear();
        int total = 0;
        int count = 0;

        for(int i=0; i<nums.size(); i++){
            total = total + nums[i];

            if(total == k){
                count++;
            }

            if(prevSum.find(total - k) != prevSum.end()){
                count = count + prevSum[total - k];
            }
            prevSum[total]++;
        }
        return count;
    }
};

int main(){
    Solution sl;

    vector<int> nums_1 =  {0,0,0,0,0,0,0,0,0,0};
    cout << sl.subarraySum(nums_1, 0) << endl;
    vector<int> nums_2 = {1,2,3,-2,3,5,6,-1,-4,6};
    cout << sl.subarraySum(nums_2, 6) << endl;
    vector<int> nums_3 =   { 10, 2, -2, -20, 10 };
    cout << sl.subarraySum(nums_3, -10) << endl;
}
