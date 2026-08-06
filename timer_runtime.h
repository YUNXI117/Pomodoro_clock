#pragma once
#include "timer_config.h"
#include "timer_types.h"
#include "sound.h"
#include "timer_tracker.h"
#include "timer_background_ui.h"

/**
 * @brief Defines a single state transition for the Pomodoro timer FSM
 * This structure represents one transition rule in the table-driven
 * finite state machine. When the current phase, state, and event match,
 * the timer transitions to the specified next phase and state.
 * 
 * @param phase        The current timer phase
 * @param state        The current timer state
 * @param event        The event that triggers the transition
 * @param next_phase   The next phase after the transition
 * @param next_state   The next state after the transition
 * @param reset_time   Whether the timer should reset its remaining time
 */
struct TimerTransition
{
    TimerPhase phase;  
    TimerState state;  
    TimerEvent event;  

    TimerPhase next_phase; 
    TimerState next_state;  

    bool reset_time;       
};

/**
 * @brief Initialize the Pomodoro timer with default values
 *
 * @param timer   The Pomodoro timer to initialise
 * @param config  Configuration values used to set initial timer settings
 */
void init_pomodoro_timer(PomodoroTimer &timer, const TimerConfig &config);

/**
 * @brief Update the Pomodoro timer based on elapsed real time
 *
 * @param timer    The Pomodoro timer to update
 * @param config   Configuration values for timer durations
 * @param tracker  Tracks completed sessions and timer statistics
 *
 * @return true if the timer reaches zero and triggers a TIME_UP event
 */
bool update_pomodoro_timer(PomodoroTimer &timer,  const TimerConfig &config, TimerTracker &tracker);

/**
 * @brief Handle a timer event using the FSM transition table
 *
 * @param timer   The Pomodoro timer to update
 * @param config  Configuration values used during state transitions
 * @param event   The timer event to be processed
 */
void handle_timer_events(PomodoroTimer &timer, const TimerConfig &config, TimerEvent event);

/**
 * @brief Run the Pomodoro timer logic and manage related components
 *
 * @param timer    The Pomodoro timer being executed
 * @param config   Configuration values that control timer behaviour
 * @param sc       Sound controller used for audio feedback
 * @param tracker  Tracks timer progress and completed sessions
 * @param bg       Background draw fill in the timer page
 * @param vis      SoundVisualizer to store the data relate to the sound visualizer
 */
void run_pomodoro_timer(PomodoroTimer &timer, TimerConfig &config, SoundControl &sc, TimerTracker &tracker, TimerBackground &bg, SoundVisualizer &vis);
