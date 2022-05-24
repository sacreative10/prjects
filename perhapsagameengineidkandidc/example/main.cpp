#include <iostream>

namespace gameengineidk
{
void log(char *message);
};

int main(int, char **)
{
    char *message = (char *)'c';
    gameengineidk::log(message);
    return 0;
}
