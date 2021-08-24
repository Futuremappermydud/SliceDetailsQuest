#pragma once
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"
#include "UnityEngine/Vector2.hpp"
#include "Score.hpp"

namespace SliceDetails
{
    struct NoteInfo
    {
        public:
        GlobalNamespace::NoteData* noteData;
		GlobalNamespace::NoteCutInfo cutInfo;
		float cutAngle;
		float cutOffset;
		UnityEngine::Vector2 noteGridPosition;
		int noteIndex;

		Score score = Score(0, 0, 0);

		NoteInfo(GlobalNamespace::NoteData* noteData, GlobalNamespace::NoteCutInfo cutInfo, float cutAngle, float cutOffset, UnityEngine::Vector2 noteGridPosition, int noteIndex) {
			this->noteData = noteData;
			this->cutInfo = cutInfo;
			this->cutAngle = cutAngle;
			this->cutOffset = cutOffset;
			this->noteGridPosition = noteGridPosition;
			this->noteIndex = noteIndex;
			this->score = Score(0, 0, 0);
		}
    };
}