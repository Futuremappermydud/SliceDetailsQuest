#pragma once
#include "GlobalNamespace/NoteCutInfo.hpp"
#include "Score.hpp"
#include "NoteInfo.hpp"
#include <vector>

namespace SliceDetails
{
    struct Tile 
    {
        std::vector<std::vector<NoteInfo>> tileNoteInfos;
        std::vector<float> angleAverages;
		std::vector<float> offsetAverages;
		std::vector<Score> scoreAverages;
        float scoreAverage = 0.0f;
        bool atLeastOneNote = false;

        void CalculateAverages() {
			angleAverages = {};
			offsetAverages = {};
			scoreAverages = {};
			scoreAverage = 0.0f;
			atLeastOneNote = false;

			for (int i = 0; i < 18; i++) {
				scoreAverages[i] = Score(0.0f, 0.0f, 0.0f);
			}

			int noteCount = 0;
			for (int i = 0; i < tileNoteInfos.size(); i++) {
				if (tileNoteInfos[i].size() > 0) {
					for(int j = 0; j < tileNoteInfos[i].size(); j++) {
						atLeastOneNote = true;
                        NoteInfo noteInfo = tileNoteInfos[i][j];
						angleAverages[i] += noteInfo.cutAngle;
						offsetAverages[i] += noteInfo.cutOffset;
                        scoreAverages[i] = Score(scoreAverages[i].PreSwing + noteInfo.score.PreSwing, scoreAverages[i].PostSwing + noteInfo.score.PostSwing, scoreAverages[i].Offset + noteInfo.score.Offset);
						scoreAverage += noteInfo.score.TotalScore();
						noteCount++;
					}
					angleAverages[i] /= tileNoteInfos[i].size();
					offsetAverages[i] /= tileNoteInfos[i].size();
                    scoreAverages[i].PreSwing /= tileNoteInfos[i].size();
                    scoreAverages[i].PostSwing /= tileNoteInfos[i].size();
                    scoreAverages[i].Offset /= tileNoteInfos[i].size();
				}
			}
			scoreAverage /= noteCount;
		}
    };
}