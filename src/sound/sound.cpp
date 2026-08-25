#include "pomodoro/sound/sound.h"
#include "pomodoro/ui/ui.h"
#include "pomodoro/sound/sound_visualizer.h"

void init_sound_control(SoundControl &sc)
{
    sc.enabled = false;
    sc.playing = false;

    sc.icon_on = load_bitmap("sound_on", "sound_on.png");
    sc.icon_off = load_bitmap("sound_off", "sound_off.png");

    sc.playlist.clear();
    // name   sound   total_play_ticks     wav_path
    sc.playlist.push_back({"Dreams_under_the_stars", load_sound_effect("Dreams_under_the_stars", "sounds/Dreams_under_the_stars.mp3"), 192, "Wav/Dreams_under_the_stars.wav"});
    sc.playlist.push_back({"Sense_of_the_Light", load_sound_effect("Sense_of_the_Light", "sounds/Sense_of_the_Light.mp3"), 256, "Wav/Sense_of_the_Light.wav"});
    sc.playlist.push_back({"Canon", load_sound_effect("Canon", "sounds/Canon.mp3"), 328, "Wav/Canon.wav"});
    sc.playlist.push_back({"Summer", load_sound_effect("Summer", "sounds/Summer.mp3"), 140, "Wav/Summer.wav"});
    sc.playlist.push_back({"Merry_Christmas_Mr. Lawrence", load_sound_effect("Merry_Christmas_Mr.Lawrence", "sounds/Merry_Christmas_Mr.Lawrence.mp3"), 357, "Wav/Merry_Christmas_Mr.Lawrence.wav"});
    sc.playlist.push_back({"Last_night_on_earth", load_sound_effect("Last_night_on_earth", "sounds/Last_night_on_earth.mp3"), 221, "Wav/Last_night_on_earth.wav"});

    // Check whether the bitmap and playlist load correctly.
    sc.enabled = bitmap_valid(sc.icon_off) && bitmap_valid(sc.icon_on);
    for (auto &t : sc.playlist)
    {
        sc.enabled = sc.enabled && sound_effect_valid(t.sound);
    }

    if (!sc.enabled)
    {
        draw_warning("Some resources failed to load!");
        return;
    }

    sc.current_index = 0;
}

void next_sound(SoundControl &sc, SoundVisualizer &vis)
{
    if (sc.playlist.empty())
        return;

    // Stop the current sound play
    stop_sound_effect(sc.playlist[sc.current_index].sound);
    sc.playing = false;

    // Switch to next sound
    sc.current_index++;
    if (sc.current_index >= (int)sc.playlist.size())
        sc.current_index = 0;

    init_visualizer(vis, sc);
    play_sound_effect(sc.playlist[sc.current_index].sound);
    sc.playing = true;
    visualizer_start(vis);
}

void prev_sound(SoundControl &sc, SoundVisualizer &vis)
{
    if (sc.playlist.empty())
        return;

    // Stop the current sound play
    stop_sound_effect(sc.playlist[sc.current_index].sound);
    sc.playing = false;

    // Switch to previous sound
    sc.current_index--;
    if (sc.current_index < 0)
        sc.current_index = (int)sc.playlist.size() - 1;

    init_visualizer(vis, sc);
    play_sound_effect(sc.playlist[sc.current_index].sound);
    sc.playing = true;
    visualizer_start(vis);
}

