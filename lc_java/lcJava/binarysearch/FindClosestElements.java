import java.util.*;

public class FindClosestElements {
    // 方法1: 二分扩展法
    public List<Integer> findClosestElements(int[] arr, int k, int x) {
        int n = arr.length;
        int idx = Arrays.binarySearch(arr, x);
        if (idx < 0) idx = -(idx + 1);
        
        int left = idx - 1, right = idx;
        
        while (right - left - 1 < k) {
            if (left < 0) {
                right++;
            } else if (right >= n) {
                left--;
            } else {
                if (x - arr[left] <= arr[right] - x) {
                    left--;
                } else {
                    right++;
                }
            }
        }
        
        List<Integer> result = new ArrayList<>();
        for (int i = left + 1; i < right; i++) {
            result.add(arr[i]);
        }
        return result;
    }
    
    // 方法2: 滑动窗口法
    public List<Integer> findClosestElementsSlidingWindow(int[] arr, int k, int x) {
        int left = 0, right = arr.length - k;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (x - arr[mid] > arr[mid + k] - x) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        List<Integer> result = new ArrayList<>();
        for (int i = left; i < left + k; i++) {
            result.add(arr[i]);
        }
        return result;
    }
    
    // 方法3: 大根堆法
    public List<Integer> findClosestElementsMaxHeap(int[] arr, int k, int x) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> {
            if (a[0] != b[0]) return b[0] - a[0]; // 距离大的在前
            return b[1] - a[1]; // 距离相同时，值大的在前
        });
        
        for (int num : arr) {
            int distance = Math.abs(num - x);
            if (pq.size() < k) {
                pq.offer(new int[]{distance, num});
            } else if (distance < pq.peek()[0] || 
                      (distance == pq.peek()[0] && num < pq.peek()[1])) {
                pq.poll();
                pq.offer(new int[]{distance, num});
            }
        }
        
        List<Integer> result = new ArrayList<>();
        while (!pq.isEmpty()) {
            result.add(pq.poll()[1]);
        }
        Collections.sort(result);
        return result;
    }
    
    // 方法3优化: 大根堆法 - 提前终止
    public List<Integer> findClosestElementsOptimizedHeap(int[] arr, int k, int x) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> {
            if (a[0] != b[0]) return b[0] - a[0];
            return b[1] - a[1];
        });
        
        for (int i = 0; i < arr.length; i++) {
            int distance = Math.abs(arr[i] - x);
            if (pq.size() < k) {
                pq.offer(new int[]{distance, arr[i], i});
            } else if (distance < pq.peek()[0] || 
                      (distance == pq.peek()[0] && arr[i] < pq.peek()[1])) {
                pq.poll();
                pq.offer(new int[]{distance, arr[i], i});
            } else if (distance > pq.peek()[0]) {
                break;
            }
        }
        
        List<int[]> temp = new ArrayList<>();
        while (!pq.isEmpty()) {
            int[] item = pq.poll();
            temp.add(new int[]{item[2], item[1]}); // {index, value}
        }
        
        temp.sort((a, b) -> a[0] - b[0]);
        List<Integer> result = new ArrayList<>();
        for (int[] item : temp) {
            result.add(item[1]);
        }
        return result;
    }
    
    public static void main(String[] args) {
        FindClosestElements sol = new FindClosestElements();
        int[] arr = {1, 2, 3, 4, 5};
        int k = 4, x = 3;
        
        System.out.println("二分扩展法: " + sol.findClosestElements(arr, k, x));
        System.out.println("滑动窗口法: " + sol.findClosestElementsSlidingWindow(arr, k, x));
        System.out.println("大根堆法: " + sol.findClosestElementsMaxHeap(arr, k, x));
    }
}