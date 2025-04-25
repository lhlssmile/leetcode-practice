package array;

public class rotate48 {
    public void rotate(int[][] matrix) {
        int n = matrix.length;

        // Step 1: 转置
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = tmp;
            }
        }

        // Step 2: 每一行反转
        for (int i = 0; i < n; i++) {
            reverseRow(matrix[i]);
        }
    }

    private void reverseRow(int[] row) {
        int left = 0, right = row.length - 1;
        while (left < right) {
            int tmp = row[left];
            row[left++] = row[right];
            row[right--] = tmp;
        }
    }

    public static void main(String[] args) {
        rotate48 rotate48 = new rotate48();
        int[][] matrix = {
                {1,2,3},{4,5,6},{7,8,9}
        };
        rotate48.rotate(matrix);
    }
}
