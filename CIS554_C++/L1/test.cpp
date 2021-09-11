#include <iostream>

int main()
{
    enum test {one = 'a', two , five, six };

    test k = two;

    std::cout << k << " " << six << std::endl;
}