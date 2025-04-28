#include <string>
#include <format>
#include <iostream>

class convertDateSolution{
public:
    std::string convertDateToBinary(std::string date) {
        return std::format("{:b}-{:b}-{:b}",
                      stoi(date.substr(0, 4)),
                      stoi(date.substr(5, 2)),
                      stoi(date.substr(8, 2)));
    }

};

int main() {
    convertDateSolution p;
    std::cout << p.convertDateToBinary("2025-01-23") << std::endl;
    return 0;
}
