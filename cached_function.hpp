#include <functional>
#include <unordered_map>
#include <iostream>

namespace HashList {
template <class T>
inline void hash_combine(std::size_t& seed, T const& v)
{
    // combine hash algorithm from boost library 
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

void hash_list_impl(size_t& seed) {}

template <class T, class ...Args>
void hash_list_impl(size_t& seed,  T head, Args... rest)
{
    hash_combine(seed, head);
    hash_list_impl(seed, rest...);
}

template<typename ...Args>
size_t hash_list(Args... args)
{
    size_t seed = 0;
    hash_list_impl(seed, args...);
    return seed;
}
}

template <typename T>
struct FuncTypes;

template<typename _ReturnType, typename ..._Args>
struct FuncTypes<_ReturnType(_Args...)>
{
    static const std::size_t ArgCount = sizeof...(_Args);
    using ReturnType = _ReturnType;
};

template<typename F>
class CachedFunction 
{
    using type = FuncTypes<F>;
    using ReturnType = typename type::ReturnType;
public:
    CachedFunction(F fun) : fun_(fun) {}

    template<typename ...Args>
    ReturnType operator()(Args... args) {
        size_t key = HashList::hash_list(args...);
        if (cache_.find(key) == cache_.end()) {
            std::cout<<"cache miss!"<<std::endl;
            cache_[key] = fun_(args...);
        }
        else {
            std::cout<<"cache hit!"<<std::endl;
        }
        return cache_[key];
    }
private:
    std::unordered_map<size_t, ReturnType> cache_ = {};
    std::function<F> fun_;
};

#define make_cached(fun) CachedFunction<decltype(fun)>(fun)