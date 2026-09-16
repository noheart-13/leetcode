#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        ranges::sort(nums);
        vector<vector<int>> ans;
        int n = nums.size();
        for (int i = 0; i < n - 2; ++i) {
            for (int j = 0; j < i; j++) {
                int k = j + 1, l = n - 1;
                while (k < l) {
                    int s = nums[i] + nums[j] + nums[k] + nums[l];
                    if (s == target) {
                        ans.push_back({ nums[i],nums[j],nums[k],nums[l] });
                        k++; l--;
                    }
                    else if (s < target) {
                        k++;
                    }
                    else {
                        l--;
                    }
                }
            }
        }
        return ans;
    }
};