#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
struct food {
    //这种方式创建对象太多了       内存超限
    string foodName;
    string cuisine;
    int rating;
    food(string foodName,string cuisine,int rating):foodName(std::move(foodName))
    ,cuisine(std::move(cuisine)),rating(rating){}
};
class food_ratings2353 {
public:
    // unordered_map<string,vector<pair<string,int>>> map;
    // unordered_map<string,int> foodToRating;
    // pmr::unordered_map<string,string> foodToCuisine;
    // food_ratings2353(vector<string>& foods,vector<string>& cuisines,vector<int>& ratings) {
    //     int n = foods.size();
    //     for(int i = 0;i < n;++i) {
    //         map[cuisines[i]].push_back({foods[i],ratings[i]});
    //         foodToRating[foods[i]] = ratings[i];
    //         foodToCuisine[foods[i]] = cuisines[i];
    //     }
    // }
    // //change rating according to name;
    // void changeRating(string food,int newRating) {
    //     //硬查?
    //     foodToRating[food] = newRating;
    //     string cuisine = foodToCuisine[food];
    //     for(auto& item : map[cuisine]) {
    //         if(item.first == food) {
    //             item.second = newRating;
    //             break;
    //         }
    //     }
    //     for(auto& [food,rating] : map[cuisine]) {
    //
    //     }
    // }
    // //根据烹饪方式返回foods name
    // string highestRated(string cuisine) {
    //     auto& foods = map[cuisine];
    //     std::sort(foods.begin(),foods.end(),[](const pair<string,int>& a,const pair<string,int>& b) {
    //         if(a.second == b.second) {
    //             return a.first < b.first;
    //         }
    //         return a.second > b.second;
    //     });
    //     return foods[0].first;
    // }



    //1.有序集合 哈希表
    pmr::unordered_map<string,pair<int,string>> food_map;
    // pmr::unordered_map<string, pmr::set<pair<int,string>>> cuisine_map;

    //2.use heap
    using pis = pair<int,string>;
    pmr::unordered_map<string,priority_queue<pis,vector<pis>,greater<>>> cuisine_mapa;
    /**
     * key：string类型的cuisine，表示某种烹饪方式（例如："japanese", "korean"）
     * value：一个priority_queue<pis, vector<pis>, greater<>>，
     * 是一个优先队列，用来存储与某个cuisine相关的食物和它们的评分
     *
     * priority_queue是一个按照一定顺序（优先级）存储元素的容器，在这里用来根据食物评分的高低排序。
     * pis是pair<int, string>，表示一个食物和它的评分：pair<评分, 食物名>。
     * greater<>是用来指定优先队列的排序规则。greater<>表示按升序排列，即评分低的优先出队（因为pair的第一个值是评分）。
     */

    food_ratings2353(vector<string>& foods,vector<string>& cuisines,vector<int> ratings) {
        for(int i = 0; i < foods.size(); ++i) {
            auto& food = foods[i];
            auto& cuisine = cuisines[i];
            int rating = ratings[i];
            food_map[food] = {rating,cuisine};
            //取符号 保证rating相同的同时 字典序更小的food在前边
            cuisine_mapa[cuisine].emplace(-rating,food);
        }
    }
    // void changeRating(string food,int newRating) {
    //     auto& [rating,cuisine] = food_map[food];
    //     auto& st = cuisine_map[cuisine];
    //     st.erase({-rating,food});       //移除旧数据
    //     st.emplace(-newRating,food);            //添加新数据
    //     rating = newRating;
    // }
    //懒删除堆
    void changeRatingUseHeap(string food,int newRating) {
        auto& [rating,cuisine] = food_map[food];
        //直接添加新数据 后面找最高评分在删除旧数据
        cuisine_mapa[cuisine].emplace(-newRating,food);
        rating = newRating;
    }
    //
    // string highestRated(string cuisine) {
    //     return cuisine_map[cuisine].begin()->second;
    // }

    string highestRatedUseHeap(string cuisine) {
        auto& pq = cuisine_mapa[cuisine];
        //堆顶的食物评分不等于实际值
        while(!pq.top().first != food_map[pq.top().second].first) {
            pq.top();
        }
        return pq.top().second;
    }

};

int main() {
    vector<string> foodName = {"kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"};
    vector<string> cuisines = {"korean", "japanese", "japanese", "greek", "japanese", "korean"};
    vector<int> ratings = {9, 12, 8, 15, 14, 7};
    food_ratings2353 foodRatings(foodName, cuisines, ratings);

    cout << foodRatings.highestRatedUseHeap("korean") << endl; // 输出 "kimchi"
    cout << foodRatings.highestRatedUseHeap("japanese") << endl; // 输出 "ramen"

    foodRatings.changeRatingUseHeap("sushi", 16);
    cout << foodRatings.highestRatedUseHeap("japanese") << endl; // 输出 "sushi"

    foodRatings.changeRatingUseHeap("ramen", 16);
    cout << foodRatings.highestRatedUseHeap("japanese") << endl; // 输出 "ramen"

    return 0;
}
