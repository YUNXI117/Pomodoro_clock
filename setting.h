#pragma once
#include <string>

#include "timer_config.h"

/**
 * @brief Display and update a time configuration value interactively.
 *
 * This function provides a generic UI page for modifying a time value.
 * The user can:
 * - Increase or decrease the value using arrow keys (+5 / -5)
 * - Type a numeric value and press Enter to confirm
 * - Press ESC to return to the previous menu
 *
 * The function runs in its own input loop and only returns
 * when the user exits the setting page.
 *
 * @param title        Title displayed at the top of the setting page.
 * @param value_minutes Reference to the time value being modified.
 * @param min_limit    Minimum allowed value (inclusive).
 * @param max_limit    Maximum allowed value (inclusive).
 */
static void update_time_value(
    const std::string &title,
    int &value_minutes,
    int min_limit,
    int max_limit);

/**
 * @brief Update the total study time configuration.
 *
 * Allows the user to modify the total study duration
 * within a predefined range.
 *
 * @param config Timer configuration structure
 */
void update_total_study_time(TimerConfig &config);

/**
 * @brief Update the Pomodoro study session duration.
 *
 * Allows the user to modify the duration of a single
 * Pomodoro study session.
 *
 * @param config Timer configuration structure.
 */
void update_pomodoro_study_time(TimerConfig &config);

/**
 * @brief Update the total break time configuration.
 *
 * Allows the user to modify the total break duration.
 *
 * @param config Timer configuration structure.
 */
void update_total_break_time(TimerConfig &config);

/**
 * @brief Update the Pomodoro break session duration.
 *
 * Allows the user to modify the duration of a single
 * Pomodoro break session.
 *
 * @param config Timer configuration structure.
 */
void update_pomodoro_break_time(TimerConfig &config);
