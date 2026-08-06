#include "timer_config.h"

void init_timer_config(TimerConfig &config)
{
    config.total_study_minutes    = 120;
    config.pomodoro_study_minutes = 25;
    config.total_break_minutes    = 30;
    config.pomodoro_break_minutes = 5;
}

