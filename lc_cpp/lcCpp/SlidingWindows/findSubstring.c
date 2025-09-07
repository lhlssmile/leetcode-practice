#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 5000
#define MAX_WORD_LEN 30
#define MAX_STR_LEN 10000

// 简单哈希表结构
typedef struct {
    char key[MAX_WORD_LEN + 1];
    int value;
    int used;
} HashEntry;

typedef struct {
    HashEntry entries[MAX_WORDS];
    int size;
} HashMap;

// 简单哈希函数
unsigned int hash(const char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % MAX_WORDS;
}

// 初始化哈希表
void initHashMap(HashMap* map) {
    map->size = 0;
    for (int i = 0; i < MAX_WORDS; i++) {
        map->entries[i].used = 0;
        map->entries[i].value = 0;
    }
}

// 在哈希表中查找或插入
int* getOrInsert(HashMap* map, const char* key) {
    unsigned int index = hash(key);
    
    // 线性探测
    while (map->entries[index].used && strcmp(map->entries[index].key, key) != 0) {
        index = (index + 1) % MAX_WORDS;
    }
    
    if (!map->entries[index].used) {
        strcpy(map->entries[index].key, key);
        map->entries[index].value = 0;
        map->entries[index].used = 1;
        map->size++;
    }
    
    return &map->entries[index].value;
}

// 在哈希表中查找
int* get(HashMap* map, const char* key) {
    unsigned int index = hash(key);
    
    while (map->entries[index].used) {
        if (strcmp(map->entries[index].key, key) == 0) {
            return &map->entries[index].value;
        }
        index = (index + 1) % MAX_WORDS;
    }
    
    return NULL;
}

// 检查键是否存在
int contains(HashMap* map, const char* key) {
    return get(map, key) != NULL;
}

// 清空哈希表
void clearHashMap(HashMap* map) {
    for (int i = 0; i < MAX_WORDS; i++) {
        map->entries[i].used = 0;
        map->entries[i].value = 0;
    }
    map->size = 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    *returnSize = 0;
    
    if (wordsSize == 0 || !s || !words) {
        return NULL;
    }
    
    int n = wordsSize;
    int m = strlen(s);
    int k = strlen(words[0]);
    int totalLen = n * k;
    
    if (m < totalLen) {
        return NULL;
    }
    
    int* ans = (int*)malloc(m * sizeof(int));
    
    // 需求表
    HashMap need;
    initHashMap(&need);
    for (int i = 0; i < n; i++) {
        (*getOrInsert(&need, words[i]))++;
    }
    
    // 遍历起点：对齐方式
    for (int offset = 0; offset < k; offset++) {
        int left = offset;
        HashMap window;
        initHashMap(&window);
        int count = 0; // 窗口内匹配的单词数
        
        // 枚举每个单词起点
        for (int right = offset; right + k <= m; right += k) {
            char w[MAX_WORD_LEN + 1];
            strncpy(w, s + right, k);
            w[k] = '\0';
            
            // 窗口右扩
            if (contains(&need, w)) {
                (*getOrInsert(&window, w))++;
                count++;
                
                // 如果某个单词超频，收缩窗口
                while (*get(&window, w) > *get(&need, w)) {
                    char lw[MAX_WORD_LEN + 1];
                    strncpy(lw, s + left, k);
                    lw[k] = '\0';
                    (*get(&window, lw))--;
                    left += k;
                    count--;
                }
                
                // 如果窗口刚好包含n个单词
                if (count == n) {
                    ans[(*returnSize)++] = left;
                    // 再往前收缩一步，准备找下一个
                    char lw[MAX_WORD_LEN + 1];
                    strncpy(lw, s + left, k);
                    lw[k] = '\0';
                    (*get(&window, lw))--;
                    left += k;
                    count--;
                }
            } else {
                // 不在need中，清空窗口
                clearHashMap(&window);
                count = 0;
                left = right + k;
            }
        }
    }
    
    if (*returnSize == 0) {
        free(ans);
        return NULL;
    }
    
    return ans;
}

int main() {
    char s[] = "barfoothefoobarman";
    char* words[] = {"foo", "bar"};
    int wordsSize = 2;
    int returnSize;
    
    int* result = findSubstring(s, words, wordsSize, &returnSize);
    
    printf("Result: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    if (result) {
        free(result);
    }
    
    return 0;
}