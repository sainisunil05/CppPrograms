#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int size_first = nums1.size();
        int size_second = nums2.size();

        if(nums2.size() == 0){
            if(size_first % 2 == 0){
                return (double(nums1[size_first/2-1]) + double(nums1[size_first/2])) / 2;
            }
            else{
                return nums1[size_first/2];
            }
        }

        if(nums1.size() == 0){
            if(size_second % 2 == 0){
                return (double(nums2[size_second/2-1]) + double(nums2[size_second/2])) / 2;
            }
            else{
                return nums2[size_second/2];
            }
        }

        const int out_len = size_first + size_second;

        std::vector<int> v(out_len);
        int i, j, index;
        i = j = index = 0;
        int first, second;
        first = second = min(nums1[0], nums2[0]);
        for (index; index<=out_len/2; index++){
            if(i < nums1.size() && nums1[i] <= nums2[j]){
                first = second;
                second = nums1[i];
                i++;
                if(i == nums1.size()) break;
            }
            else if(j < nums2.size() && nums2[j] < nums1[i]){
                first = second;
                second = nums2[j];
                j++;
                if(j == nums2.size()) break;
            }
        }
        index++;
        for (index; index<=out_len/2; index++){
            if(i < nums1.size()){
                first = second;
                second = nums1[i];
                i++;
            }
            if(j < nums2.size()){
                first = second;
                second = nums2[j];
                j++;
            }
        }
        if(out_len % 2 == 0){
            return (double(first) + double(second))  / 2;
        }
        else{
            return second;
        }
    }
};

int main(){
    Solution sl;
    vector<int> nums1 = {};
    vector<int> nums2 = {3,4,5,8};
    cout << sl.findMedianSortedArrays(nums1, nums2) << endl;
}
