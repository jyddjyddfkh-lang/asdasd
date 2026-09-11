#pragma once
#include "beatsaber-hook/shared/utils/logging.hpp"
namespace QuestMapBrowser {
inline auto& Logger() {
    static auto logger = Paper::getLogger("QuestMapBrowser");
    return logger;
}
}
