// 双指针解法
pub fn compare_version(version1: String, version2: String) -> i32 {
    let (mut p1, mut p2) = (0, 0);
    let (n1, n2) = (version1.len(), version2.len());
    let (v1_bytes, v2_bytes) = (version1.as_bytes(), version2.as_bytes());
    
    while p1 < n1 || p2 < n2 {
        let mut num1 = 0;
        
        while p1 < n1 && v1_bytes[p1] != b'.' {
            num1 = num1 * 10 + (v1_bytes[p1] - b'0') as i32;
            p1 += 1;
        }
        p1 += 1;
        
        let mut num2 = 0;
        while p2 < n2 && v2_bytes[p2] != b'.' {
            num2 = num2 * 10 + (v2_bytes[p2] - b'0') as i32;
            p2 += 1;
        }
        p2 += 1;
        
        match num1.cmp(&num2) {
            std::cmp::Ordering::Less => return -1,
            std::cmp::Ordering::Greater => return 1,
            std::cmp::Ordering::Equal => continue,
        }
    }
    0
}

// 函数式编程解法
pub fn compare_version_functional(version1: String, version2: String) -> i32 {
    let parse_versions = |version: &str| -> Vec<i32> {
        version.split('.')
            .map(|s| s.parse::<i32>().unwrap_or(0))
            .collect()
    };
    
    let v1_parts = parse_versions(&version1);
    let v2_parts = parse_versions(&version2);
    
    let max_len = v1_parts.len().max(v2_parts.len());
    
    (0..max_len)
        .map(|i| {
            let num1 = v1_parts.get(i).unwrap_or(&0);
            let num2 = v2_parts.get(i).unwrap_or(&0);
            num1.cmp(num2)
        })
        .find(|&ord| ord != std::cmp::Ordering::Equal)
        .map(|ord| match ord {
            std::cmp::Ordering::Less => -1,
            std::cmp::Ordering::Greater => 1,
            std::cmp::Ordering::Equal => 0,
        })
        .unwrap_or(0)
}