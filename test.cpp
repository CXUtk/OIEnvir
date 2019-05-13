template <typename T>
struct cmplx : public array<T, 2>,
               public add_ops<cmplx<T>, add_impl>,
               public fmt_ops<cmplx<T>, fmt_impl> {
    typedef array<T, 2> array_t;
    typedef add_ops<cmplx<T>, add_impl> add_ops_t;
    typedef fmt_ops<cmplx<T>, fmt_impl> fmt_ops_t;

    cmplx() : add_ops_t(*this), fmt_ops_t(*this) {}
    cmplx(const cmplx& c) : array_t(c), add_ops_t(*this), fmt_ops_t(*this) {}
    cmplx(initializer_list<T> l) : add_ops_t(*this), fmt_ops_t(*this) {
        copy_n(l.begin(), 2, this->begin());
    }
    cmplx& operator=(const cmplx& c) {
        array_t::operator=(c);
        return *this;
    }
};

template <typename T, size_t N>
struct vec : public array<T, N>,
             public add_ops<vec<T, N>, add_impl>,
             public fmt_ops<vec<T, N>, fmt_impl> {
    typedef array<T, N> array_t;
    typedef add_ops<vec<T, N>, add_impl> add_ops_t;
    typedef fmt_ops<vec<T, N>, fmt_impl> fmt_ops_t;

    vec() : add_ops_t(*this), fmt_ops_t(*this) {}
    vec(const vec& v) : array_t(v), add_ops_t(*this), fmt_ops_t(*this) {}
    vec(initializer_list<T> l) : add_ops_t(*this), fmt_ops_t(*this) {
        copy_n(l.begin(), N, this->begin());
    }
    vec& operator=(const vec& v) {
        array_t::operator=(v);
        return *this;
    }
};

template <typename T, size_t N, size_t M>
struct mat : public array<vec<T, N>, M>,
             public add_ops<mat<T, N, M>, add_impl>,
             public fmt_ops<mat<T, N, M>, fmt_impl> {
    typedef array<vec<T, N>, M> array_t;
    typedef add_ops<mat<T, N, M>, add_impl> add_ops_t;
    typedef fmt_ops<mat<T, N, M>, fmt_impl> fmt_ops_t;

    mat() : add_ops_t(*this), fmt_ops_t(*this) {}
    mat(const mat& m) : array_t(m), add_ops_t(*this), fmt_ops_t(*this) {}
    mat(initializer_list<vec<T, N>> l) : add_ops_t(*this), fmt_ops_t(*this) {
        copy_n(l.begin(), M, this->begin());
    }
    mat& operator=(const mat& m) {
        array_t::operator=(m);
        return *this;
    }
};

typedef cmplx<double> c;
typedef vec<double, 3> vec3;
typedef vec<c, 3> vec3c;
typedef mat<double, 3, 2> mat32;