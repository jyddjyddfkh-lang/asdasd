# QuestMap Browser — Beat Saber Quest Mod

Target: Beat Saber Quest `1.40.8_7379` / `com.beatgames.beatsaber` / Scotland2.

This repository is an MVP implementation scaffold designed around the real QMOD/Scotland2 layout used by current Quest mods. It contains the UI entry point, audio-file pipeline, BPM/beat detection interfaces, basic automatic note generation, map metadata, security validation, and automated QMOD packaging scripts.

## Build requirements

- Windows PowerShell 7+
- CMake
- Ninja
- Android NDK
- QPM/qpm-rust

The project intentionally does **not** ship a guessed or fake ARM64 `.so`. Run `pwsh ./scripts/build.ps1` on a configured Quest modding machine; QPM restores the exact native dependencies and compiles the mod.

## Build

```powershell
qpm restore
qpm s build
qpm s qmod
```

or:

```powershell
pwsh ./scripts/build.ps1
```

The generated QMOD is written to `./build/QuestMapBrowser.qmod` (path may vary by qpm version).

## MVP scope

- Main-menu QuestMap Browser tab
- Audio import/detection pipeline
- Safe extension/size/path validation
- WAV metadata parsing
- BPM/beat analysis interface with lightweight fallback estimation
- Automatic map generation with Easy/Normal/Hard/Expert/Expert+
- Map library metadata storage
- Installation adapter boundary for SongCore/Beat Saber integration
- QMOD packaging

Browser rendering, remote HTTP download and the full timeline editor are isolated behind interfaces so they can be added without changing the map engine.

## Important

The installer deliberately does not hard-code a guessed Beat Saber CustomLevels path. The real installation adapter should use the SongCore API available in the target mod environment. This avoids breaking when the Quest storage implementation changes.
