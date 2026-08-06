#include "sound_visualizer.h"
#include <fstream>    
#include <cstdint>     
#include <cmath>       
#include <algorithm>    
#include "ui.h"         
#include "sound.h"      

void init_visualizer(SoundVisualizer &vis, SoundControl &sc)
{
    vis.ready = false; // Mark visualiser as not ready until data is loaded

    // Set visualisation panel size
    vis.panel_width = 800;
    vis.panel_height = 100;

    // set playback start time (used for sync)
    vis.start_time_seconds = 0.0;

    // Configure bar settings
    vis.bar.total_bars = 30000;
    vis.bar.samples_per_bar = 1;
    vis.bar.bar_values.clear();

    // Load WAV data and compute MinMax bar values
    load_wav_and_compute_minmax(vis, sc.playlist[sc.current_index].wav_path);
}

bool load_wav_and_compute_minmax(SoundVisualizer &vis, const std::string &wav_path)
{
    std::ifstream file(wav_path, std::ios::binary);

    if (!file) return false;

    // Skip the standard 44-byte WAV header
    file.seekg(44);

    std::vector<float> samples;
    int16_t raw_sample;    

    // Read samples and normalise to range [-1, 1]
    while (file.read((char*)&raw_sample, sizeof(raw_sample)))
    {
        samples.push_back(raw_sample / 32768.0f);
    }

    int total_samples = (int)samples.size();

    if (total_samples == 0) return false;

    // Decide how many samples belong to one bar
    vis.bar.samples_per_bar = std::max(1, total_samples / vis.bar.total_bars);

    vis.bar.bar_values.clear();

    // MinMax algorithm:
    // For each bar, find the maximum absolute amplitude
    for (int bar_index = 0; bar_index < vis.bar.total_bars; bar_index++)
    {
        int start_sample = bar_index * vis.bar.samples_per_bar;

        int end_sample = std::min(start_sample + vis.bar.samples_per_bar, total_samples);

        float max_amplitude = 0.0f;

        for (int i = start_sample; i < end_sample; i++)
        {
            max_amplitude = std::max(max_amplitude, (float)std::fabs(samples[i]));
        }

        // Store normalised bar height (0..1)
        vis.bar.bar_values.push_back(max_amplitude);
    }

    vis.ready = true;
    return true;
}

void visualizer_start(SoundVisualizer &vis)
{
    vis.start_time_seconds = current_ticks() / 1000.0;
}

void draw_visualizer(SoundVisualizer &vis, float x, float y, SoundControl &sc)
{
    float center_y = y + vis.panel_height / 2.0f;
    draw_line(COLOR_GRAY, x, center_y, x + vis.panel_width, center_y);

    // Do not draw bars if data is not ready
    if (!vis.ready)
    {
        draw_warning("Visualizer not ready");
        return;
    }

    int current_bar = 0; 

    // Calculate current playback position
    if (sc.playing)
    {
        double elapsed_seconds = (current_ticks() / 1000.0) - vis.start_time_seconds;
        if (elapsed_seconds < 0) elapsed_seconds = 0;

        double duration_seconds = sc.playlist[sc.current_index].total_play_ticks;
        if (duration_seconds <= 0) duration_seconds = 1;

        float play_progress = (float)(elapsed_seconds / duration_seconds);
        if (play_progress < 0) play_progress = 0;
        if (play_progress > 1) play_progress = 1;

        current_bar = (int)std::floor(play_progress * vis.bar.total_bars);

        if (current_bar < 0) current_bar = 0;
        if (current_bar > vis.bar.total_bars) current_bar = vis.bar.total_bars;
    }

    // Width of each bar
    float bar_width = (float)vis.panel_width / (float)vis.bar.total_bars;

    // Draw waveform bars up to current play position
    for (int i = 0; i < current_bar; i++)
    {
        float amplitude = vis.bar.bar_values[i];  
        float bar_height = amplitude * vis.panel_height;

        float x_pos = x + i * bar_width;

        draw_line(COLOR_KHAKI,
                  x_pos, center_y - bar_height,
                  x_pos, center_y + bar_height);
    }

    // Draw red playhead line
    float playhead_x = x + current_bar * bar_width;
    draw_line(COLOR_RED, playhead_x, y, playhead_x, y + vis.panel_height);
}
