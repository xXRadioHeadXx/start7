#ifndef GLOBAL_H
#define GLOBAL_H

#include <utility>

#define delayDisconnectStatus 20500

template<class T>
T const as_const(T&&t){return std::forward<T>(t);}

template<class T>
T const& as_const(T&t){return t;}

// 1010 -> 0101
// 1100 -> 1100
// 0001 -> 1000
//constexpr int G_bitsInByte = 8;
//template< class T, int bytes = sizeof( T ) >
//std::enable_if_t< std::is_integral_v< T >, T >
//ReverseBits( T number )
//{
//   int bits = bytes * G_bitsInByte;
//   T result = 0;
//   while( bits > 0 )
//   {
//      result |= ( number & 1 ) << ( bits - 1 );
//      number >>= 1;
//      --bits;
//   }

//   return result;
//}


#endif // GLOBAL_H
