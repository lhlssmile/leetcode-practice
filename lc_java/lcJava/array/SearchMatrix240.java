package array;


class SearchMatrix240{
    public boolean searchMatrix(int[][] matrix,int target){
        int m = matrix.length,n = matrix[0].length;
        int row = 0,col = n - 1;
        while(row < m && col >= 0){
            if(matrix[row][col] == target){
                return true;
            }else if(target > matrix[row][col]){
                row++;
            }else{
                col--;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        SearchMatrix240 sol = new SearchMatrix240();
        int[][] matrix = {
                {1,4,7,11,15},
                {2,5,8,12,19},
                {3,6,9,16,22},
                {10,13,14,17,24},
                {18,21,23,26,30}
        };
        int target = 20;
        System.out.println(sol.searchMatrix(matrix, target));
    }
}