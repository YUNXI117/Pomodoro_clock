#include "menu.h"
#include "ui.h"

static const int FONT_SIZE = 32;
static const int SPACING   = 20;

using namespace std;

void add_option(Menu &menu, const string &text, MenuAction action)
{
    menu.items.push_back({ text, action });
}

bool draw_menu(const Menu &menu)
{
    if (menu.items.empty()) return true;

    float x = screen_width() / 4.0f;
    float y = screen_height() / 4.0f;

    for (int i = 0; i < menu.items.size(); i++)
    {
        string label = to_string(i + 1) + ". " + menu.items[i].text;
        int height = text_height(label, "main_font", FONT_SIZE);

        if (y + height > screen_height())
        {
            return false;
        }

        draw_text( 
            label,
            COLOR_BLACK,
            "main_font",
            FONT_SIZE,
            x,
            y
        );

        y += height + SPACING;
    }

    return true;
}

MenuAction handle_menu(const Menu &menu)
{
    for (int i = 0; i < menu.items.size(); i++)
    {
        key_code key = static_cast<key_code>(NUM_1_KEY + i);
        if (key_typed(key))
        {
            return menu.items[i].action; 
        }
    }
    return MenuAction::ACTION_NONE;
}
