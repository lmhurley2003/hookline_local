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
constexpr float fixed_dt = 1.0f / 120.0f;

// Physics
constexpr glm::vec2 min_velocity = {0.05, 0.05};
constexpr glm::vec2 max_velocity = {5.0, 5.0};
constexpr glm::vec2 player_movement_force = {30.0f, 15.0f};

constexpr float g = -9.8f;
constexpr float drag = 2.0f;

// Grapple
constexpr float grapple_max_length = 15.0f;
constexpr float grapple_pull_force = 15.0f;
constexpr float grapple_deactive_dist = 0.01f;

}  // namespace hookline