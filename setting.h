#pragma once
#include "timer_config.h"

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
