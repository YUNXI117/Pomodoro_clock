#include "timer_runtime.h"
#include "splashkit.h"
#include "timer_types.h"
#include "timer_config.h"
#include "timer_ui.h"
#include "sound.h"
#include "timer_tracker.h"
#include "timer_background_ui.h"
#include "sound_visualizer.h"

static const TimerTransition TRANSITIONS[] =
{
        // -------- STUDY --------
        {TimerPhase::STUDY, TimerState::IDLE, TimerEvent::START, TimerPhase::STUDY, TimerState::RUNNING, true},
        {TimerPhase::STUDY, TimerState::RUNNING, TimerEvent::PAUSE, TimerPhase::STUDY, TimerState::PAUSED, false},
        {TimerPhase::STUDY, TimerState::PAUSED, TimerEvent::START, TimerPhase::STUDY, TimerState::RUNNING, false},
        {TimerPhase::STUDY, TimerState::RUNNING, TimerEvent::TIME_UP, TimerPhase::BREAK, TimerState::RUNNING, true},

        // -------- BREAK --------
        {TimerPhase::BREAK, TimerState::IDLE, TimerEvent::START, TimerPhase::BREAK, TimerState::RUNNING, true},
        {TimerPhase::BREAK, TimerState::RUNNING, TimerEvent::PAUSE, TimerPhase::BREAK, TimerState::PAUSED, false},
        {TimerPhase::BREAK, TimerState::PAUSED, TimerEvent::START, TimerPhase::BREAK, TimerState::RUNNING, false},
        {TimerPhase::BREAK, TimerState::RUNNING, TimerEvent::TIME_UP, TimerPhase::STUDY, TimerState::RUNNING, true},
};

void init_pomodoro_timer(PomodoroTimer &timer, const TimerConfig &config)
{
    timer.phase = TimerPhase::STUDY;
    timer.state = TimerState::IDLE;
    timer.remaining_seconds = config.pomodoro_study_minutes * 60;
}

bool update_pomodoro_timer(PomodoroTimer &timer, const TimerConfig &config, TimerTracker &tracker)
{
    static double last_tick = current_ticks();

    if (timer.state != TimerState::RUNNING)
    {
        last_tick = current_ticks();
        return false;
    }

    double now = current_ticks();

    if (now - last_tick >= 1000)
    {
        if (timer.remaining_seconds > 0)
        {
            timer.remaining_seconds--;
            last_tick = now;
        }

        if (timer.remaining_seconds == 0)
        {
            handle_timer_events(timer, config, TimerEvent::TIME_UP);
        }

        return true;
    }

    return false;
}

void handle_timer_events(PomodoroTimer &timer, const TimerConfig &config, TimerEvent event)
{   
    for (const auto &t : TRANSITIONS)
    {
        if (t.phase == timer.phase &&
            t.state == timer.state &&
            t.event == event)
        {
            timer.phase = t.next_phase;
            timer.state = t.next_state;
     
            if (t.reset_time)
            {
                if (timer.phase == TimerPhase::STUDY)
                    timer.remaining_seconds = config.pomodoro_study_minutes * 60;
                else
                    timer.remaining_seconds = config.pomodoro_break_minutes * 60;
            }

            return;
        }
    }
}

void run_pomodoro_timer(PomodoroTimer &timer, TimerConfig &config, SoundControl &sc, TimerTracker &tracker, TimerBackground &bg, SoundVisualizer &vis)
{
    init_pomodoro_timer(timer, config);

    while (!quit_requested())
    {   
        process_events();

        // 1. Handle input (SPACE = toggle)
        if (key_typed(SPACE_KEY))
        {
            if (timer.state == TimerState::RUNNING)
                handle_timer_events(timer, config, TimerEvent::PAUSE);

            else
                handle_timer_events(timer, config, TimerEvent::START);
        }

        // ESC -> exit timer UI
        if (key_typed(ESCAPE_KEY))
            break;

        // 2. Tick timer(1 second)
        bool ticked = update_pomodoro_timer(timer, config, tracker);

        if(ticked)
        {
            update_timer_tracker(tracker, timer, config);
        }

        update_sound_control_and_visualizer(sc, vis);

        // 3. Draw
        clear_screen(COLOR_WHITE);

        draw_timer_background(bg);
        draw_background_switch_button(bg);

        draw_sound_ui(sc, vis);

        draw_timer_ui(timer, config);

        draw_tracker_popup(tracker);
        draw_interruption_counter(timer, tracker);

        refresh_screen(60);
    }
}
