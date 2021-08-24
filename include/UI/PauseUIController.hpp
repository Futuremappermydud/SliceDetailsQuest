#pragma once

#include "main.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "HMUI/ImageView.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DECLARE_CLASS_CODEGEN(SliceDetails, PauseUIController, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_METHOD(void, Init);
    DECLARE_INSTANCE_METHOD(void, OnPause, GlobalNamespace::PauseMenuManager* pauseMenuManager);
    DECLARE_INSTANCE_METHOD(void, OnResume, GlobalNamespace::PauseMenuManager* pauseMenuManager);
)

static inline SliceDetails::PauseUIController* pauseInstance;