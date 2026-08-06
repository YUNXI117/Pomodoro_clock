#pragma once

/**
 * @brief Represents all possible user actions in the menu system.
 *
 * MenuAction is used as the communication layer between:
 * - menu input handling
 * - menu navigation (state transitions)
 * - application logic (timer configuration, exit, etc.)
 *
 * Each value corresponds to a specific user intention selected
 * from a menu option.
 */
enum class MenuAction
{
    /**
     * @brief No action selected.
     *
     * Used when the user has not made any valid input.
     */
    ACTION_NONE,

    // ===== Main Menu Actions =====

    /**
     * @brief Navigate to the timer menu.
     */
    ACTION_GOTO_TIMER,

    /**
     * @brief Navigate to the settings menu.
     */
    ACTION_GOTO_SETTINGS,

    /**
     * @brief Exit the application.
     */
    ACTION_QUIT,

    // ===== Timer Menu Actions =====

    /**
     * @brief Start the Pomodoro timer.
     */
    ACTION_START_TIMER,

    /**
     * @brief Return to the previous menu.
     */
    ACTION_BACK,

    // ===== Settings Menu Actions =====

    /**
     * @brief Navigate to study timer settings.
     */
    ACTION_GOTO_STUDY_TIMER,

    /**
     * @brief Navigate to break timer settings.
     */
    ACTION_GOTO_BREAK_TIMER,

    // ===== Study / Break Configuration Actions =====

    /**
     * @brief Set the total study time.
     */
    ACTION_SET_TOTAL_STUDY,

    /**
     * @brief Set the Pomodoro study duration.
     */
    ACTION_SET_POMODORO_STUDY,

    /**
     * @brief Set the total break time.
     */
    ACTION_SET_TOTAL_BREAK,

    /**
     * @brief Set the Pomodoro break duration.
     */
    ACTION_SET_POMODORO_BREAK
};