void update_sound_control_and_visualizer(SoundControl &sc, SoundVisualizer &vis)
{
    if (sc.playing && !sc.playlist.empty())
    {
        sound_effect current_sound = sc.playlist[sc.current_index].sound;
        if (!sound_effect_playing(current_sound))
        {
            next_sound(sc, vis);
        }
    }

    bitmap icon = sc.playing ? sc.icon_on : sc.icon_off;

    float x = 0;
    float y = screen_height() - bitmap_height(icon);

    const int BTN_W = 100;
    const int BTN_H = bitmap_height(icon) / 2;

    rectangle rectangle_area_icon = rectangle_from(x, y, bitmap_width(icon), bitmap_height(icon));
    rectangle rectangle_area_next = rectangle_from(x + bitmap_width(icon), y, BTN_W, BTN_H);
    rectangle rectangle_area_pre = rectangle_from(x + bitmap_width(icon), y + BTN_H, BTN_W, BTN_H);
    rectangle rectangle_area_sort = rectangle_from(x, y - 20, 250, 20);

    // To turn on / off the music player
    if (mouse_clicked(LEFT_BUTTON))
    {
        point_2d mouse = mouse_position();

        if (point_in_rectangle(mouse, rectangle_area_icon))
        {
            if (sc.playlist.empty())
                return;

            sc.playing = !sc.playing;

            if (sc.playing)
            {
                if (!vis.ready)
                    init_visualizer(vis, sc);
                play_sound_effect(sc.playlist[sc.current_index].sound);
                visualizer_start(vis);
            }
            else
            {
                stop_sound_effect(sc.playlist[sc.current_index].sound);
            }
        }

        // To check whether to change sounds
        else if (point_in_rectangle(mouse, rectangle_area_next))
            next_sound(sc, vis);
        else if (point_in_rectangle(mouse, rectangle_area_pre))
            prev_sound(sc, vis);
        // To sort the sounds by names
        else if (point_in_rectangle(mouse, rectangle_area_sort))
        {
            // Stop the original sound
            if (sc.playing)
            {
                stop_sound_effect(sc.playlist[sc.current_index].sound);
                sc.playing = false;
            }

            // Begin sort
            sort_playlist_by_name(sc);

            init_visualizer(vis, sc);
        }
    }
}

void draw_sound_ui(SoundControl &sc, SoundVisualizer &vis)
{
    // Draw icon
    bitmap icon = sc.playing ? sc.icon_on : sc.icon_off;

    float icon_x = 0;
    float icon_y = screen_height() - bitmap_height(icon);

    draw_bitmap(icon, icon_x, icon_y);

    // Draw the sound name
    float sound_name_x = 0;
    float sound_name_y = icon_y - 40;

    std::string sound_name_text = "Now playing: " + sc.playlist[sc.current_index].name;

    draw_text(sound_name_text, COLOR_BLACK, sound_name_x, sound_name_y);

    // Draw the sort button
    float sort_button_x = 0;
    float sort_button_y = icon_y - 20;

    const int SORT_W = 250;
    const int SORT_H = 20;

    fill_rectangle(COLOR_WHITE, sort_button_x, sort_button_y, SORT_W, SORT_H);
    draw_rectangle(COLOR_GRAY, sort_button_x, sort_button_y, SORT_W, SORT_H);
    draw_text("Sort sounds by name: A-Z", COLOR_BLACK, sort_button_x + 10, sort_button_y + 5);

    // Draw pre and next button
    const int BTN_W = 100;
    const int BTN_H = bitmap_height(icon) / 2;

    double next_button_x = bitmap_width(icon);
    double pre_button_x = bitmap_width(icon);

    double next_button_y = screen_height() - bitmap_height(icon);
    double pre_button_y = screen_height() - bitmap_height(icon) / 2;

    fill_rectangle(COLOR_WHITE, next_button_x, next_button_y, BTN_W, BTN_H);
    fill_rectangle(COLOR_WHITE, pre_button_x, pre_button_y, BTN_W, BTN_H);

    draw_rectangle(COLOR_GRAY, next_button_x, next_button_y, BTN_W, BTN_H);
    draw_rectangle(COLOR_GRAY, pre_button_x, pre_button_y, BTN_W, BTN_H);

    draw_text("Next >>", COLOR_BLACK, next_button_x + 10, next_button_y + 5);
    draw_text("Prev <<", COLOR_BLACK, pre_button_x + 10, pre_button_y + 5);

    float vis_x = 0;
    // 40: sound name height -> 20   sort button y -> 20
    float vis_y = icon_y - 40 - vis.panel_height - 20;
    if (vis_y < 0)
        vis_y = 0;

    draw_visualizer(vis, vis_x, vis_y, sc);
}

void sort_playlist_by_name(SoundControl &sc)
{
    if (sc.playlist.size() <= 1)
        return;

    // Insertion Sort by sounds' name (A-Z)
    for (int i = 1; i < (int)sc.playlist.size(); i++)
    {
        Sound key = sc.playlist[i];
        int j = i - 1;

        while (j >= 0 && sc.playlist[j].name > key.name)
        {
            sc.playlist[j + 1] = sc.playlist[j];
            j--;
        }

        sc.playlist[j + 1] = key;
    }

    // Reset index after sorting
    sc.current_index = 0;
}
