#define STRUCT_ID__ Dbl1
namespace mystd {
    namespace STRUCT_ID__ {
        template <class S, auto op, auto e>
        struct Doubling {
            // https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp からひったくってきた
            static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                          "op must work as S(S, S)");
            static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                          "e must work as S()");

            struct Result {
                int dest;
                S value;
            };
        
            std::size_t size_;
            std::vector<std::vector<int>> dest_; // 遷移先
            std::vector<std::vector<S>> value_; // 集約値
        
            template <typename T>
            explicit Doubling(const std::vector<T> dest) : Doubling(dest, std::vector<S>(dest.size(), e())) {}
        
            template <typename T>
            explicit Doubling(const std::vector<T>& dest, const std::vector<S>& value)
                : size_(dest.size()) {
                assert(dest.size() == value.size());
                dest_ = std::vector<std::vector<int>>(62, std::vector<int>(size_, 0));
                value_ = std::vector<std::vector<S>>(62, std::vector<S>(size_, e()));
                
                for (int i = 0; i < size_; i++) {
                    dest_[0][i] = static_cast<int>(dest[i]);
                    value_[0][i] = value[i];
                }
            
                for (int k = 1; k < 62; k++) {
                    for (int i = 0; i < size_; i++) {
                        dest_[k][i] = dest_[k - 1][dest_[k - 1][i]];
                        value_[k][i] = op(value_[k - 1][i], value_[k - 1][dest_[k - 1][i]]);
                    }
                }
            }
        
            Result query(int start, long long count) {
                int current = start;
                S answer = e();
            
                for (int k = 0; k < 62; k++) {
                    if (!((count >> k) & 1)) continue;
                    answer = op(answer, value_[k][current]);
                    current = dest_[k][current];
                }
            
                return {.dest = current, .value = answer};
            }
        };

        using S = ll;
        S op(S a, S b) {
            return max(a,b);
        }
        S e() {
            return -INFLL;
        }

        using It = Doubling<S,op,e>;
    }
}
namespace STRUCT_ID__ = mystd:: STRUCT_ID__ ;
#undef STRUCT_ID__
// Dbl1::It dbl(vector<Dbl1::S>(n,0),vector<Dbl1::S>(n,0));