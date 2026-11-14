//时间复杂发度 O(nlogn)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        auto check = [&](long long x) ->bool {
            long long sum = 0;
            for (int t : citations) {
                if (t >= x) {
                    sum++;
                }
            }
            if (sum >= x) {
                return true;
            }
            else {
                return false;
            }
            };
        long long left = 0;
        long long right = citations.size() + 1;
        while (left + 1 < right) {
            long long mid = left + (right - left) / 2;
            (check(mid) ? left : right) = mid;
        }
        return left;
    }
};
//时间复杂度 O(log n)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = static_cast<int>(citations.size());
        int left = 0;
        int right = n + 1;

        while (left + 1 < right) {
            int mid = left + (right - left) / 2;

            if (citations[n - mid] >= mid) {
                left = mid;
            }
            else {
                right = mid;
            }
        }

        return left;
    }
};