#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <vector>
namespace QuestMapBrowser {
struct AudioInfo {
    std::string path, title, artist, extension;
    uint64_t sizeBytes{};
    uint32_t sampleRate{};
    uint16_t channels{};
    double durationSeconds{};
};
struct BeatInfo { double bpm{120.0}; std::vector<double> beats, onsets; };
std::optional<AudioInfo> AnalyzeAudioFile(const std::string& path);
BeatInfo EstimateBeats(const std::vector<float>& monoSamples, uint32_t sampleRate);
bool IsSupportedAudioExtension(const std::string& extension);
}
