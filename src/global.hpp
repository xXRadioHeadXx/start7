template<class T>
T const as_const(T&&t){return std::forward<T>(t);}
template<class T>
T const& as_const(T&t){return t;}