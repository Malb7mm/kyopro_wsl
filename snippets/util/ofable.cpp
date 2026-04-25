template <typename T>
struct ofable {
    T val;
    bool is_overflow;

    constexpr ofable() : val(0), is_overflow(false) {}
    constexpr ofable(T v) : val(v), is_overflow(false) {}
    constexpr ofable(T v, bool o) : val(o ? 0 : v), is_overflow(o) {}
    constexpr explicit operator T() const { return val; }

    constexpr ofable<T>& operator+=(const ofable<T>& rhs) {
        if (is_overflow || rhs.is_overflow) {
            is_overflow = true; val = 0;
        } else {
            if (__builtin_add_overflow(val, rhs.val, &val)) {
                val = 0; is_overflow = true;
            }
        }
        return *this;
    }
    constexpr ofable<T>& operator-=(const ofable<T>& rhs) {
        if (is_overflow || rhs.is_overflow) {
            is_overflow = true; val = 0;
        } else {
            if (__builtin_sub_overflow(val, rhs.val, &val)) {
                val = 0; is_overflow = true;
            }
        }
        return *this;
    }
    constexpr ofable<T>& operator*=(const ofable<T>& rhs) {
        if (is_overflow || rhs.is_overflow) {
            is_overflow = true; val = 0;
        } else {
            if (__builtin_mul_overflow(val, rhs.val, &val)) {
                val = 0; is_overflow = true;
            }
        }
        return *this;
    }
    constexpr ofable<T>& operator/=(const ofable<T>& rhs) {
        if (is_overflow || rhs.is_overflow) {
            is_overflow = true; val = 0;
            return *this;
        }
        if (val == std::numeric_limits<T>::min() && rhs.val == -1) {
            is_overflow = true; val = 0;
        } else {
            val /= rhs.val;
        }
        return *this;
    }
    constexpr ofable<T>& operator<<=(int shift) {
        if (is_overflow) return *this;
        if (shift < 0) {
            is_overflow = true; val = 0; return *this;
        }
        if (val == 0) return *this;

        T max_val = std::numeric_limits<T>::max();
        T min_val = std::numeric_limits<T>::min();

        if (shift >= std::numeric_limits<T>::digits + 1) {
             is_overflow = true; val = 0;
        } else {
            if (val > 0) {
                if (val > (max_val >> shift)) { is_overflow = true; val = 0; }
                else val <<= shift;
            } else {
                if (val < (min_val >> shift)) { is_overflow = true; val = 0; }
                else val <<= shift;
            }
        }
        return *this;
    }

    constexpr ofable<T>& operator>>=(int shift) {
        if (is_overflow) return *this;
        val >>= shift;
        return *this;
    }

    friend constexpr ofable<T> operator+(ofable<T> lhs, const ofable<T>& rhs) { return lhs += rhs; }
    friend constexpr ofable<T> operator-(ofable<T> lhs, const ofable<T>& rhs) { return lhs -= rhs; }
    friend constexpr ofable<T> operator*(ofable<T> lhs, const ofable<T>& rhs) { return lhs *= rhs; }
    friend constexpr ofable<T> operator/(ofable<T> lhs, const ofable<T>& rhs) { return lhs /= rhs; }
    friend constexpr ofable<T> operator<<(ofable<T> lhs, int shift) { return lhs <<= shift; }
    friend constexpr ofable<T> operator>>(ofable<T> lhs, int shift) { return lhs >>= shift; }

    friend constexpr ofable<T> operator+(ofable<T> lhs, T rhs) { return lhs += ofable<T>(rhs); }
    friend constexpr ofable<T> operator-(ofable<T> lhs, T rhs) { return lhs -= ofable<T>(rhs); }
    friend constexpr ofable<T> operator*(ofable<T> lhs, T rhs) { return lhs *= ofable<T>(rhs); }
    friend constexpr ofable<T> operator/(ofable<T> lhs, T rhs) { return lhs /= ofable<T>(rhs); }
    friend constexpr ofable<T> operator+(T lhs, const ofable<T>& rhs) { return ofable<T>(lhs) += rhs; }
    friend constexpr ofable<T> operator-(T lhs, const ofable<T>& rhs) { return ofable<T>(lhs) -= rhs; }
    friend constexpr ofable<T> operator*(T lhs, const ofable<T>& rhs) { return ofable<T>(lhs) *= rhs; }
    friend constexpr ofable<T> operator/(T lhs, const ofable<T>& rhs) { return ofable<T>(lhs) /= rhs; }

    friend constexpr bool operator==(const ofable<T>& lhs, const ofable<T>& rhs) {
        return lhs.val == rhs.val && lhs.is_overflow == rhs.is_overflow;
    }
    friend constexpr bool operator!=(const ofable<T>& lhs, const ofable<T>& rhs) { return !(lhs == rhs); }
    friend constexpr bool operator<(const ofable<T>& lhs, const ofable<T>& rhs) { return lhs.val < rhs.val; }
    friend constexpr bool operator>(const ofable<T>& lhs, const ofable<T>& rhs) { return lhs.val > rhs.val; }

    friend std::ostream& operator<<(std::ostream& os, const ofable<T>& v) {
        if (v.is_overflow) os << "Overflow";
        else os << v.val;
        return os;
    }
};
