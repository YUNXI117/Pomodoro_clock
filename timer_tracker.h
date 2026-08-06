#pragma once 
#include "timer_types.h"
#include "timer_config.h"

/**
 * @brief Tracks elapsed time and limit states for the Pomodoro timer
 *
 * This structure stores accumulated study and break time,
 * as well as flags used to indicate when time limits are reached
 * and when related popup notifications should be shown. 
 * Also, track the times the user be interrupted.
 */
struct TimerTracker
{
    int study_elapsed;// Total elapsed study time in seconds
    int break_elapsed; // Total elapsed break time in seconds

    bool study_limit_reached; // Indicates whether the study time limit has been reached
    bool break_limit_reached; // Indicates whether the break time limit has been reached
    bool popoup_study_done;// Indicates whether the study completion popup has been shown
    bool popup_break_done; // Indicates whether the break completion popup has been shown

    int interruption_count; // Record the times the user be interrupted when studying
};

/**
 * @brief Initialise the timer tracker
 *
 * Sets initial elapsed times and resets all limit
 * and popup state flags.
 *
 * @param tracker  Timer tracker to initialise
 */
void init_timer_tracker(TimerTracker &tracker);

/**
 * @brief Update the timer tracker based on the current timer state
 *
 * Updates elapsed study or break time and checks
 * whether configured limits have been reached.
 *
 * @param tracker  Timer tracker to update
 * @param timer    Current Pomodoro timer
 * @param config   Configuration values used for time limits
 */
void update_timer_tracker(
    TimerTracker &tracker,
    const PomodoroTimer &timer,
    const TimerConfig &config);

/**
 * @brief Draw popup notifications related to timer progress
 *
 * Displays popup messages when study or break
 * sessions have been completed.
 *
 * @param tracker  Timer tracker containing popup state information
 */
void draw_tracker_popup(TimerTracker &tracker);

/**
 * @brief Draw a interruption button at the right coner of the window, when user clicked
 * the counter number would + 1, to record the user be interrupted when studying
 * 
 */
void draw_interruption_counter(const PomodoroTimer &timer, TimerTracker &tracker);
