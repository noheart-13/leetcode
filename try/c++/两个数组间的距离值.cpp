//排序＋二分查找
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        ranges::sort(arr2);
        int ans = 0;
        for (int x : arr1) {
            auto num = ranges::lower_bound(arr2, x - d);
            if (num == arr2.end() || *num > x + d) {
                ans++;
            }
        }
        return ans;
    }
};
//排序＋双指针
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        ranges::sort(arr1);
        ranges::sort(arr2);
        int ans = 0, j = 0;
        for (int x : arr1) {
            while (j < arr2.size() && arr2[j] < x - d) {
                j++;
            }
            if (j == arr2.size() || arr2[j] > x + d) {
                ans++;
            }
        }
        return ans;
    }
};
