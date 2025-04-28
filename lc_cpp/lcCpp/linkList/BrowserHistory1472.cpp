#include <string>
#include <stack>
#include <iostream>
#include <vector>
using namespace std;
class browser_history1472 {
public:
    std::stack<string> backStack;
    std::stack<string> forwardStack;
    string current;
    browser_history1472(string homepage) {
        current = homepage;
    }
    void visit(string url) {
        backStack.push(current);
        current = url;
        while (!forwardStack.empty()) {
            forwardStack.pop();
        }
    }
    string back(int steps) {
        while(steps --> 0 && !backStack.empty()) {
            forwardStack.push(current);
            current = backStack.top();
            backStack.pop();
        }
        return current;
    }
    string forward(int steps) {
        while(steps --> 0 && !forwardStack.empty()) {
            backStack.push(current);
            current = forwardStack.top();
            forwardStack.pop();
        }
        return current;
    }




};
class browserHistory {
    //用数组模拟栈?
    vector<string> history;
    int current = 0;
public:
    browserHistory(string homepage) : history{homepage} {};
    void visit(string url) {
        current++;
        history.resize(current);
        history.push_back(url);
    }
    string back(int steps) {
        current = max(current - steps,0);
        return history[current];
    }
    string forward(int steps) {
        current = min(current + steps,(int) history.size() - 1);
        return history[current];
    }
};
int main() {
    auto browserHistory = new browser_history1472("leetcode.com");
    browserHistory->visit("google.com");       // 你原本在浏览 "leetcode.com" 。访问 "google.com"
    browserHistory->visit("facebook.com");     // 你原本在浏览 "google.com" 。访问 "facebook.com"
    browserHistory->visit("youtube.com");      // 你原本在浏览 "facebook.com" 。访问 "youtube.com"
    cout << browserHistory->back(1) << endl;                   // 你原本在浏览 "youtube.com" ，后退到 "facebook.com" 并返回 "facebook.com"
    cout << browserHistory->back(1) << endl;                   // 你原本在浏览 "facebook.com" ，后退到 "google.com" 并返回 "google.com"
    cout << browserHistory->forward(1) << endl;                // 你原本在浏览 "google.com" ，前进到 "facebook.com" 并返回 "facebook.com"
    browserHistory->visit("linkedin.com");     // 你原本在浏览 "facebook.com" 。 访问 "linkedin.com"
    cout << browserHistory->forward(2) << endl;                // 你原本在浏览 "linkedin.com" ，你无法前进任何步数。
    cout << browserHistory->back(2) << endl;                   // 你原本在浏览 "linkedin.com" ，后退两步依次先到 "facebook.com" ，然后到 "google.com" ，并返回 "google.com"
    cout << browserHistory->back(7) << endl;
    return 0;
}

