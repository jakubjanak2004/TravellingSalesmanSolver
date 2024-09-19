//
// Created by Jakub Janak on 9/19/24.
//

#include "Helper.h"

#include <random>

int Helper::getRandomInteger(const int from, const int to) {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution intDist(from, to);

    return intDist(rng);
}