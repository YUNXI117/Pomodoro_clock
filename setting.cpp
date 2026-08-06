#include "setting.h"
#include "splashkit.h"
#include "ui.h"

#include <algorithm>
#include <string>

static void update_time_value(
    const std::string &title,
    int &value_minutes,
    int min_limit,
    int max_limit)
{
    // Buffer to store user-typed numeric input
    std::string input_buffer = "";

    // Stay in setting page until user presses ESC or quits application
    while (!quit_requested())
    {
        process_events();
        clear_screen(COLOR_WHITE);

        // Draw page title
        draw_title(title);

        // Display current configured time
        draw_centered_text(
            "Current time: " + std::to_string(value_minutes) + " min",
            "main_font",
            28,
            COLOR_BLACK,
            160);

        // Display user instructions
        draw_centered_text("+5 (UP)    -5 (DOWN)", "main_font", 20, COLOR_GRAY, 220);
        draw_centered_text("Type number + Enter", "main_font", 18, COLOR_GRAY, 260);
        draw_hint("ESC to go back");

        // Increase value by 5 minutes
        if (key_typed(UP_KEY))
            value_minutes = std::min(value_minutes + 5, max_limit);

        // Decrease value by 5 minutes
        if (key_typed(DOWN_KEY))
            value_minutes = std::max(value_minutes - 5, min_limit);

        // Remove last digit when backspace is pressed
        if (key_typed(BACKSPACE_KEY) && !input_buffer.empty())
            input_buffer.pop_back();

        // Handle numeric key input (0-9)
        for (int i = 0; i <= 9; i++)
        {
            // Convert numeric key index to key_code
            key_code key = static_cast<key_code>(NUM_0_KEY + i);

            if (key_typed(key))
            {
                // Convert digit to character and append to input buffer
                input_buffer.push_back('0' + i);
            }
        }

        // Confirm typed input when Enter is pressed
        if (key_typed(RETURN_KEY) && !input_buffer.empty())
        {
            int value = std::stoi(input_buffer);

            // Apply value only if within allowed range
            if (value >= min_limit && value <= max_limit)
                value_minutes = value;

            input_buffer.clear();
        }

        // Display current typed input
        if (!input_buffer.empty())
        {
            draw_centered_text(
                "Input: " + input_buffer,
                "main_font",
                20,
                COLOR_BLUE,
                310);
        }

        // Exit setting page
        if (key_typed(ESCAPE_KEY))
            break;

        refresh_screen(60);
    }
}

void update_total_study_time(TimerConfig &config)
{
    update_time_value(
        "Set Total Study Time",
        config.total_study_minutes,
        1,
        600);
}

void update_pomodoro_study_time(TimerConfig &config)
{
    update_time_value(
        "Set Pomodoro Study Time",
        config.pomodoro_study_minutes,
        1,
        60);
}

void update_total_break_time(TimerConfig &config)
{
    update_time_value(
        "Set Total Break Time",
        config.total_break_minutes,
        1,
        120);
}

void update_pomodoro_break_time(TimerConfig &config)
{
    update_time_value(
        "Set Pomodoro Break Time",
        config.pomodoro_break_minutes,
        1,
        30);
}
