//
// Created by 24276 on 2025/3/31.
//

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
class percentage_letter2278 {
public:
    int percentageLetter(string s,char letter) {
        return ranges::count(s,letter) * 100 / s.size();
        //
    }
};

int main() {
    percentage_letter2278 solution;
    string s = "foobar";
    char letter = 'o';
    cout << solution.percentageLetter(s,letter) << endl;
    return 0;
}
