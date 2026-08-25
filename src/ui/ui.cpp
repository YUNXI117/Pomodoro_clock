#include "pomodoro/ui/ui.h"

void draw_centered_text(
    const string &text,
    const string &font,
    int size,
    color clr,
    float y
)
{
    float x = (screen_width() - text_width(text, font, size)) / 2;
    draw_text(text, clr, font, size, x, y);
}

void draw_left_text(
    const string &text,
    const string &font,
    int size,
    color clr,
    float y
)
{
    float x = 0;
    draw_text(text, clr, font, size, x, y);
}

void draw_title(const string &text)
{
    draw_centered_text(text, "main_font", 36, COLOR_BLACK, 80);
}

void draw_warning(const string &text)
{
    draw_centered_text(text, "main_font", 20, COLOR_RED, screen_height() - 40);
}

void draw_hint(const string &text)
{
    draw_centered_text(text, "main_font", 18, COLOR_CYAN, screen_height() - 20);
}

