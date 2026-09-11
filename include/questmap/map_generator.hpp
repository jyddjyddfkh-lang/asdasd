#pragma once
#include "questmap/audio_pipeline.hpp"
#include <string>
#include <vector>
namespace QuestMapBrowser {
enum class Difficulty { Easy, Normal, Hard, Expert, ExpertPlus };
struct Note { float time{}; int line{}; int layer{}; int cutDirection{}; };
struct MapData { std::string songName; std::string difficultyName; float bpm{}; std::vector<Note> notes; };
MapData GenerateBasicMap(const std::string& songName, const BeatInfo& beatInfo, Difficulty difficulty);
std::string ToJson(const MapData& map);
}
