#include "UI/PauseUIController.hpp"
#include "UI/MainUIController.hpp"
#include "main.hpp"
#include "Data/Score.hpp"
#include "Data/Tile.hpp"
#include "SliceProcessor.hpp"
#include "SliceRecorder.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace UnityEngine::UI;

DEFINE_TYPE(SliceDetails, PauseUIController);

void SliceDetails::PauseUIController::Init()
{
    getLogger().info("%s", "pauseUIStart");
    GameObject* swagshit = GameObject::New_ctor(il2cpp_utils::createcsstr("Slice Details UI"));
    SliceDetails::MainUIController* d = swagshit->AddComponent<SliceDetails::MainUIController*>();
    mainUIInstance = d;
    mainUIInstance->Init(get_transform()->get_parent());
    getLogger().info("%p", mainUIInstance);
    swagshit->SetActive(false);
}
void SliceDetails::PauseUIController::OnPause(PauseMenuManager* pauseMenuManager)
{
    getLogger().info("%s", "pauseUIPause"); 
    getLogger().info("%p", mainUIInstance);
    mainUIInstance->Open(get_transform()->get_parent());
    SliceRecorderInstance->ProcessSlices();
    mainUIInstance->SetTileScores();
}

void SliceDetails::PauseUIController::OnResume(PauseMenuManager* pauseMenuManager)
{
    mainUIInstance->Close();
}