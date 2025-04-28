#include <iostream>
enum Example{
    A,B,C       //the value of the first variable is 0,incrementing sequentially
};

//c++ constructor func
class Entity{
public:
    float x,y;
    //Java类似 同名构造函数 提供不同的参数
    Entity(){

    };
    Entity(float x,float y){
        this->x = x;
        this->y = y;
    }

    void init(float xx,float yy){
        this->x = xx;
        this->y = yy;
    }
    void print(){
        std::cout << x << "," << y << std::endl;
    }
};

int a = 0;
int main()
{
    Example value = B; // The type is an enum, so the assignment can only be among A, B, C

    if (value == B)
    {
        // Do something here
        std::cout << "B:" << B <<  std::endl;
    }
// default constructor

    Entity e(2.1f,2.0f);

//    e.init(2.0f,22.2f);
//  de constructor
    e.~Entity();
    std::cout << e.x << e.y << std::endl;
    e.print();
}