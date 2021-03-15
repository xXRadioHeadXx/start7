#ifndef GLOBAL_H
#define GLOBAL_H

#include <utility>

#define delayDisconnectStatus 20500

template<class T>
T const as_const(T&&t){return std::forward<T>(t);}
template<class T>
T const& as_const(T&t){return t;}

#endif // GLOBAL_H
