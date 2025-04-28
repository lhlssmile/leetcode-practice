#include <vector>
#include <string>
#include <iostream>
using namespace std;
class ordered_stream_1656 {
public:
    vector<string> stream;
    int ptr = 1;

    ordered_stream_1656(int n) : stream(n + 1){};
    vector<string> insert(int idKey,string value) {
        stream[idKey] = move(value);
        int start = ptr;
        while(ptr < stream.size() && !stream[ptr].empty()) {
            ++ptr;
        }
        return {stream.begin() + start,stream.begin() + ptr};
    }
};

int main() {
    auto ps = new ordered_stream_1656(5);
    auto result1 = ps->insert(3,"ccccc");
    auto result2 = ps->insert(1,"aaaaa");
    auto result3 = ps->insert(2,"bbbbb");
    auto result4 = ps->insert(5,"eeeee");
    auto result5 = ps->insert(4,"ddddd");
    // 输出结果
    auto printResult = [](const vector<string>& res) {
        cout << "[";
        for (size_t i = 0; i < res.size(); ++i) {
            cout << "\"" << res[i] << "\"";
            if (i < res.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    };

    cout << "Result of insert(3, \"cc\"): ";
    printResult(result1);

    cout << "Result of insert(1, \"aa\"): ";
    printResult(result2);

    cout << "Result of insert(2, \"bb\"): ";
    printResult(result3);

    cout << "Result of insert(5, \"ee\"): ";
    printResult(result4);

    cout << "Result of insert(4, \"dd\"): ";
    printResult(result5);

    return 0;
}
