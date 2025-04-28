//
// Created by 24276 on 2025/4/14.
//

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class count_good_triplets1534 {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int n = arr.size();
        int ans = 0;
        for (int i = 0;i < n - 2;i++){
            for(int j = i + 1;j < n - 1;j++){
                if (abs(arr[i] - arr[j]) > a){
                    break;
                }
                for(int k = j + 1;k < n;k++){
                    if(abs(arr[j] - arr[k]) > b || abs(arr[i] - arr[k]) > c){
                        break;
                    }
                    ++ans;
                }
            }
        }
        return ans;
    }
    int countGoodTri(vector<int>& arr,int a,int b,int c) {
        int n = arr.size(), mx = ranges::max(arr),ans = 0;
        vector<int> s(mx + 2);
        for(int j = 0;j < n;j++){
            int y = arr[j];
            for(int k = j + 1;k < n;k++){
                int z = arr[k];
                if(abs(arr[k] - y) > b){
                    continue;
                }
                int l = max({0,z - c,y - a});
                int r = min({mx,z + c,y + a});
                ans += max(s[r + 1] - s[l],0);
            }
            for(int v = y + 1;v < mx + 2;v++){
                s[v]++;         //存储的arr[i]的前缀和
            }
        }
        return ans;
    }
};

int main() {
    count_good_triplets1534 sol;
    vector<int> nums = {3,0,1,1,9,7};
    cout << sol.countGoodTri(nums,7,2,3);
    return 0;
}
