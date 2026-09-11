#include "questmap/map_generator.hpp"
#include <algorithm>
#include <sstream>

namespace QuestMapBrowser {
static int Density(Difficulty d) {
    switch (d) {
        case Difficulty::Easy: return 1;
        case Difficulty::Normal: return 1;
        case Difficulty::Hard: return 2;
        case Difficulty::Expert: return 2;
        case Difficulty::ExpertPlus: return 3;
    }
    return 1;
}
static const char* Name(Difficulty d) {
    switch (d) {
        case Difficulty::Easy: return "Easy";
        case Difficulty::Normal: return "Normal";
        case Difficulty::Hard: return "Hard";
        case Difficulty::Expert: return "Expert";
        case Difficulty::ExpertPlus: return "Expert+";
    }
    return "Expert";
}
MapData GenerateBasicMap(const std::string& songName, const BeatInfo& beatInfo, Difficulty difficulty) {
    MapData m;
    m.songName = songName;
    m.difficultyName = Name(difficulty);
    m.bpm = static_cast<float>(beatInfo.bpm);
    const int density = Density(difficulty);
    int toggle = 0;
    for (double t : beatInfo.beats) {
        const int count = density == 1 ? 1 : ((toggle++ % density) ? 1 : density);
        for (int n = 0; n < count; ++n) {
            Note note;
            note.time = static_cast<float>(t + n * 0.25 * 60.0 / beatInfo.bpm);
            note.line = (toggle + n) % 4;
            note.layer = ((toggle / 2) + n) % 3;
            note.cutDirection = (toggle + n) % 8;
            m.notes.push_back(note);
        }
    }
    return m;
}
std::string ToJson(const MapData& map) {
    std::ostringstream o;
    o << "{\"songName\":\"" << map.songName << "\",\"difficulty\":\"" << map.difficultyName
      << "\",\"beatsPerMinute\":" << map.bpm << ",\"notes\":[";
    for (size_t i = 0; i < map.notes.size(); ++i) {
        if (i) o << ',';
        const auto& n = map.notes[i];
        o << "{\"time\":" << n.time << ",\"line\":" << n.line << ",\"layer\":" << n.layer
          << ",\"cutDirection\":" << n.cutDirection << '}';
    }
    o << "]}";
    return o.str();
}
}
