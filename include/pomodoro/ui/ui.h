#pragma once
#include "splashkit.h"

/**
 * @brief Draw text horizontally centered on the screen.
 *
 * This function calculates the horizontal center position
 * automatically and draws the text at the specified vertical
 * position.
 *
 * @param text The text string to be displayed.
 * @param font The font name used for rendering.
 * @param size Font size.
 * @param clr  Text color.
 * @param y    Vertical position on the screen.
 */
void draw_centered_text(
    const string &text,
    const string &font,
    int size,
    color clr,
    float y
);

/**
 * @brief Draw text aligned to the left side of the screen.
 *
 * This function renders text starting from a fixed left margin
 * at the specified vertical position.
 *
 * @param text The text string to be displayed.
 * @param font The font name used for rendering.
 * @param size Font size.
 * @param clr  Text color.
 * @param y    Vertical position on the screen.
 */
void draw_left_text(
    const string &text,
    const string &font,
    int size,
    color clr,
    float y
);

/**
 * @brief Draw a title text at the top of the screen.
 *
 * Uses a predefined font size and position to ensure
 * consistent title styling across the application.
 *
 * @param text Title text to be displayed.
 */
void draw_title(const string &text);

/**
 * @brief Draw a warning message near the bottom of the screen.
 *
 * This function is typically used to display error or warning
 * messages to the user.
 *
 * @param text Warning message to be displayed.
 */
void draw_warning(const string &text);

/**
 * @brief Draw a hint message near the bottom of the screen.
 *
 * This function is used to display helpful instructions,
 * such as key bindings or navigation hints.
 *
 * @param text Hint message to be displayed.
 */
void draw_hint(const string &text);

