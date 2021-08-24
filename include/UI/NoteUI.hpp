#pragma once

#include "main.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "HMUI/ImageView.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "GlobalNamespace/ColorType.hpp"
#include "custom-types/shared/macros.hpp"
#include "Data/Tile.hpp"
#include "Data/Score.hpp"
#include "Data/NoteInfo.hpp"
#include "UI/TileUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DECLARE_CLASS_CODEGEN(SliceDetails, NoteUI, UnityEngine::MonoBehaviour,

    //Some silly person decided to use unity image and Not Image view >:(
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Image*, _directionArrowImage);
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, _cutGroup);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Image*, _cutArrowImage);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Image*, _cutDistanceImage);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Image*, _backgroundImage);

    DECLARE_INSTANCE_FIELD(UnityEngine::Color, _noteColor);

    DECLARE_INSTANCE_FIELD(float, _noteRotation);
public:
    void SetData(float angle, float offset, Score score);
    void Init(OrderedNoteCutDirection cutDirection, GlobalNamespace::ColorType colorType);
)