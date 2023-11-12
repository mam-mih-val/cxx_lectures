#ifndef _GAME_CONSTANTS_H_
#define _GAME_CONSTANTS_H_

#include <array>

using stats_type = int;
using pos_type = std::array<int, 2>;

constexpr stats_type X_MIN = 0;
constexpr stats_type X_MAX = 80;
constexpr stats_type Y_MIN = 0;
constexpr stats_type Y_MAX = 20;

#endif // _GAME_CONSTANTS_H_