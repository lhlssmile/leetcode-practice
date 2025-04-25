package array;



class minCosts3502 {
    public int[] minCosts(int[] cost){
        int n = cost.length;
        int[] ans = new int[n];
        ans[0] = cost[0];
        for(int i = 1;i<n;i++){
            ans[i] = Math.min(ans[i-1],cost[i]);
        }
        return ans;
    }
    public void main(){
        minCosts3502 sol = new minCosts3502();
        int[] cost = {5,3,1,2,4};
        int[] ans = sol.minCosts(cost);
        for(int i = 0;i<ans.length;i++){
            System.out.println(ans[i]);
        }
    }
}