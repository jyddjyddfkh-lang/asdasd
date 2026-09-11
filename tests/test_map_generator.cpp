#include "questmap/map_generator.hpp"
#include <cassert>
int main() {
    QuestMapBrowser::BeatInfo b;
    b.bpm = 120;
    for (int i = 0; i < 8; ++i) b.beats.push_back(i * 0.5);
    auto m = QuestMapBrowser::GenerateBasicMap("Demo", b, QuestMapBrowser::Difficulty::Expert);
    assert(m.bpm == 120.0f);
    assert(!m.notes.empty());
    auto j = QuestMapBrowser::ToJson(m);
    assert(j.find("Demo") != std::string::npos);
    return 0;
}
