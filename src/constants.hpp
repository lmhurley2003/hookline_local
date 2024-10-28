/**
 * @file constants.hpp
 *
 * Useful constants for use throughout the game.
 */

#pragma once

#include <glm/glm.hpp>
namespace hookline {

constexpr int default_window_width = 1080;
constexpr int default_window_height = 1080;
constexpr int minimum_window_width = 100;
constexpr int minimum_window_height = 100;
constexpr float fixed_dt = 1.0f / 60.0f;

// Physics
constexpr glm::vec2 min_velocity = {0.05, 0.05};
constexpr glm::vec2 max_velocity = {2.0, 2.0};
constexpr float g = 0.0f;
constexpr float drag = 2.0f;

}  // namespace hookline