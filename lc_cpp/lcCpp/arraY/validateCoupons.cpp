//
// Created by 24276 on 2025/7/6.
//
/**
 * 给你三个长度为 n 的数组，分别描述 n 个优惠券的属性：code、businessLine 和 isActive。其中，第 i 个优惠券具有以下属性：

code[i]：一个 字符串，表示优惠券的标识符。
businessLine[i]：一个 字符串，表示优惠券所属的业务类别。
isActive[i]：一个 布尔值，表示优惠券是否当前有效。
当以下所有条件都满足时，优惠券被认为是 有效的 ：

code[i] 不能为空，并且仅由字母数字字符（a-z、A-Z、0-9）和下划线（_）组成。
businessLine[i] 必须是以下四个类别之一："electronics"、"grocery"、"pharmacy"、"restaurant"。
isActive[i] 为 true 。
返回所有 有效优惠券的标识符 组成的数组，按照以下规则排序：

先按照其 businessLine 的顺序排序："electronics"、"grocery"、"pharmacy"、"restaurant"。
在每个类别内，再按照 标识符的字典序（升序）排序。
 

示例 1：

输入： code = ["SAVE20","","PHARMA5","SAVE@20"], businessLine = ["restaurant","grocery","pharmacy","restaurant"], isActive = [true,true,true,true]

输出： ["PHARMA5","SAVE20"]

解释：

第一个优惠券有效。
第二个优惠券的标识符为空（无效）。
第三个优惠券有效。
第四个优惠券的标识符包含特殊字符 @（无效）。
示例 2：

输入： code = ["GROCERY15","ELECTRONICS_50","DISCOUNT10"], businessLine = ["grocery","electronics","invalid"], isActive = [false,true,true]

输出： ["ELECTRONICS_50"]

解释：

第一个优惠券无效，因为它未激活。
第二个优惠券有效。
第三个优惠券无效，因为其业务类别无效。
 

提示：

n == code.length == businessLine.length == isActive.length
1 <= n <= 100
0 <= code[i].length, businessLine[i].length <= 100
code[i] 和 businessLine[i] 由可打印的 ASCII 字符组成。
isActive[i] 的值为 true 或 false。
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
using namespace std;

class validate_coupons{
public:
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine,
        vector<bool>& isActive) {
        int n = code.size();
        vector<pair<string, string>> validCoupons;  // {code, businessLine}
        
        const unordered_set<string> service_category = {"electronics", "grocery",
            "pharmacy", "restaurant"};
        
        // 业务类别优先级映射
        const unordered_map<string, int> categoryOrder = {
            {"electronics", 0}, {"grocery", 1}, {"pharmacy", 2}, {"restaurant", 3}
        };
        
        for(int i = 0; i < n; i++) {
            if (!code[i].empty()
                && isValidCode(code[i])  // 验证字符串只包含字母数字和下划线
                && isActive[i]  // 直接判断bool值
                && service_category.find(businessLine[i]) != service_category.end()) {
                validCoupons.push_back({code[i], businessLine[i]});
            }
        }
        
        // 按要求排序：先按业务类别，再按字典序
        sort(validCoupons.begin(), validCoupons.end(), 
            [&categoryOrder](const pair<string, string>& a, const pair<string, string>& b) {
                int orderA = categoryOrder.at(a.second);
                int orderB = categoryOrder.at(b.second);
                if (orderA != orderB) {
                    return orderA < orderB;  // 按业务类别顺序
                }
                return a.first < b.first;  // 同类别内按字典序
            });
        
        vector<string> res;
        for (const auto& coupon : validCoupons) {
            res.push_back(coupon.first);
        }
        
        return res;
    }
    
private:
    // 验证字符串只包含字母数字和下划线
    bool isValidCode(const string& code) {
        for (char c : code) {
            if (!isalnum(c) && c != '_') {
                return false;
            }
        }
        return true;
    }
};

int main() {
    vector<string> code = {"SAVE20","","PHARMA5","SAVE@20"};
    vector<string> businessLine = {"restaurant","grocery","pharmacy","restaurant"};
    vector<bool> isActive = {true,true,true,true};

    validate_coupons ps;
    auto res = ps.validateCoupons(code, businessLine, isActive);
    for (const auto& couponCode : res) {
        cout << couponCode << " ";
    }
    cout << endl;
    
    return 0;
}