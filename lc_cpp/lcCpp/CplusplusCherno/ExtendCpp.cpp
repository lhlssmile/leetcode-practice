#include <iostream>

class Entity {
public:
    float x, y;

    void move(float xa, float ya) {
        x += xa;
        y += ya;
        std::cout << x << "," << y << std::endl;
    }
};

class Player : public Entity {
public:
    const char* Name;

    Player() {}

    Player(const char* name, float xa, float ya) {
        this->x = xa;  // 直接使用继承的 x 和 y
        this->y = ya;
        this->Name = name;
    }

    void printName() {
        std::cout << Name << std::endl;
    }
};

int main() {
    const char* name = "name";
    Player player(name, 2.0f, 2.0f);
    player.printName();
    float xa = 4.0f, ya = 4.2f;
    player.move(xa, ya);  // 输出应该是 6, 6.2
    return 0;
}