#include "questmap/mod.hpp"
#include "questmap/app.hpp"
#include "bsml/shared/BSML.hpp"

namespace QuestMapBrowser {

static const char* kTitle = "QuestMap Browser";
static const char* kTabText = "MAPS";
static const char* kHover = "Audio to Beat Saber maps";

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    (void)addedToHierarchy;
    (void)screenSystemEnabling;
    if (!firstActivation) return;

    auto* root = BSML::Lite::CreateScrollableSettingsContainer(self->get_transform());
    BSML::Lite::CreateText(root->get_transform(), "QuestMap Browser");
    BSML::Lite::CreateText(root->get_transform(), "Audio → Analyze → Generate → Install");
    BSML::Lite::CreateButton(root->get_transform(), "Music", [](){ Application::OpenMusic(); });
    BSML::Lite::CreateButton(root->get_transform(), "Map Maker", [](){ Application::OpenMapMaker(); });
    BSML::Lite::CreateButton(root->get_transform(), "My Maps", [](){ Application::OpenLibrary(); });
    BSML::Lite::CreateButton(root->get_transform(), "Downloads", [](){ Application::OpenDownloads(); });
    BSML::Lite::CreateButton(root->get_transform(), "Settings", [](){ Application::OpenSettings(); });
}

}

extern "C" void late_load() {
    using namespace QuestMapBrowser;
    il2cpp_functions::Init();
    BSML::Init();
    Application::Initialize();
    BSML::Register::RegisterMainMenuViewControllerMethod(
        kTitle, kTabText, kHover, DidActivate);
}
