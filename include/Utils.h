//
// Created by sQuAde on 10/7/2025.
//

#ifndef STRATEGYCPP_UTILS_H
#define STRATEGYCPP_UTILS_H


#include <cstdlib>
#include <ctime>

class Utils {
public:
    static inline void seed() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }
    static inline int rng(int minV, int maxV) {
        return minV + (std::rand() % (maxV - minV + 1));
    }

    static inline bool chance(int percent) {
        return rng(1, 100) <= percent;
    }
};


#endif //STRATEGYCPP_UTILS_H