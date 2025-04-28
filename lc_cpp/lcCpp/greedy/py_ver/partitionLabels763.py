from typing import List
class PartitionLabels:
    def partitionLabels(self,s:str)-> List[int]:
        last_pos = [0] * 26
        for i in range(0,len(s)):
            last_pos[ord(s[i]) - ord('a')] = i
        max_end = 0
        start = 0
        ans = []
        for i in range(0,len(s)):
            max_end = max(max_end,last_pos[ord(s[i]) - ord('a')])
            if i == max_end:
                ans.append(i - start + 1)
                start = i + 1
        return ans



if __name__ == '__main__':
    partition_labels = PartitionLabels()
    res = partition_labels.partitionLabels("ababcbacadefegdehijhklij")
    print(res)