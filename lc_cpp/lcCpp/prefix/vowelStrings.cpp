//
// Created by 24276 on 2025/8/8.
//
#include <vector>
#include <string>
class vowel_strings {
public:
    std::vector<int> vowelStrings (std::vector<std::string>& words, std::vector<std::vector<int>>& queries) {
        int n = words.size();
        std::vector<int> prefix(n + 1, 0);
        auto isVowel = [](char c ) {
            return std::string("aeiou").find(c) != std::string::npos;
        };
        auto isVowelWord = [&](const std::string& word) {
            return isVowel(word.front()) && isVowel(word.back());
        };
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + (isVowelWord(words[i]) ? 1 : 0);
        }
        std::vector<int> ans;

        for (auto& q :queries) {
            ans.push_back(prefix[q[1] + 1] - prefix[q[0]]);
        }
        return ans;
    }
};

int main() {
    return 0;
}
