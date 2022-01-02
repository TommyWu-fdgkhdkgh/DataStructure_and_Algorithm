/*
   就本質上來說，這題跟 zj-d794 感覺上一模一樣
   https://yuihuang.com/zj-d794/
   Q: 這裡實作的 BIT 是 0-indexed 嗎?
   A: 是 1-indexed
   
 */
class Solution {
    
private:
    vector<int> sorted;
    vector<int> BIT;
    int getIndex(int v) {
        return lower_bound(sorted.begin(), sorted.end(), v) - sorted.begin() + 1;
    }
    
    void update(int index, int val) {
        while (index < BIT.size()) {
            //printf("index : %d\n", index);
            BIT[index] += val;
            index += index & (-index);
        }
    }
    
    int query(int index) {
        int ret = 0;
        while (index > 0){
            ret += BIT[index];
            index -= index & (-index);
        }
        return ret;
    }
    
public:
    
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> v = vector<int>(nums.size(), 0);
        BIT = vector<int>(nums.size() + 1, 0);
        
        sorted = nums;
        sort(sorted.begin(), sorted.end());
        
        for(int i = nums.size() - 1;i >= 0;i--) {
            int getSortedIndex = getIndex(nums[i]);
            update(getSortedIndex, 1);
            int num = query(getSortedIndex - 1);
            v[i] = num;
        }
        return v;
    }
};





