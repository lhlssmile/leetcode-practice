#include <stdio.h>
#include <string.h>
#include <ctype.h>   // islower, isupper, isdigit
#include <stdbool.h> // C99 提供 bool/true/false

bool strongPasswordCheckerII(const char *password) {
    int n = strlen(password);
    if (n < 8) return false;

    const char *special = "!@#$%^&*()-+";
    int mask = 0;

    for (int i = 0; i < n; i++) {
        char c = password[i];
        if (i > 0 && c == password[i - 1]) return false;

        if (islower((unsigned char)c)) {
            mask |= 1;  // 0001
        } else if (isupper((unsigned char)c)) {
            mask |= 2;  // 0010
        } else if (isdigit((unsigned char)c)) {
            mask |= 4;  // 0100
        } else if (strchr(special, c)) {
            mask |= 8;  // 1000
        }
    }

    return mask == 15; // 必须四个条件全满足
}

int main() {
    printf("%d\n", strongPasswordCheckerII("IloveLe3tcode!")); // 1
    printf("%d\n", strongPasswordCheckerII("Me+You--IsMyDream")); // 0
    printf("%d\n", strongPasswordCheckerII("1aB!1aB!")); // 1
    printf("%d\n", strongPasswordCheckerII("1234567")); // 0
    return 0;
}
