#include "timer_ui.h"
#include "ui.h"
#include "splashkit.h"
#include <ctime>
#include "timer_config.h"

std::string get_today_date()
{
    time_t now = time(nullptr);
    tm *lt = localtime(&now);

    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", lt);
    return std::string(buffer);
}

std::string format_time_mmss(int total_seconds)
{
    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;

    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, seconds);
    return std::string(buffer);
}

std::string control_hint(TimerState state)
{
    switch (state)
    {
    case TimerState::RUNNING:
        return "Pause (SPACE)";
    case TimerState::PAUSED:
        return "Start (SPACE)";
    case TimerState::IDLE:
        return "Start (SPACE)";

    default:
        return "";
    }
}

bool draw_timer_ui(PomodoroTimer &timer)
{

    if(timer.phase == TimerPhase::STUDY)
    draw_title("----------Study----------");
    else
    draw_title("----------Break----------");

    // Time display (MM:SS)
    draw_centered_text(
        format_time_mmss(timer.remaining_seconds),
        "main_font",
        72,
        COLOR_BLACK,
        200);
    
    // Draw date
    draw_left_text(
        get_today_date(),
        "main_font",
        20,
        COLOR_BLACK,
        0);

    // Control hint
    draw_centered_text(
        control_hint(timer.state),
        "main_font",
        20,
        COLOR_CYAN,
        280);

    draw_hint("ESC to return");

    return true;
}



