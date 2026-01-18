//https://qiita.com/hamamu/items/4d081751b69aa3bb3557#comment-09da436b204261f1624d
namespace mystd{
    template<class T> size_t HashCombine(const size_t seed,const T &v){
       return seed^(std::hash<T>()(v)+0x9e3779b9+(seed<<6)+(seed>>2));
    }
    template<typename T>
    struct hash{
        size_t operator()(const T& keyval) const noexcept {
            return std::hash<T>()(keyval);
        }
    };
    /* pair用 */
    template<class T,class S>
    struct hash<std::pair<T,S>>{
        size_t operator()(const std::pair<T,S> &keyval) const noexcept {
            return HashCombine(std::hash<T>()(keyval.first), keyval.second);
        }
    };
    /* vector用 */
    template<class T>
    struct hash<std::vector<T>>{
        size_t operator()(const std::vector<T> &keyval) const noexcept {
            size_t s=0;
            for (auto&& v: keyval) s=HashCombine(s,v);
            return s;
        }
    };
    /* tuple用 */
    template<int N>
    struct HashTupleCore{
        template<class Tuple> size_t operator()(const Tuple &keyval) const noexcept{
            size_t s=HashTupleCore<N-1>()(keyval);
            return HashCombine(s,std::get<N-1>(keyval));
        }
    };
    template <> struct HashTupleCore<0>{
        template<class Tuple> size_t operator()(const Tuple &keyval) const noexcept{ return 0; }
    };
    template<class... Args>
    struct hash<std::tuple<Args...>>{
        size_t operator()(const std::tuple<Args...> &keyval) const noexcept {
            return HashTupleCore<std::tuple_size<std::tuple<Args...>>::value>()(keyval);
        }
    };
    template<typename K, typename T>
    using unordered_map = std::unordered_map<K,T,hash<K>>;
    template<typename K>
    using unordered_set = std::unordered_set<K,hash<K>>;
}