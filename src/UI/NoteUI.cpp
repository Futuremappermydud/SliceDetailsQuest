#include "UI/NoteUI.hpp"
#include "main.hpp"
#include "Sprites.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/UI/ColorBlock.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/ColorSchemesSettings.hpp"
#include "GlobalNamespace/ColorScheme.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace HMUI;
using namespace UnityEngine::Events;
using namespace UnityEngine::UI;

DEFINE_TYPE(SliceDetails, NoteUI);

void SliceDetails::NoteUI::Init(OrderedNoteCutDirection cutDirection, GlobalNamespace::ColorType colorType)
{
    //Sprite* bloqSprite = QuestUI::BeatSaberUI::Base64ToSprite(spr_bloq_base64);
    Sprite* arrowSprite = QuestUI::BeatSaberUI::Base64ToSprite(spr_arrow_base64);
    auto mat_UINoGlow = QuestUI::ArrayUtil::First(Resources::FindObjectsOfTypeAll<Material*>(), [](Material* x) { return to_utf8(csstrtostr(x->get_name())) == "UINoGlow"; });

    _backgroundImage = GetComponent<UnityEngine::UI::Image*>();
    _backgroundImage->set_material(mat_UINoGlow);
    _backgroundImage->set_color(Color(0.58f, 0.58f, 0.58f, 1));
    auto layoutThingFucker = _backgroundImage->get_gameObject()->AddComponent<LayoutElement*>();
    layoutThingFucker->set_preferredHeight(10);
    layoutThingFucker->set_preferredWidth(10);  
    auto a2 = _backgroundImage->get_gameObject()->AddComponent<ContentSizeFitter*>();
    a2->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    a2->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
    _directionArrowImage = reinterpret_cast<ImageView*>(QuestUI::BeatSaberUI::CreateImage(_backgroundImage->get_transform(), arrowSprite, Vector2(0, 0), Vector2(10, 10)));
    float noteRotation;

	ColorScheme* colorScheme = Resources::FindObjectsOfTypeAll<GlobalNamespace::PlayerDataModel*>()->get(0)->playerData->colorSchemesSettings->GetSelectedColorScheme();
	if (colorType == ColorType::ColorA)
		_noteColor = colorScheme->saberAColor;
	else if (colorType == ColorType::ColorB)
		_noteColor = colorScheme->saberBColor;

    switch (cutDirection) {
	    case OrderedNoteCutDirection::Down:
	    	noteRotation = 0.0f;
	    	break;
	    case OrderedNoteCutDirection::Up:
	    	noteRotation = 180.0f;
	    	break;
	    case OrderedNoteCutDirection::Left:
	    	noteRotation = 270.0f;
	    	break;
	    case OrderedNoteCutDirection::Right:
	    	noteRotation = 90.0f;
	    	break;
	    case OrderedNoteCutDirection::DownLeft:
	    	noteRotation = 315.0f;
	    	break;
	    case OrderedNoteCutDirection::DownRight:
	    	noteRotation = 45.0f;
	    	break;
	    case OrderedNoteCutDirection::UpLeft:
	    	noteRotation = 225.0f;
	    	break;
	    case OrderedNoteCutDirection::UpRight:
	    	noteRotation = 135.0f;
	    	break;
	    case OrderedNoteCutDirection::Any:
	    	noteRotation = 0.0f;
	    	_directionArrowImage->set_sprite(QuestUI::BeatSaberUI::Base64ToSprite(spr_dot_base64));
		break;
	}

    _backgroundImage->get_transform()->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, noteRotation)));
}

void SliceDetails::NoteUI::SetData(float angle, float offset, Score score)
{
	if (angle == 0.0f && offset == 0.0f) {
		_backgroundImage->set_color(Color::get_gray());
		_cutArrowImage->get_gameObject()->SetActive(false);
		//_cutDistanceImage->get_gameObject()->SetActive(false);
		_directionArrowImage->set_color(Color(0.8f, 0.8f, 0.8f));
		//_noteHoverHint.text = "";
	} else {
		_backgroundImage->set_color(_noteColor);
		_cutArrowImage->get_gameObject()->SetActive(true);
		//_cutDistanceImage->get_gameObject()->SetActive(true);
		_cutGroup->get_transform()->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, angle - _noteRotation)));
		//if (Plugin.Settings.TrueCutOffsets) {
			_cutArrowImage->get_transform()->set_localPosition(Vector3(offset * 20.0f, 0.0f, 0.0f));
			//_cutDistanceImage.transform.localScale = new Vector2(-offset * 1.33f, 1.0f);
		//} else {
		//	_cutArrowImage->get_transform()->set_localPosition(Vector3(offset * (30.0f + score.Offset), 0.0f, 0.0f));
		//	//_cutDistanceImage.transform.localScale = new Vector2(-offset * (1.995f + score.Offset*0.0665f), 1.0f);
		//}
		_directionArrowImage->set_color(Color::get_white());
		//_noteHoverHint.text = "Average score - " + String.Format("{0:0.00}", score.TotalScore) + " (" + String.Format("{0:0.00}", score.PreSwing) + ", " + String.Format("{0:0.00}", score.PostSwing) + ", " + String.Format("{0:0.00}", score.Offset) + ")";
	}
}