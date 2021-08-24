#include "SliceProcessor.hpp"
#include "UI/TileUI.hpp"
#include "main.hpp"

using namespace GlobalNamespace;

DEFINE_TYPE(SliceDetails, SliceProcessor);

void SliceDetails::SliceProcessor::Awake()
{
    //tiles.clear();
    for (int i = 0; i < 12; i++)
    {
        tiles.push_back(Tile());
    }
    DontDestroyOnLoad(this->get_gameObject());
}

void SliceDetails::SliceProcessor::ResetProcessor()
{
    //ready = false;
    //for (int i = 0; i < 12; i++)
    //{
    //    //tiles.push_back(Tile());
    //    for (int j = 0; j < 18; j++) {
    //        tiles[i].tileNoteInfos = std::vector<std::vector<NoteInfo>>();
	//		tiles[i].tileNoteInfos.push_back(std::vector<NoteInfo>());
	//	}
    //}
    
}

void SliceDetails::SliceProcessor::ProcessSlices(std::vector<NoteInfo> noteInfos)
{
    ResetProcessor();

    for (int i = 0; i < noteInfos.size(); i++) {
        auto ni = noteInfos[i];
        int noteDirection;
        switch (ni.noteData->cutDirection) {
            case NoteCutDirection::Down:
                noteDirection = (int)OrderedNoteCutDirection::Down;
                break;
            case NoteCutDirection::Up:
                noteDirection = (int)OrderedNoteCutDirection::Up;
                break;
            case NoteCutDirection::Left:
                noteDirection = (int)OrderedNoteCutDirection::Left;
                break;
            case NoteCutDirection::Right:
                noteDirection = (int)OrderedNoteCutDirection::Right;
                break;
            case NoteCutDirection::DownLeft:
                noteDirection = (int)OrderedNoteCutDirection::DownLeft;
                break;
            case NoteCutDirection::DownRight:
                noteDirection = (int)OrderedNoteCutDirection::DownRight;
                break;
            case NoteCutDirection::UpLeft:
                noteDirection = (int)OrderedNoteCutDirection::UpLeft;
                break;
            case NoteCutDirection::UpRight:
                noteDirection = (int)OrderedNoteCutDirection::UpRight;
                break;
            case NoteCutDirection::Any:
                noteDirection = (int)OrderedNoteCutDirection::Any;
                break;
        }
		int noteColor = (int)ni.noteData->colorType;
		int tileNoteDataIndex = noteColor * 9 + noteDirection;
		tiles[ni.noteIndex].tileNoteInfos[tileNoteDataIndex].push_back(ni);
	}

    for (int i = 0; i < 12; i++) {
		tiles[i].CalculateAverages();
	}

    ready = true;
}