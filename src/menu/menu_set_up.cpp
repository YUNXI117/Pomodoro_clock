#include "pomodoro/menu/menu_set_up.h"
#include "pomodoro/menu/menu_action.h"

void create_main_menu(Menu &main_menu)
{
    main_menu.name = "main_menu";
    add_option(main_menu, "Enter Pomodoro Timer", MenuAction::ACTION_GOTO_TIMER);
    add_option(main_menu, "Settings", MenuAction::ACTION_GOTO_SETTINGS);
    add_option(main_menu, "Quit", MenuAction::ACTION_QUIT);
}

void create_timer_menu(Menu &timer_menu)
{
    timer_menu.name = "timer_menu";
    add_option(timer_menu, "Start Timer", MenuAction::ACTION_START_TIMER);
    add_option(timer_menu, "Back", MenuAction::ACTION_BACK);
}

void create_settings_menu(Menu &settings_menu)
{
    settings_menu.name = "settings_menu";
    add_option(settings_menu, "Study Timer Settings", MenuAction::ACTION_GOTO_STUDY_TIMER);
    add_option(settings_menu, "Break Timer Settings", MenuAction::ACTION_GOTO_BREAK_TIMER);
    add_option(settings_menu, "Back", MenuAction::ACTION_BACK);
}

void create_study_timer_menu(Menu &study_timer_menu)
{
    study_timer_menu.name = "study_timer_menu";
    add_option(study_timer_menu, "Set Total Study Time", MenuAction::ACTION_SET_TOTAL_STUDY);
    add_option(study_timer_menu, "Set Pomodoro Study Time", MenuAction::ACTION_SET_POMODORO_STUDY);
    add_option(study_timer_menu, "Back", MenuAction::ACTION_BACK);
}

void create_break_timer_menu(Menu &break_timer_menu)
{
    break_timer_menu.name = "break_timer_menu";
    add_option(break_timer_menu, "Set Total Break Time", MenuAction::ACTION_SET_TOTAL_BREAK);
    add_option(break_timer_menu, "Set Pomodoro Break Time", MenuAction::ACTION_SET_POMODORO_BREAK);
    add_option(break_timer_menu, "Back", MenuAction::ACTION_BACK);
}

void create_total_study_time_menu(Menu &menu)
{
    menu.name = "total_study_time_menu";
    add_option(menu, "Back", MenuAction::ACTION_BACK);
}

void create_total_break_time_menu(Menu &menu)
{
    menu.name = "total_break_time_menu";
    add_option(menu, "Back", MenuAction::ACTION_BACK);
}
