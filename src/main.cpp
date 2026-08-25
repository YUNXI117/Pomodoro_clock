#include "pomodoro/menu/menu.h"
#include "splashkit.h"
#include "pomodoro/menu/menu_set_up.h"
#include "pomodoro/timer/timer_config.h"
#include "pomodoro/timer/setting.h"
#include "pomodoro/timer/timer_runtime.h"
#include "pomodoro/timer/timer_ui.h"
#include "pomodoro/timer/timer_types.h"
#include "pomodoro/sound/sound.h"
#include "pomodoro/timer/timer_tracker.h"
#include "pomodoro/timer/timer_background_ui.h"
#include "pomodoro/sound/sound_visualizer.h"
#include "pomodoro/ui/ui.h"

/**
 * @brief Describes a valid transition between menus.
 * - from   : current menu
 * - action : user action selected from the menu
 * - to     : target menu after transition (nullptr means exit program)
 */
struct MenuTransition
{
    Menu *from;
    MenuAction action;
    Menu *to;
};

/** 
 * @brief: A container struct holding all menus used in the application.
 * This avoids declaring many Menu variables separately in main().
 */
struct ClockMenus
{
    Menu main_menu;
    Menu timer_menu;
    Menu settings_menu;
    Menu study_timer_menu;
    Menu break_timer_menu;
    Menu total_study_time_menu;
    Menu total_break_time_menu;
};

/**
 * @brief Apply a table-driven menu transition based on user action.
 *
 * This function searches the transition table for a matching
 * (current menu + action) pair. If found, it updates the current menu
 * pointer accordingly.
 *
 * @param current_menu Reference to the pointer of the current menu.
 *        This allows the function to update which menu is currently active.
 * @param action The action selected by the user.
 * @param transitions Array of valid menu transitions.
 * @param transition_count Number of elements in the transition array.
 *
 * @return true  If the application should continue running.
 * @return false If the transition indicates the program should exit.
 */
bool apply_transition(
    Menu *&current_menu,
    MenuAction action,
    const MenuTransition transitions[],
    int transition_count);

/**
 * @brief Initialize all menus used in the Pomodoro application.
 *
 * This function creates and configures every menu by calling
 * the corresponding create_xxx_menu functions. It centralizes
 * menu initialization and keeps main() clean.
 *
 * @param menus A container holding all menu instances.
 */
void init_menus(ClockMenus &menus);

int main()
{   
    // Create application window and load font
    open_window("Pomodoro App", 800, 600);
    load_font("main_font", "arial.ttf");

    // Initialize all menus
    ClockMenus menus;
    init_menus(menus);

    // Creat timer configuration
    TimerConfig timer_config;
    init_timer_config(timer_config);

    // Creat timer.
    PomodoroTimer timer;

    // Initialize sound.
    SoundControl sc;
    init_sound_control(sc);

    // Initialize sound_visualizer
    SoundVisualizer vis;
    init_visualizer(vis, sc);

    // Initialize tracker
    TimerTracker tracker;
    init_timer_tracker(tracker);

    // Initialize the timer background
    TimerBackground bg;
    load_timer_backgrounds(bg); 

    static const MenuTransition transitions[] =
        {   
            {&menus.main_menu, MenuAction::ACTION_GOTO_TIMER, &menus.timer_menu},
            {&menus.main_menu, MenuAction::ACTION_GOTO_SETTINGS, &menus.settings_menu},
            {&menus.main_menu, MenuAction::ACTION_QUIT, nullptr},

            {&menus.timer_menu, MenuAction::ACTION_BACK, &menus.main_menu},

            {&menus.settings_menu, MenuAction::ACTION_GOTO_STUDY_TIMER, &menus.study_timer_menu},
            {&menus.settings_menu, MenuAction::ACTION_GOTO_BREAK_TIMER, &menus.break_timer_menu},
            {&menus.settings_menu, MenuAction::ACTION_BACK, &menus.main_menu},

            {&menus.study_timer_menu, MenuAction::ACTION_BACK, &menus.settings_menu},

            {&menus.break_timer_menu, MenuAction::ACTION_BACK, &menus.settings_menu},

            {&menus.total_study_time_menu, MenuAction::ACTION_BACK, &menus.study_timer_menu},

            {&menus.total_break_time_menu, MenuAction::ACTION_BACK, &menus.break_timer_menu},

        };

    // Start from the main menu
    Menu *current_menu = &menus.main_menu;
    bool running = true;
    
    // Main application loop
    while (running && not quit_requested())
    {
        process_events();
        clear_screen(COLOR_WHITE);

        //Get the user option
        MenuAction action = handle_menu(*current_menu);

        // Draw the current menu
        if (!draw_menu(*current_menu))
        {
            draw_warning("Menu too large to display");
        }

        switch (action)
        {
        case MenuAction::ACTION_SET_TOTAL_STUDY:
            update_total_study_time(timer_config);
            break;

        case MenuAction::ACTION_SET_POMODORO_STUDY:
            update_pomodoro_study_time(timer_config);
            break;

        case MenuAction::ACTION_SET_TOTAL_BREAK:
            update_total_break_time(timer_config);
            break;

        case MenuAction::ACTION_SET_POMODORO_BREAK:
            update_pomodoro_break_time(timer_config);
            break;
        
        case MenuAction::ACTION_START_TIMER:
            run_pomodoro_timer(timer, timer_config, sc, tracker, bg, vis);
            break;


        default:
        // Use table-driven transition for navigation
            running = apply_transition(
                current_menu,
                action,
                transitions,
                sizeof(transitions) / sizeof(transitions[0]));
            break;
        }

        refresh_screen(60);
    }

    return 0;
}

bool apply_transition(
    Menu *&current_menu,
    MenuAction action,
    const MenuTransition transitions[],
    int transition_count)
{
    for (int i = 0; i < transition_count; i++)
    {
        if (transitions[i].from == current_menu &&
            transitions[i].action == action)
        {
            if (transitions[i].to == nullptr)
                return false;

            current_menu = transitions[i].to;
            return true;
        }
    }

    return true;
}

void init_menus(ClockMenus &menus)
{
    create_main_menu(menus.main_menu);
    create_timer_menu(menus.timer_menu);
    create_settings_menu(menus.settings_menu);
    create_study_timer_menu(menus.study_timer_menu);
    create_break_timer_menu(menus.break_timer_menu);
    create_total_study_time_menu(menus.total_study_time_menu);
    create_total_break_time_menu(menus.total_break_time_menu);
}
