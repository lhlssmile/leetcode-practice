func compareVersion(version1 string, version2 string) int {
    p1, p2 := 0, 0
    n1, n2 := len(version1), len(version2)
    
    for p1 < n1 || p2 < n2 {
        num1 := 0
        
        for p1 < n1 && version1[p1] != '.' {
            num1 = num1*10 + int(version1[p1]-'0')
            p1++
        }
        p1++
        
        num2 := 0
        for p2 < n2 && version2[p2] != '.' {
            num2 = num2*10 + int(version2[p2]-'0')
            p2++
        }
        p2++
        
        if num1 < num2 {
            return -1
        } else if num1 > num2 {
            return 1
        }
    }
    return 0
}