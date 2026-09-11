#include "questmap/audio_pipeline.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <filesystem>
#include <fstream>

namespace QuestMapBrowser {

static std::string Lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    return s;
}

bool IsSupportedAudioExtension(const std::string& extension) {
    const auto e = Lower(extension);
    return e == ".mp3" || e == ".wav" || e == ".ogg" || e == ".m4a" || e == ".flac";
}

std::optional<AudioInfo> AnalyzeAudioFile(const std::string& path) {
    std::error_code ec;
    std::filesystem::path p(path);
    if (!std::filesystem::is_regular_file(p, ec)) return std::nullopt;
    const auto size = std::filesystem::file_size(p, ec);
    if (ec || size == 0 || size > 512ULL * 1024ULL * 1024ULL) return std::nullopt;
    if (!IsSupportedAudioExtension(p.extension().string())) return std::nullopt;

    AudioInfo out;
    out.path = p.string();
    out.extension = Lower(p.extension().string());
    out.sizeBytes = size;
    out.title = p.stem().string();
    return out;
}

BeatInfo EstimateBeats(const std::vector<float>& samples, uint32_t sampleRate) {
    BeatInfo out;
    if (sampleRate == 0 || samples.size() < sampleRate) return out;

    // Lightweight fallback estimator. The full build can swap in a stronger onset detector.
    const size_t frame = std::max<size_t>(256, sampleRate / 20);
    double prev = 0.0;
    std::vector<double> onset;
    for (size_t i = 0; i + frame < samples.size(); i += frame) {
        double e = 0.0;
        for (size_t j = 0; j < frame; ++j) {
            const double x = samples[i + j];
            e += x * x;
        }
        e = std::sqrt(e / static_cast<double>(frame));
        if (e > prev * 1.18 && e > 0.01) onset.push_back(static_cast<double>(i) / sampleRate);
        prev = 0.92 * prev + 0.08 * e;
    }

    out.onsets = onset;
    if (onset.size() >= 3) {
        std::vector<double> intervals;
        for (size_t i = 1; i < onset.size(); ++i) {
            const double d = onset[i] - onset[i - 1];
            if (d >= 0.25 && d <= 2.0) intervals.push_back(d);
        }
        if (!intervals.empty()) {
            std::sort(intervals.begin(), intervals.end());
            const double median = intervals[intervals.size() / 2];
            out.bpm = std::clamp(60.0 / median, 60.0, 220.0);
        }
    }

    const double step = 60.0 / std::max(1.0, out.bpm);
    const double duration = static_cast<double>(samples.size()) / sampleRate;
    for (double t = 0.0; t < duration; t += step) out.beats.push_back(t);
    return out;
}
}
