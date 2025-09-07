function compareVersion(version1, version2) {
    let p1 = 0, p2 = 0;
    const n1 = version1.length, n2 = version2.length;
    
    while (p1 < n1 || p2 < n2) {
        let num1 = 0;
        
        while (p1 < n1 && version1[p1] !== '.') {
            num1 = num1 * 10 + parseInt(version1[p1]);
            p1++;
        }
        p1++;
        
        let num2 = 0;
        while (p2 < n2 && version2[p2] !== '.') {
            num2 = num2 * 10 + parseInt(version2[p2]);
            p2++;
        }
        p2++;
        
        if (num1 < num2) {
            return -1;
        } else if (num1 > num2) {
            return 1;
        }
    }
    return 0;
}