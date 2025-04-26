package greedy;


class jump45{
    public int jump(int[] nums){
        int n = nums.length;
        int end = 0;    // 当前能到达的最远位置
        int maxPos = 0; // 下一步能到达的最远位置
        int step = 0;  // 跳跃次数

        for(int i = 0; i < n - 1; i++){
            maxPos = Math.max(maxPos,i + nums[i]);
            if(i == end){
                end = maxPos;
                step++;
            }
        }
        return step;
    }
    public static void main(String[] args){
        jump45 jump45 = new jump45();
        int[] nums = {2,3,1,1,4};
        System.out.println(jump45.jump(nums));
    }
}

