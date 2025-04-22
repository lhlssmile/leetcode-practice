#include <queue>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;
class FoodRatings {
    using pis = pair<int, string>;

    std::unordered_map<std::string, std::pair<int, string>> food_map;
    unordered_map<string, priority_queue<pis, vector<pis>, greater<>>> cuisine_map;

public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        for (int i = 0; i < foods.size(); i++) {
            auto& food = foods[i];
            auto& cuisine = cuisines[i];
            int rating = ratings[i];
            food_map[food] = {rating, cuisine};
            cuisine_map[cuisine].emplace(-rating, food);
        }
    }

    void changeRating(string food, int newRating) {
        auto& [rating, cuisine] = food_map[food];
        // 直接添加新数据，后面 highestRated 再删除旧的
        cuisine_map[cuisine].emplace(-newRating, food);
        rating = newRating;
    }

    string highestRated(string cuisine) {
        auto& pq = cuisine_map[cuisine];
        // 堆顶的食物评分不等于其实际值
        while (-pq.top().first != food_map[pq.top().second].first) {
            pq.pop();
        }
        return pq.top().second;
    }
};

int main() {
    vector<string> foodName = {"kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"};
    vector<string> cuisines = {"korean", "japanese", "japanese", "greek", "japanese", "korean"};
    vector<int> ratings = {9, 12, 8, 15, 14, 7};
    auto foodRatings = new FoodRatings(foodName, cuisines, ratings);
    cout << foodRatings->highestRated("korean") << endl; // 返回 "kimchi"
    // "kimchi" 是分数最高的韩式料理，评分为 9 。
    cout << foodRatings->highestRated("japanese") << endl; // 返回 "ramen"
    // "ramen" 是分数最高的日式料理，评分为 14 。
    foodRatings->changeRating("sushi", 16); // "sushi" 现在评分变更为 16 。
    cout << foodRatings->highestRated("japanese") << endl; // 返回 "sushi"
    // "sushi" 是分数最高的日式料理，评分为 16 。
    foodRatings->changeRating("ramen", 16); // "ramen" 现在评分变更为 16 。
    cout << foodRatings->highestRated("japanese") << endl; // 返回 "ramen"
    // "sushi" 和 "ramen" 的评分都是 16 。
    // 但是，"ramen" 的字典序比 "sushi" 更小。
    return 0;
}
