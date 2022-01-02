#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
 
int n, m, b[100005];
vector <long long> v, d;
 
int getID(long long num){
    //離散化
    return lower_bound(d.begin(), d.end(), num) - d.begin() + 1;
}
 
int query(int x){
    int ret = 0;
    while (x){
        ret += b[x];
        x -= x & (-x);
    }
    return ret;
}
 
void update(int x, int y){
    while (x <= n){
        b[x] += y;
        x += x & (-x);
    }
}
 
int main() {
    while (cin >> n){
        memset(b, 0, sizeof(b));
        v.clear();
        for (int i = 0; i < n; i++){
            cin >> m;
            v.push_back(m);
        }
        d = v;

        for(int i = 0;i < n;i++) {
            printf("d[%d] : %d\n", i, d[i]);
        }

        sort(d.begin(), d.end());

        for(int i = 0;i < n;i++) {
            printf("d[%d] : %d\n", i, d[i]);
        }

        // 去除重複的數字
        // d.erase(unique(d.begin(), d.end()), d.end());

        // 算前綴和，就知道在自己前面有多少個鍵值比自己小的值
        for (int i = 1; i <= n; i++){
            // idx 代表值的排名
            printf("v[i - 1] : %d, getID(v[i - 1]) :%d\n", v[i - 1], getID(v[i - 1]));

            // getID 就是用值來找出值的排名
            int idx = getID(v[i-1]);
            update(idx, 1);
            cout << i - query(idx) + 1 << "\n";
        }
    }
}
