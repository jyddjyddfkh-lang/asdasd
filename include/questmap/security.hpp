#pragma once
#include <cstdint>
#include <string>
namespace QuestMapBrowser {
struct ValidationResult { bool ok{}; std::string error; };
ValidationResult ValidateDownload(const std::string& fileName, uint64_t sizeBytes);
bool IsSafeRelativePath(const std::string& path);
}
