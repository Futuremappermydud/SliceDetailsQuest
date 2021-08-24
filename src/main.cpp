#include "main.hpp"
#include "questui/shared/QuestUI.hpp"
#include "custom-types/shared/register.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"
#include "GlobalNamespace/ScoreController.hpp"
#include "GlobalNamespace/GameSongController.hpp"
#include "UI/PauseUIController.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "SliceRecorder.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace SliceDetails;

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

MAKE_HOOK_MATCH(pause, &PauseMenuManager::ShowMenu, void, PauseMenuManager* self) {
    pause(self);
    getLogger().info("%s", "pause");
    pauseInstance->OnPause(self);
}

MAKE_HOOK_MATCH(resume, &PauseMenuManager::HandleResumeFromPauseAnimationDidFinish, void, PauseMenuManager* self) {
    resume(self);
    getLogger().info("%s", "resume");
    pauseInstance->OnResume(self);
}

MAKE_HOOK_MATCH(start, &GameSongController::StartSong, void, GameSongController* self, float songTimeOffset) {
    start(self, songTimeOffset);
    getLogger().info("%s", "start");
    pauseInstance = GameObject::New_ctor()->AddComponent<PauseUIController*>();
    auto pauseMenu = Resources::FindObjectsOfTypeAll<PauseMenuManager*>()->values[0];
    pauseInstance->get_transform()->SetParent(pauseMenu->pauseContainerTransform, false);
    pauseInstance->Init();

    SliceRecorderInstance = reinterpret_cast<SliceRecorder*>(GameObject::New_ctor()->AddComponent(csTypeOf(SliceRecorder*)));
    SliceRecorderInstance->SongStart();
}

MAKE_HOOK_MATCH(end, &GameSongController::StopSong, void, GameSongController* self) {
    end(self);
    getLogger().info("%s", "stop");
    SliceRecorderInstance->SongEnd();
}

MAKE_HOOK_MATCH(cut, &ScoreController::HandleNoteWasCut, void, ScoreController* self, GlobalNamespace::NoteController* noteController, ByRef<GlobalNamespace::NoteCutInfo> noteCutInfo) {
    cut(self, noteController, noteCutInfo);
    SliceRecorderInstance->ProcessNote(noteController, noteCutInfo.heldRef);
}

MAKE_HOOK_MATCH(swingRatingFinished, &CutScoreBuffer::HandleSaberSwingRatingCounterDidFinish, void, CutScoreBuffer* self, ISaberSwingRatingCounter* swingRatingCounter) {
    swingRatingFinished(self, swingRatingCounter);
    SliceRecorderInstance->HandleSaberSwingRatingCounterDidFinish(swingRatingCounter);
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    custom_types::Register::AutoRegister();
    QuestUI::Init();

    INSTALL_HOOK(getLogger(), pause);
    INSTALL_HOOK(getLogger(), resume);
    INSTALL_HOOK(getLogger(), start);

    INSTALL_HOOK(getLogger(), cut);
    INSTALL_HOOK(getLogger(), swingRatingFinished);
}