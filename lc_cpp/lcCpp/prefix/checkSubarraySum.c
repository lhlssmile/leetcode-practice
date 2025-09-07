#include <stdbool.h>
#include <stdlib.h>

#define HASH_SIZE 1000

typedef struct {
    int key;
    int value;
    bool used;
} HashEntry;

typedef struct {
    HashEntry entries[HASH_SIZE];
} HashMap;

int hash(int key) {
    return ((key % HASH_SIZE) + HASH_SIZE) % HASH_SIZE;
}

void put(HashMap* map, int key, int value) {
    int index = hash(key);
    while (map->entries[index].used && map->entries[index].key != key) {
        index = (index + 1) % HASH_SIZE;
    }
    map->entries[index].key = key;
    map->entries[index].value = value;
    map->entries[index].used = true;
}

bool get(HashMap* map, int key, int* value) {
    int index = hash(key);
    while (map->entries[index].used) {
        if (map->entries[index].key == key) {
            *value = map->entries[index].value;
            return true;
        }
        index = (index + 1) % HASH_SIZE;
    }
    return false;
}

bool checkSubarraySum(int* nums, int numsSize, int k) {
    HashMap mod_map = {0};
    put(&mod_map, 0, -1);
    int prefix_s = 0;
    
    for (int i = 0; i < numsSize; i++) {
        prefix_s += nums[i];
        
        int mod = ((prefix_s % k) + k) % k;
        
        int prev_index;
        if (get(&mod_map, mod, &prev_index)) {
            if (i - prev_index >= 2) {
                return true;
            }
        } else {
            put(&mod_map, mod, i);
        }
    }
    return false;
}