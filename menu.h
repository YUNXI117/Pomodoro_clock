#pragma once

#include <string>
#include <vector>

#include "menu_action.h"

/**
 * @brief Represents a single selectable item in a menu.
 *
 * Each MenuItem consists of:
 * - text   : the label displayed on screen
 * - action : the action triggered when this item is selected
 */
struct MenuItem
{
    std::string text;   // Display text of the menu option
    MenuAction action;  // Action associated with this option
};

/**
 * @brief Represents a menu consisting of multiple menu items.
 *
 * A Menu contains:
 * - name  : identifier or title of the menu (used for display/debugging)
 * - items : a list of selectable menu items
 */
struct Menu
{
    std::string name;            // Name or title of the menu
    std::vector<MenuItem> items; // List of menu items
};

/**
 * @brief Add a new option to a menu.
 *
 * This function appends a new MenuItem to the given menu,
 * binding a display text to a specific MenuAction.
 *
 * @param menu   Menu to which the option will be added.
 * @param text   Text displayed for this menu option.
 * @param action Action triggered when this option is selected.
 */
void add_option(Menu &menu, const std::string &text, MenuAction action);

/**
 * @brief Draw the menu on the screen.
 *
 * This function is responsible for rendering all menu items
 * and arranging them visually using UI helper functions.
 *
 * @param menu Menu to be drawn.
 *
 * @return true  If the menu was drawn successfully.
 * @return false If the menu could not be drawn (e.g. too many items).
 */
bool draw_menu(const Menu &menu);

/**
 * @brief Handle user input for the menu.
 *
 * This function checks keyboard input and determines
 * which menu option has been selected by the user.
 *
 * @param menu Menu for which input is being handled.
 *
 * @return The MenuAction corresponding to the selected option,
 *         or ACTION_NONE if no valid input was detected.
 */
MenuAction handle_menu(const Menu &menu);
