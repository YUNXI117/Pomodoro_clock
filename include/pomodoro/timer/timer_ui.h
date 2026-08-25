#pragma once
#include <string>

#include "pomodoro/timer/timer_types.h"

/**
 * @brief Get the today date and format it into YYYY:mm:dd
 * 
 * @return std::string the time that have been formatted.
 */
std::string get_today_date();

/**
 * @brief format the remaining seconds into MM:SS
 * 
 * @param total_seconds the promodoro's config time
 * @return std::string the time that have been formatted
 */
std::string format_time_mmss(int total_seconds);

/**
 * @brief Control the hint to tell the user the timer state (RUNNING / PAUSED / IDLE)
 * 
 * @param state The timers's state
 * @return std::string return the string Pause (SPAUSE) / Start (SPACE)
 */
std::string control_hint(TimerState state);

/**
 * @brief Draw and handle the Pomodoro timer UI.
 *
 * Responsibilities:
 * - Display remaining time in MM:SS format
 * - Display current control hint (Start / Pause)
 * - Handle SPACE key to toggle running state
 * - Handle ESC to exit timer view
 *
 * @param timer Pomodoro timer runtime state
 * @return true  Continue showing timer UI
 * @return false Exit timer UI (back to menu)
 */
bool draw_timer_ui(PomodoroTimer &timer);

