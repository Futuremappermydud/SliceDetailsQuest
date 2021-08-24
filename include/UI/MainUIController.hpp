#pragma once

#include "main.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "HMUI/ImageView.hpp"
#include "HMUI/ModalView.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DECLARE_CLASS_CODEGEN(SliceDetails, MainUIController, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_METHOD(void, Open, UnityEngine::Transform* parent);
    DECLARE_INSTANCE_METHOD(void, Close);
    DECLARE_INSTANCE_METHOD(void, SetTileScores);
    DECLARE_INSTANCE_METHOD(void, Init, UnityEngine::Transform* parent);

    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, tileView);
public:
	std::vector<UnityEngine::GameObject*> noteGridTiles;
)

static inline SliceDetails::MainUIController* mainUIInstance;