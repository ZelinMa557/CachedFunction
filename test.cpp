#include "cached_function.hpp"
#include <iostream>
using namespace std;
int sum(int a, int b) {
    return a+b;
}
int main() {
    auto cached_sum = make_cached(sum);
    cout<<cached_sum(1, 2)<<endl;   //cache miss
    cout<<cached_sum(2, 3)<<endl;   //cache miss
    cout<<cached_sum(1, 2)<<endl;   //cache hit
}