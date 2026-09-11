#include "questmap/security.hpp"
#include "questmap/audio_pipeline.hpp"
#include <algorithm>
#include <filesystem>
namespace QuestMapBrowser {
ValidationResult ValidateDownload(const std::string& fileName, uint64_t sizeBytes) {
    if (sizeBytes == 0 || sizeBytes > 512ULL * 1024ULL * 1024ULL) return {false, "file size rejected"};
    if (!IsSafeRelativePath(fileName)) return {false, "unsafe path"};
    const auto ext = std::filesystem::path(fileName).extension().string();
    if (!IsSupportedAudioExtension(ext)) return {false, "not a supported audio file"};
    return {true, {}};
}
bool IsSafeRelativePath(const std::string& path) {
    if (path.find('\0') != std::string::npos) return false;
    std::filesystem::path p(path);
    if (p.is_absolute()) return false;
    for (const auto& part : p) if (part == "..") return false;
    return true;
}
}
