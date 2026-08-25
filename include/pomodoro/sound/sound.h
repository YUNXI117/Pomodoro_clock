#pragma once
#include <string>
#include <vector>

#include "splashkit.h"

// Forward declaration to avoid "undefined type" when compile the files
// SoundVisualizer is defined in sound_visualize.h
struct SoundVisualizer;

/**
 * @brief Represents a single song
 * 
 */
struct Sound
{
    std::string name;       //The song's name
    sound_effect sound;     //MP3 file loaded by SplashKit for playing
    float total_play_ticks; // to record the total seconds which this sound have.
    std::string wav_path;   //A wav file path. 
};

/**
 * @brief  Stores all sound-related states and resources.
 * 
 */
struct SoundControl
{
    bool enabled;        // True if sound is enabled
    bool playing;        // True if music is currently playing

    bitmap icon_on;      // Bitmap used to represent sound ON
    bitmap icon_off;     // Bitmap used to represent sound OFF

    std::vector<Sound> playlist; // A list of sounds
    int current_index;  // Index of the currently selected sound in the playlist.
};

/**
 * @brief Initialise the sound control system
 * 
 * @param sc Sound control struct
 */
void init_sound_control(SoundControl &sc);

/**
 * @brief Play the next sound in the playlist
 * 
 * @param sc SoundControl containing some sound-related configuration
 * @param vis SoundVisualizer used to reset and start visualization
 */
void next_sound(SoundControl &sc, SoundVisualizer &vis);

/**
 * @brief Play the previous sound in the playlist
 * 
 * @param sc SoundControl containing some sound-related configuration
 * @param vis SoundVisualizer used to reset and start visualization
 */
void prev_sound(SoundControl &sc, SoundVisualizer &vis);

/**
 * @brief Update the sound system state and visualizer
 * 
 * @param sc SoundControl structure to update
 * @param vis SoundVisualizer used to visualization
 */
void update_sound_control_and_visualizer(SoundControl &sc, SoundVisualizer &vis);

/**
 * @brief Draw the sound interface
 * 
 * @param sc SoundControl containing some sound-related configuration
 * @param vis SoundVisualizer used to reset and start visualization
 */
void draw_sound_ui(SoundControl &sc, SoundVisualizer &vis);

/**
 * @brief Sort the playlist by sound name in alphabetical order (A-Z).
 * 
 * @param sc SoundControl containing playlist
 */
void sort_playlist_by_name(SoundControl &sc);
