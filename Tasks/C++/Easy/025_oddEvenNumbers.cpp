#include <iostream>
#include <cassert>
#include <vector>

//четный и нечетные числы
//123,34,45,3 == false;
//2,4,6,8 == true;
//2,4,5,8 == false;


bool odd(std::vector<int> vec) {
    if(vec.empty()) return false;
    int n1 = 0;
    int n2 = 0;
    for(auto i : vec) {
        if(i % 2 != 0) n1++;
        else n2++;
    }
    return (n1 == 0) || (n2 == 0);
}

void tester() {
    assert(odd(std::vector{1,2,-3}) == false);
    assert(odd(std::vector{7,11,7}) == true);
    assert(odd(std::vector{6,-2,0}) == true);
    assert(odd(std::vector{3,4,5,4,3,2}) == false);
    std::cout << "OK" << std::endl;

}



int main() {
    tester();
}