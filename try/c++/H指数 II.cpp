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