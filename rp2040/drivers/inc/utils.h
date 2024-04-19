#ifndef UTILS_H
#define UTILS_H

#include <type_traits>

/***************************************************************************************
*    Title: Effective Modern C++ - Item 10
*    Author: Scott Meyers
*    Date: November 2014
*
***************************************************************************************/
template <typename E>
constexpr auto to_underlying(E e) noexcept
{
  return static_cast<std::underlying_type_t<E>>(e);
}

#endif //UTILS_H
