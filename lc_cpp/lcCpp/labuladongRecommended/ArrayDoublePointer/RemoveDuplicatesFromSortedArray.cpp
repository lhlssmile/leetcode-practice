#include <iostream>
#include <vector>
class removeDuplicatesFromSortedArray{
public:
    int removeDuplicates(std::vector<int>& nums){
        int slow = 0;
        for(int fast = 1; fast < nums.size();++fast){
            if(nums[slow] != nums[fast]){
                ++slow;
                nums[slow] = nums[fast];
            }
        }
        return slow + 1;
    }
};
struct Entity{
    static int x,y;
    void print(){
        std::cout << x << "," << y << std::endl;
    }
};
int Entity::x;
int Entity::y;
int main() {
    removeDuplicatesFromSortedArray ps;
    std::vector<int> nums = {0,0,1,1,1,2,2,3,3,4};
    std::cout << ps.removeDuplicates(nums) << std::endl;
    int val = 9;
    double *ptr = (double *)&val;
    std::cout << ptr << std::endl;
    std::cout << "------------" << std::endl;
    Entity e;
    e.x = 2,e.y = 3;
    e.print();

    Entity e1;
    Entity::x = 5;
    Entity::y = 8;
    e1.print();         //5,8
    std::cin.get();
    return 0;
}
