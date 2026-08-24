#pragma once
#include <string>
#include <vector>

#include "splashkit.h"

// Forward declaration to avoid "undefined type" when compile the files.
// SoundControl is defined in sound.h
struct SoundControl;

/**
 * @brief Stores bar-related data for MinMax visualization.
 * 
 */
struct Bar
{
    int total_bars;                 // Total bars to draw
    int samples_per_bar;            // Number of samples per bar

    // Normalize bar values in [0, 1]
    // Each value represents the height of one bar
    std::vector<float> bar_values;  
};

/**
 * @brief This struct stores all data required to visualize the sounds.
 * using the MinMax algorithm.
 * 
 */
struct SoundVisualizer
{
    bool ready;            // True if WAV file has been loaded and processed successfully

    int panel_width;       // Width of the visualization area (pixels)
    int panel_height;      // Height of the visualization area (pixels)

    double start_time_seconds; // Time when playback started

    Bar bar;                // Bar data used for visualization
};

/**
 * @brief Initailize the sound visualizer
 * 
 * @param vis SoundVisualizer to initialize
 * @param sc  SoundControl containing current sound information
 */
void init_visualizer(SoundVisualizer &vis, SoundControl &sc);

/**
 * @brief Load a 16-bit WAV file and compute MinMax bar values.
 *
 * @param vis      SounsVisualizer to fill with computed data
 * @param wav_path Path to the WAV file
 * @return true if loading was successful, false otherwise
 */
bool load_wav_and_compute_minmax(
    SoundVisualizer &vis,
    const std::string &wav_path
);

/**
 * @brief Start visualizer
 * 
 * @param vis SoundVisualizer to update
 */
void visualizer_start(SoundVisualizer &vis);

/**
 * @brief Stop the visualizer
 * 
 * @param vis SoundVisualizer to update
 */
void visualizer_stop(SoundVisualizer &vis);

/*
 * Draw the MinMax visualization on screen.
 *
 * @param vis Soundvisualizer containing prepared visualization data
 * @param x   X position 
 * @param y   Y position 
 * @param sc  SoundControl containing some sound-related configuration
 */
void draw_visualizer(SoundVisualizer &vis, float x, float y, SoundControl &sc);
