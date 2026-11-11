//无lambda表达式
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1, right = *max_element(piles.begin(), piles.end());
        if (piles.size() == h) {
            return right;
        }
        else {
            while (left < right) {
                int speed = left + (right - left) / 2;
                long long time = 0;
                for (int i = 0; i < piles.size(); i++) {
                    time += (piles[i] + speed - 1) / speed;
                }
                if (time <= h) {
                    right = speed;
                }
                else {
                    left = speed + 1;
                }
            }
            return left;
        }
    }
};
//使用lambda表达式
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        auto check = [&](int k) -> bool {
            int sum = piles.size();
            for (int p : piles) {
                sum += (p - 1) / k;
                if (sum > h) {
                    return false;
                }
            }
            return true;
            };

        int left = 0; // 循环不变量：恒为 false
        int right = ranges::max(piles); // 循环不变量：恒为 true
        while (left + 1 < right) { // 开区间不为空
            int mid = left + (right - left) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right; // 最小的 true
    }
};