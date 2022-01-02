/*
back tracking + state prunning?

or greedy ?

最大流?

太久沒看到這個題形，我被嚇傻ㄌ QQ


*/


class Solution {
public:
    
    void DFS(int x, int y, vector<vector<int>> &heights, vector<vector<bool>> &record, int threash_hold){
        int newx;
        int newy;
        
        //up
        newx = x - 1;
        newy = y;
        
        if(newx >= 0 && newx < heights.size() && newy >= 0 && newy < heights[0].size()) {
            int diff = abs(heights[x][y] - heights[newx][newy]);
            if(diff <= threash_hold && record[newx][newy] == false) {
                record[newx][newy] = true;
                DFS(newx, newy, heights, record, threash_hold);
            }
        }
        
        
        //down
        newx = x + 1;
        newy = y;
        
        if(newx >= 0 && newx < heights.size() && newy >= 0 && newy < heights[0].size()) {
            int diff = abs(heights[x][y] - heights[newx][newy]);
            if(diff <= threash_hold && record[newx][newy] == false) {
                record[newx][newy] = true;
                DFS(newx, newy, heights, record, threash_hold);
            }
        }
        
        
        //left
        newx = x;
        newy = y - 1;
        if(newx >= 0 && newx < heights.size() && newy >= 0 && newy < heights[0].size()) {
            int diff = abs(heights[x][y] - heights[newx][newy]);
            if(diff <= threash_hold && record[newx][newy] == false) {
                record[newx][newy] = true;
                DFS(newx, newy, heights, record, threash_hold);
            }
        }
        
        
        //right
        newx = x;
        newy = y + 1;
        if(newx >= 0 && newx < heights.size() && newy >= 0 && newy < heights[0].size()) {
            int diff = abs(heights[x][y] - heights[newx][newy]);
            if(diff <= threash_hold && record[newx][newy] == false) {
                record[newx][newy] = true;
                DFS(newx, newy, heights, record, threash_hold);
            }
        }
        
    }
    
    
    int minimumEffortPath(vector<vector<int>>& heights) {
        
        vector<vector<bool>> record = vector<vector<bool>>(heights.size(), vector<bool>(heights[0].size(), false));
        
        if(heights.size() == 0 && heights[0].size() == 0) {
            return 0;
        } else if(heights.size() == 1 && heights[0].size() == 1){
            return 0;
        }
            
        
        
        record[0][0] = true;        
        
        int left = 0;
        int right = 1000000;
        int minval = INT_MAX;
        
        while(left <= right) {
            
            //printf("left : %d, right : %d\n", left, right);
            
            int mid = (left + right)/2;
            DFS(0, 0, heights, record, mid);
            if(record[heights.size() - 1][heights[0].size() - 1]){
                if(mid < minval) {
                    minval = mid;
                }
                right = mid - 1;
                
            } else {
                left = mid + 1;
            }
            record = vector<vector<bool>>(heights.size(), vector<bool>(heights[0].size(), false));
            
            
            
        }
        
        return minval;
    }
}
