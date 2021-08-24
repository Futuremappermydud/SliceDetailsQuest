#pragma once

#include "main.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "custom-types/shared/macros.hpp"
#include "Data/Tile.hpp"
#include "Data/NoteInfo.hpp"

DECLARE_CLASS_CODEGEN(SliceDetails, SliceProcessor, UnityEngine::MonoBehaviour,
    //DECLARE_DEFAULT_CTOR();
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, ResetProcessor);
public:
    std::vector<Tile> tiles;
    bool ready = false;
    void ProcessSlices(std::vector<NoteInfo> noteInfos);
)

static inline SliceDetails::SliceProcessor* SliceProcessorInstance;