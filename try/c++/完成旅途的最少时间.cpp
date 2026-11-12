class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        auto check = [&](long long x) -> bool {
            long long sum = 0;
            for (int t : time) {
                sum += x / t;
                if (sum >= totalTrips) {
                    return true;
                }
            }
            return false;
            };
        int min_t = ranges::min(time);
        long long left = min_t - 1;
        long long right = 1LL * min_t * totalTrips;
        while (left + 1 < right) {
            long long mid = left + (right - left) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right;
    }
};