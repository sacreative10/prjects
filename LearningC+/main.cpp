#include <iostream>
#include <vector>

#define LOG(inp) std::cout << inp << std::endl;

void print(int a) {
    LOG(a);
}


void functiona(const std::vector<int>& v, void(*func)(int)){
    for(int value : v){
        func(value);
    };
}



int main()
{

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    functiona(v, [](int a){ LOG(a); });



    LOG("Hello World!");
    return 0;
}