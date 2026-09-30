class Solution {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        int ans = 0;
        int a = capacityA, b = capacityB;
        int i = 0, j = plants.size() - 1;
        while (i < j) {
            if (a < plants[i]) {
                ans++;
                a = capacityA;
            }
            a -= plants[i++];
            if (b < plants[j]) {
                ans++;
                b = capacityB;
            }
            b -= plants[j--];
        }
        if (i == j && max(a, b) < plants[i]) {
            ans++;
        }
        return ans;
    }
};