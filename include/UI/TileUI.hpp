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

enum OrderedNoteCutDirection
{
	UpLeft = 0,
	Up = 1,
	UpRight = 2,
	Left = 3,
	Any = 4,
	Right = 5,
	DownLeft = 6,
	Down = 7,
	DownRight = 8
};

#include "UI/NoteUI.hpp"

DECLARE_CLASS_CODEGEN(SliceDetails, TileUIController, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_METHOD(void, Open, UnityEngine::Transform* parent);
    DECLARE_INSTANCE_METHOD(void, Close);
    DECLARE_INSTANCE_METHOD(void, Init, UnityEngine::Transform* parent);
	DECLARE_INSTANCE_METHOD(void, SelectTile, int index);

    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, tileView);
public:
	std::vector<UnityEngine::GameObject*> leftNoteTiles;
	std::vector<UnityEngine::GameObject*> rightNoteTiles;
)

static inline SliceDetails::TileUIController* tileUIInstance;