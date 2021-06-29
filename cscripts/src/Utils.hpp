#pragma once

#include "array"

enum CollLayers
{
    WORLD = 1,
    UNITS = 2,
};

template <typename... T> static constexpr CollLayers GetLayers(T... layers)
{
    constexpr auto size = (sizeof(T) + ...);
    std::array<CollLayers, size> arr{layers...};

    int64_t result = 0;

    for (auto layer : arr)
    {
        result |= layer;
    }

    return (CollLayers)result;
}