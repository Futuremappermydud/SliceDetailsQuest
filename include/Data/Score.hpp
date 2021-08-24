#pragma once

namespace SliceDetails
{
    struct Score
    {
        float PreSwing;
		float PostSwing;
		float Offset;
		float TotalScore()
        {
            return PreSwing + PostSwing + Offset;
        }
        Score(float preSwing, float postSwing, float offset) {
			PreSwing = preSwing;
			PostSwing = postSwing;
			Offset = offset;
		}

        Score operator + (Score obj) {
            Score res = Score(PreSwing + obj.PreSwing, PostSwing + obj.PostSwing, Offset + obj.Offset);
            return res;
        }
    };
}