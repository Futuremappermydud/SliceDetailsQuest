#include "SliceRecorder.hpp"
#include "UI/TileUI.hpp"
#include "main.hpp"
#include "SliceProcessor.hpp"
//idk
#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>

using namespace GlobalNamespace;
using namespace UnityEngine;

DEFINE_TYPE(SliceDetails, SliceRecorder);

void SliceDetails::SliceRecorder::SongEnd()
{
    ProcessSlices();
}

void SliceDetails::SliceRecorder::ctor()
{
    INVOKE_CTOR();

    _noteInfos = std::vector<NoteInfo>();
}

void SliceDetails::SliceRecorder::SongStart()
{
    SliceProcessorInstance->ResetProcessor();
}

void SliceDetails::SliceRecorder::ProcessSlices()
{
    SliceProcessorInstance->ProcessSlices(_noteInfos);
}

void SliceDetails::SliceRecorder::HandleSaberSwingRatingCounterDidFinish(ISaberSwingRatingCounter* saberSwingRatingCounter)
{
    int preSwing, postSwing, offset;
    ScoreModel::RawScoreWithoutMultiplier(saberSwingRatingCounter, _noteSwingInfos.at(saberSwingRatingCounter).cutInfo.cutDistanceToCenter, preSwing, postSwing, offset);

    _noteSwingInfos.at(saberSwingRatingCounter).score = Score(preSwing, postSwing, offset);

    _noteInfos.push_back(_noteSwingInfos.at(saberSwingRatingCounter));
	_noteSwingInfos.erase(saberSwingRatingCounter);
}

void SliceDetails::SliceRecorder::ProcessNote(GlobalNamespace::NoteController* noteController, GlobalNamespace::NoteCutInfo noteCutInfo)
{
    if (noteController == nullptr) return;

    Vector3 cutDirection = Vector3(-noteCutInfo.cutNormal.y, noteCutInfo.cutNormal.x, 0.0f);
    float cutAngle = atan2(cutDirection.y, cutDirection.x) * 57.295827f + 90.0f;

    float cutOffset = noteCutInfo.cutDistanceToCenter;
	Vector3 noteCenter = noteController->get_noteTransform()->get_position();

    if (Vector3::Dot(noteCutInfo.cutNormal, noteCutInfo.cutPoint - noteCenter) > 0.0f) {
		cutOffset = -cutOffset;
	}

    Vector2 noteGridPosition;
	noteGridPosition.y = (int)noteController->get_noteData()->noteLineLayer;
	noteGridPosition.x = noteController->get_noteData()->lineIndex;
	int noteIndex = (int)(noteGridPosition.y * 4 + noteGridPosition.x);

    NoteInfo noteInfo = NoteInfo(noteController->get_noteData(), noteCutInfo, cutAngle, cutOffset, noteGridPosition, noteIndex);

    _noteSwingInfos.insert(std::pair<GlobalNamespace::ISaberSwingRatingCounter*, NoteInfo>(noteCutInfo.swingRatingCounter, noteInfo));
}