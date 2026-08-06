#include "timer_tracker.h"
#include "ui.h"

void init_timer_tracker(TimerTracker &tracker)
{
    tracker.study_elapsed = 0;
    tracker.break_elapsed = 0;

    tracker.study_limit_reached = false;
    tracker.break_limit_reached = false;
    tracker.popoup_study_done = false;
    tracker.popup_break_done = false;

    int interruption_count = 0;
}

void update_timer_tracker(
    TimerTracker &tracker,
    const PomodoroTimer &timer,
    const TimerConfig &config)
{
    if (timer.state != TimerState::RUNNING)
        return;

    else if (timer.phase == TimerPhase::STUDY)
    {
        tracker.study_elapsed++;

        if (!tracker.study_limit_reached &&
            tracker.study_elapsed >= config.total_study_minutes * 60)
        {
            tracker.study_limit_reached = true;
            tracker.popoup_study_done = true;
        }
    }
    else if (timer.phase == TimerPhase::BREAK)
    {
        tracker.break_elapsed++;

        if (!tracker.break_limit_reached &&
            tracker.break_elapsed >= config.total_break_minutes * 60)
        {
            tracker.break_limit_reached = true;
            tracker.popup_break_done = true;
        }
    }
    else
    {
        draw_warning("Something about tracker went wrong! ");
    }
}

void draw_tracker_popup(TimerTracker &tracker)
{
    int w = screen_width();
    int h = screen_height();

    const int POPUP_W = 200;
    const int POPUP_H = 90;
    const int BUTTEN_SIZE = 20;
    const int MARGIN = 20;

    //STUDY POPUP (LEFT)
    if (tracker.popoup_study_done)
    {
        int x = MARGIN;
        int y = h / 2 - POPUP_H;

        // popup background
        fill_rectangle(COLOR_GREEN, x, y, POPUP_W, POPUP_H);
        draw_rectangle(COLOR_BLACK, x, y, POPUP_W, POPUP_H);

        // text
        draw_text("Study goal completed!", COLOR_BLACK, x + 20, y + 45);

        // close button
        int button_x = x + POPUP_W - BUTTEN_SIZE - 10;
        int button_y = y + 10;

        fill_rectangle(COLOR_RED, button_x, button_y, BUTTEN_SIZE, BUTTEN_SIZE);
        draw_text("X", COLOR_WHITE, button_x + 6, button_y + 2);

        // click detection
        if (mouse_clicked(LEFT_BUTTON))
        {
            point_2d m = mouse_position();
            rectangle close_btn = rectangle_from(button_x, button_y, BUTTEN_SIZE, BUTTEN_SIZE);

            if (point_in_rectangle(m, close_btn))
            {
                tracker.popoup_study_done = false;
            }
        }
    }

    //BREAK POPUP (RIGHT)
    if (tracker.popup_break_done)
    {
        int x = w - POPUP_W - MARGIN;
        int y = h / 2 - POPUP_H;

        fill_rectangle(COLOR_GREEN, x, y, POPUP_W, POPUP_H);
        draw_rectangle(COLOR_BLACK, x, y, POPUP_W, POPUP_H);

        draw_text("Break goal completed!", COLOR_BLACK, x + 20, y + 45);

        int button_x = x + POPUP_W - BUTTEN_SIZE - 10;
        int button_y = y + 10;

        fill_rectangle(COLOR_RED, button_x, button_y, BUTTEN_SIZE, BUTTEN_SIZE);
        draw_text("X", COLOR_WHITE, button_x + 6, button_y + 2);

        rectangle button_area = rectangle_from(button_x, button_y, BUTTEN_SIZE, BUTTEN_SIZE);

        if (mouse_clicked(LEFT_BUTTON))
        {
            point_2d mouse = mouse_position();

            if (point_in_rectangle(mouse, button_area))
            {
                tracker.popup_break_done = false;
            }
        }
    }
}

void draw_interruption_counter(const PomodoroTimer &timer, TimerTracker &tracker)
{
    const int BTN_W = 300;
    const int BTN_H = 40;

    int x = screen_width() - BTN_W;
    int y = screen_height() - BTN_H;

    string text = "interrupt times(click to +1): " + std::to_string(tracker.interruption_count);

    fill_rectangle(COLOR_LAVENDER, x, y, BTN_W, BTN_H);
    draw_rectangle(COLOR_CORNSILK, x, y, BTN_W, BTN_H);
    draw_text(text, COLOR_BLACK, x + 10, y + 12);

    rectangle rectangle_area = rectangle_from(x, y, BTN_W, BTN_H);

    if(mouse_clicked(LEFT_BUTTON))
    {
        point_2d mouse = mouse_position();

        if(point_in_rectangle(mouse, rectangle_area) && timer.phase == TimerPhase::STUDY)
        {
            tracker.interruption_count ++;
        }
    }
}

