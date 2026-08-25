#pragma once

#include <vector>
#include "splashkit.h"

/**
 * @brief Stores and manages background images for the timer.
 *
 * This structure holds a collection of background images and keeps track
 * of which background is currently selected using an index.
 */
struct TimerBackground
{
    std::vector<bitmap> backgrounds;
    int current_bg_index = 0;
};

/**
 * @brief Load the timer background images.
 * 
 * @param bg the struct witch store the background config
 */
void load_timer_backgrounds(TimerBackground &bg);

/**
 * @brief Draw the background in the timer page.
 * 
 * @param bg the struct witch store the background config
 */
void draw_timer_background(TimerBackground &bg);

/**
 * @brief Draw the button that user can click to change the background.
 * 
 * @param bg the struct witch store the background config
 */
void draw_background_switch_button(TimerBackground &bg);
