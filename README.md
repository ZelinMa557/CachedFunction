### Introduction
This is a function template class. Each time this function is executed, it will first check whether the same parameter has been calculated. If it has been calculated, it will directly return the previously saved calculation result. Otherwise, it will be calculated first, and the parameters and results will be stored in the cache. This toy is based on template metaprogramming.  
**Notice:** This is just an experimental toy, don't take it seriously, don't use it in a production environment.  
### example
```
int sum(int a, int b) {
    return a+b;
}
int main() {
    auto cached_sum = make_cached(sum);
    cout<<cached_sum(1, 2)<<endl;   //cache miss
    cout<<cached_sum(2, 3)<<endl;   //cache miss
    cout<<cached_sum(1, 2)<<endl;   //cache hit
}
```
### Inspiration
Inspired by the programming language principles course at Zhejiang University. This course mentions that languages like Haskell, R, etc. use "lazy evaluation" to avoid repeated computations. So I wanted to explore whether the best programming language in human history - C++ - could implement a similar mechanism without adding new features to the complier.
