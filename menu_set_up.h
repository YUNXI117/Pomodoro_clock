#pragma once
#include "menu.h"

/**
 * @brief Create and configure the main menu.
 *
 * The main menu is the entry point of the application.
 * It provides options to start the Pomodoro timer,
 * open the settings menu, or quit the application.
 *
 * @param main_menu Menu instance to be initialized.
 */
void create_main_menu(Menu &main_menu);

/**
 * @brief Create and configure the timer menu.
 *
 * The timer menu allows the user to start the Pomodoro timer
 * or navigate back to the main menu.
 *
 * @param timer_menu Menu instance to be initialized.
 */
void create_timer_menu(Menu &timer_menu);

/**
 * @brief Create and configure the settings menu.
 *
 * The settings menu provides access to all timer configuration
 * options, including study and break timers.
 *
 * @param settings_menu Menu instance to be initialized.
 */
void create_settings_menu(Menu &settings_menu);

/**
 * @brief Create and configure the study timer settings menu.
 *
 * This menu allows the user to modify study-related settings,
 * such as total study time and Pomodoro study duration.
 *
 * @param study_timer_menu Menu instance to be initialized.
 */
void create_study_timer_menu(Menu &study_timer_menu);

/**
 * @brief Create and configure the break timer settings menu.
 *
 * This menu allows the user to modify break-related settings,
 * such as total break time and Pomodoro break duration.
 *
 * @param break_timer_menu Menu instance to be initialized.
 */
void create_break_timer_menu(Menu &break_timer_menu);

/**
 * @brief Create the total study time configuration menu.
 *
 * This menu represents a dedicated page for adjusting
 * the total study time value. Input handling and navigation
 * logic are managed elsewhere.
 *
 * @param total_study_time_menu Menu instance to be initialized.
 */
void create_total_study_time_menu(Menu &total_study_time_menu);

/**
 * @brief Create the total break time configuration menu.
 *
 * This menu represents a dedicated page for adjusting
 * the total break time value. Input handling and navigation
 * logic are managed elsewhere.
 *
 * @param total_break_time_menu Menu instance to be initialized.
 */
void create_total_break_time_menu(Menu &total_break_time_menu);
