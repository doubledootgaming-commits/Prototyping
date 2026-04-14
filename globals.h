#ifndef GLOBALS
#define GLOBALS

#include <format>
#include <print>
#include <expected>

#include <cstdlib>
#include <iostream>
#include <cassert>

#include <string>
#include <vector>
#include <list>

#include "SDL3/SDL.h"
#include "vulkan/vulkan.h"

inline SDL_FColor blue{ 0.0f, 0.2f, 0.4f, 1.0f };

struct Vector2 {
	float x{}, y{};
};
struct Vector3 {
	float x{}, y{}, z{};
};
struct Vector4 {
	float x{}, y{}, z{}, a{};
};

template<>
struct std::formatter<Vector2> : std::formatter<std::string> {
	auto format(const Vector2& v, format_context& ctx) const {
		return std::formatter<std::string>::format(std::format("{}, {}", v.x, v.y), ctx);
	}
};
#endif