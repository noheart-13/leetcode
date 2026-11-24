class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {
        ranges::sort(price);
        auto check = [&](int sweet) -> bool {
            int count = 1;
            int last = price[0];
            for (int i = 1; i < price.size(); i++) {
                if (price[i] - last >= sweet) {
                    count++;
                    last = price[i];
                }
            }
            return count >= k;
            };
        int left = 0, right = price.back() - price[0] + 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? left : right) = mid;
        }
        return left;
    }
};