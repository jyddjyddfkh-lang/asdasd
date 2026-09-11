#include "questmap/app.hpp"
#include "questmap/mod.hpp"
#include "questmap/audio_pipeline.hpp"

namespace QuestMapBrowser::Application {
void Initialize() {
    Logger().info("QuestMap Browser initialized");
}
void OpenMusic() {
    Logger().info("Music screen requested");
}
void OpenMapMaker() {
    Logger().info("Map Maker requested");
}
void OpenLibrary() {
    Logger().info("Map Library requested");
}
void OpenDownloads() {
    Logger().info("Downloads requested");
}
void OpenSettings() {
    Logger().info("Settings requested");
}
}
