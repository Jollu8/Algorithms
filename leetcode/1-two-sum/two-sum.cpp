class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int t) {
        unordered_map<int, int> m;

        for(auto i = 0 ; i < nums.size(); ++i) {
            if(m.contains(t - nums[i])) return {m[t - nums[i]], i};
            else m[nums[i]] = i;
        }
        return {};
    }
};