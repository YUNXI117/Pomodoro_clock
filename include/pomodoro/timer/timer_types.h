#pragma once 

/**
 * @brief Timer logical phase
 * 
 */
enum class TimerPhase
{
    STUDY,
    BREAK
};

/**
 * @brief Runtime state
 * 
 */
enum class TimerState
{
    IDLE,
    RUNNING,
    PAUSED
};

/**
 * @brief External events
 * 
 */
enum class TimerEvent
{
    START,
    PAUSE,
    TICK, // 1 second passed 
    TIME_UP
};

/**
 * @brief Stores the current state and data of the Pomodoro timer
 * 
 */
struct PomodoroTimer
{
    TimerPhase phase = TimerPhase::STUDY;
    TimerState state = TimerState::IDLE;

    int remaining_seconds = 0;
};

