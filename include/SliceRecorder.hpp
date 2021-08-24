#pragma once

#include "main.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "GlobalNamespace/ISaberSwingRatingCounter.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/ScoreModel.hpp"
#include "Data/NoteInfo.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "custom-types/shared/macros.hpp"
#include "Data/Tile.hpp"
#include "Data/NoteInfo.hpp"
#include <map>
#include <vector>

DECLARE_CLASS_CODEGEN(SliceDetails, SliceRecorder, UnityEngine::MonoBehaviour,
    DECLARE_CTOR(ctor);

    DECLARE_INSTANCE_METHOD(void, ProcessSlices);
    DECLARE_INSTANCE_METHOD(void, SongEnd);
    DECLARE_INSTANCE_METHOD(void, SongStart);
    DECLARE_INSTANCE_METHOD(void, ProcessNote, GlobalNamespace::NoteController* noteController, GlobalNamespace::NoteCutInfo noteCutInfo);

    DECLARE_INSTANCE_METHOD(void, HandleSaberSwingRatingCounterDidFinish, GlobalNamespace::ISaberSwingRatingCounter* saberSwingRatingCounter);
public:
    std::map<GlobalNamespace::ISaberSwingRatingCounter*, NoteInfo> _noteSwingInfos;
    std::vector<NoteInfo> _noteInfos;
)

static inline SliceDetails::SliceRecorder* SliceRecorderInstance;