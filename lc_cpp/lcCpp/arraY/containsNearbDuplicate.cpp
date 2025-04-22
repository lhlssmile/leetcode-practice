// tag: array, hash table,mov windows
#include <vector>
#include <iostream>
#include <unordered_map>
class containsNearBySolution{
public:
    bool containsNearbyDuplicate(std::vector<int>& nums,int k){
        //whether index reflected num appear,store index,not value.
        //key store value, value store index.
        std::unordered_map<int,int> mp;
        for (int i = 0; i < nums.size(); ++i) {
            //find in map first, if true then no num in the map
            if(mp.find(nums[i]) != mp.end()){
                //then check the Difference
                if (i - mp[nums[i]] <= k){
                    return true;
                }
            }
            //update index
            mp[nums[i]] = i;
        }
        return false;
    }
};
int main() {
    containsNearBySolution ps;
    std::vector<int> nums = {1,2,3,1,2,3};
    int k = 2;
    std::cout << ps.containsNearbyDuplicate(nums,k) << std::endl;
    return 0;
}
