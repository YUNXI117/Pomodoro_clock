# Pomodoro Clock

A desktop Pomodoro timer built with C++ and SplashKit.

## Project Structure

- `src/` contains implementation files grouped by feature.
- `include/pomodoro/` contains public project headers grouped by feature.
- `images/` contains timer background and icon assets.
- `sounds/` contains MP3 files used for playback.
- `Wav/` contains WAV files used by the audio visualizer.

```text
src/
  main.cpp
  menu/
  sound/
  timer/
  ui/

include/pomodoro/
  menu/
  sound/
  timer/
  ui/
```

## Build

Run this from the project root in PowerShell:

```powershell
./build.ps1
```

Then run:

```powershell
./test.exe
```

## Academic Integrity

If this project was created for coursework, keep the full source code private unless your unit staff confirm that public sharing is allowed.
