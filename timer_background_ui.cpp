#include "timer_background_ui.h"
#include <vector>
#include "SplashKit.h"

void load_timer_backgrounds(TimerBackground &bg)
{
    bg.backgrounds.push_back(load_bitmap("bg0", "timer_bg_0.png"));
    bg.backgrounds.push_back(load_bitmap("bg1", "timer_bg_1.png"));
    bg.backgrounds.push_back(load_bitmap("bg2", "timer_bg_2.png"));
}

void draw_timer_background(TimerBackground &bg)
{
    if(bg.backgrounds.empty()) return;

    draw_bitmap(bg.backgrounds[bg.current_bg_index], 0, 0);
}

void draw_background_switch_button(TimerBackground &bg)
{
    const int BTN_W = 40;
    const int BTN_H = 40;
    const int MARGIN = 15;

    int x = screen_width() - BTN_W - MARGIN;
    int y = MARGIN;

    fill_rectangle(COLOR_MEDIUM_SPRING_GREEN, x, y, BTN_W, BTN_H);
    draw_rectangle(COLOR_AQUA, x, y, BTN_W, BTN_H);
    draw_text("BG", COLOR_AZURE, x + 8, y + 10);

    rectangle rectangle_area = rectangle_from(x, y, BTN_W, BTN_H);

    if(mouse_clicked(LEFT_BUTTON))
    {
        point_2d mouse = mouse_position();

        if(point_in_rectangle(mouse, rectangle_area))
        {
            bg.current_bg_index++;

            if(bg.current_bg_index >= bg.backgrounds.size())
            {
                bg.current_bg_index = 0;
            }
        }
    }

}