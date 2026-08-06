#pragma once

/**
 * @brief Stores all configurable timer values for the Pomodoro application.
 *
 * TimerConfig acts as the central data structure for all time-related
 * settings, including study and break durations.
 *
 * All values are stored in minutes.
 */
struct TimerConfig
{
    int total_study_minutes;        // Total allowed study time (minutes)
    int pomodoro_study_minutes;     // Duration of a single Pomodoro study session (minutes)
    int total_break_minutes;        // Total allowed break time (minutes)
    int pomodoro_break_minutes;     // Duration of a single Pomodoro break session (minutes)
};

/**
 * @brief Initialize timer configuration with default values.
 *
 * This function sets the initial values for all timer-related
 * configuration fields used in the Pomodoro application.
 *
 * Default values:
 * - total study time       : 120 minutes
 * - Pomodoro study time   : 25 minutes
 * - total break time      : 30 minutes
 * - Pomodoro break time   : 5 minutes
 *
 * @param config Timer configuration structure to initialize.
 */
void init_timer_config(TimerConfig &config);
