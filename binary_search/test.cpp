// https://labuladong.gitbook.io/algo/di-ling-zhang-bi-du-xi-lie/er-fen-cha-zhao-xiang-jie
// 看這個教學的測試程式碼
// leetcode 704, 34 可以測試自己的算法
//
// 這篇文章把所有可能遇到的情況都條列出來，並仔細深究
// 這樣的方法與心態值得學習

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// 1. normal - close interval
int binarySearch(vector<int>& nums, int target) {

  int left = 0;
  int right = nums.size() - 1;
  int mid;

  // [left, right] close interval
  while(left <= right) {
    //mid = (left + right) / 2;
    mid = left + (right - left) / 2; // 避免 overflow    

    if(nums[mid] > target) {
      right = mid - 1;
    } else if(nums[mid] < target) {
      left = mid + 1;
    } else {
      return mid;
    }
  } 
  return -1;
}

// 2. normal - open interval
int close_binarySearch(vector<int>& nums, int target) {
  int left = 0;
  int right = nums.size(); //diff
  int mid;

  // [left, right)
  while(left < right) {
    mid = left + (right - left) / 2;

    if(nums[mid] > target) {
      right = mid; // diff
    } else if(nums[mid] < target) {
      left = mid + 1;
    } else {
      return mid;
    }
  }

  return -1;

}

// 3. normal - open interval version 2
int close_binarySearch_v2(vector<int>& nums, int target) {
  int left = 0;
  int right = nums.size();
  int mid;

  // [left, right)
  while(left < right) {
    mid = left + (right - left) / 2;

    if(nums[mid] > target) {
      right = mid;
    } else if(nums[mid] < target) {
      left = mid + 1;
    } else {
      return mid;
    }
  }

  // 跟 第1種方法只有這一行有差異
  return nums[left] == target ? left : -1; // diff

}

// 4. left - open interval - wrong 
int left_binarySearch(vector<int>& nums, int target) {
  int left = 0;
  int right = nums.size();
  int mid;

  // [left, right)
  while(left < right) {
    mid = left + (right - left) / 2;

    if(nums[mid] > target) {
      right = mid;
    } else if(nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  // kind of buggy
  // 這裡的意思是，在這個陣列中，比 target 小的有多少個
  return left;
}

// 5. left - open interval - the good one
int left_binarySearch_v2(vector<int>& nums, int target) {
  int left = 0;
  int right = nums.size();
  int mid;

  // [left, right)
  while(left < right) {
    mid = left + (right - left) / 2;

    if(nums[mid] > target) {
      right = mid;
    } else if(nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  // target 比值陣列中所有元素都還要大
  // 這時候 left 會被推到最右邊
  if(left == nums.size()) {
    return -1; 
  }

  return nums[left] == target ? left : -1;

}

// 6. left - close interval - right
int left_binarySearch_v3(vector<int>& nums, int target) {
  int left = 0;
  int right = nums.size() - 1;
  int mid;

  // [left, right]
  while(left <= right) {
    mid = left + (right - left) / 2;

    if(nums[mid] > target) {
      right = mid - 1;
    } else if(nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  // target 比值陣列中所有元素都還要大
  // 這時候 left 會被推到最右邊
  if(left == nums.size()) {
    return -1; 
  }

  return nums[left] == target ? left : -1;
  // 文章內給的程式碼
  /*
  if (left >= nums.size() || nums[left] != target) {
    return -1;
  } 
  return left;
  */

}

// 7. right - open interval - wrong
int right_binarySearch(vector<int>& nums, int target) {
  int left = 0;
  int right = nums.size();
  int mid;

  // [left, right)
  while(left < right) {
    mid = left + (right - left) / 2;

    if(nums[mid] > target) {
      right = mid;
    } else if(nums[mid] < target) {
      left = mid + 1;
    } else {
      left = mid + 1;
    }
  }

  // 這並不是解答，而是回傳在這個陣列裡，總共有多少值小於等於 target 
  return left;
}

// 8. right - open interval - the good one
int right_binarySearch_v2(vector<int>& nums, int target) {
  int left = 0;
  int right = nums.size();
  int mid;

  // [left, right)
  while(left < right) {
    mid = left + (right - left) / 2;

    if(nums[mid] > target) {
      right = mid;
    } else if(nums[mid] < target) {
      left = mid + 1;
    } else {
      left = mid + 1;
    }
  }

  if(left == 0) return -1;
  return nums[left - 1] == target ? left - 1 : -1;
}


// 9. right - close interval
int right_binarySearch_v3(vector<int>& nums, int target) {
  int left = 0;
  int right = nums.size() - 1;
  int mid;

  while(left <= right) {
    mid = (left + right) / 2;
    
    if(nums[mid] > target) {
      right = mid - 1;
    } else if(nums[mid] < target) {
      left = mid + 1;
    } else {
      left = mid + 1;
    } 

  }

  /* 我寫的，應該是錯了
  if(left == 0) return -1;
  return nums[left - 1] == target ? left - 1 : -1;   
  */
 
  if(right < 0 || nums[right] != target) {
    return -1;
  }
  return right;



}

int main() {


  //vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> nums = {1, 2, 3, 5, 5, 5, 7, 8, 9};

  for(int i = 0;i < nums.size();i++) {
    printf("%d ", nums[i]);
  }
  printf("\n");
 
  printf("I want to find 15\n"); 
  cout << binarySearch(nums, 15) << endl;
  cout << close_binarySearch(nums, 15) << endl;
  cout << close_binarySearch_v2(nums, 15) << endl;
  cout << left_binarySearch(nums, 15) << endl;
  cout << left_binarySearch_v2(nums, 15) << endl;
  cout << left_binarySearch_v3(nums, 15) << endl;
  cout << right_binarySearch(nums, 15) << endl;
  cout << right_binarySearch_v2(nums, 15) << endl;
  cout << right_binarySearch_v3(nums, 15) << endl;

  printf("\n\n\n");

  printf("I want to find 5\n"); 
  cout << binarySearch(nums, 5) << endl;
  cout << close_binarySearch(nums, 5) << endl;
  cout << close_binarySearch_v2(nums, 5) << endl;
  cout << left_binarySearch(nums, 5) << endl;
  cout << left_binarySearch_v2(nums, 5) << endl;
  cout << left_binarySearch_v3(nums, 5) << endl;
  cout << right_binarySearch(nums, 5) << endl;
  cout << right_binarySearch_v2(nums, 5) << endl;
  cout << right_binarySearch_v3(nums, 5) << endl;


  return 0;
}
