#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
    vector<int> v = {1, 2, 3, 4, 4, 5, 6, 7};

    printf("before : \n");

    for(int i = 0;i < v.size();i++) {
        printf("v[%d] :%d\n", i, v[i]);
    }

    printf("after : \n");

    unique(v.begin(), v.end());

    for(int i = 0;i < v.size();i++) {
        printf("v[%d] :%d\n", i, v[i]);
    }

    printf("----------\n");

    v = {1, 2, 3, 4, 4, 5, 6, 7};

    printf("before : \n");

    for(int i = 0;i < v.size();i++) {
        printf("v[%d] :%d\n", i, v[i]);
    }

    printf("after : \n");

    v.erase(unique(v.begin(), v.end()), v.end());

    for(int i = 0;i < v.size();i++) {
        printf("v[%d] :%d\n", i, v[i]);
    }

    return 0;
}


