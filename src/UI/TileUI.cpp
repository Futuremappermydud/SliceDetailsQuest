#include "UI/TileUI.hpp"
#include "Sprites.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/UI/ColorBlock.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "main.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace UnityEngine::Events;
using namespace UnityEngine::UI;

DEFINE_TYPE(SliceDetails, TileUIController);

#define MakeDelegate(DelegateType, object, varName) (il2cpp_utils::MakeDelegate<DelegateType>(classof(DelegateType), object, varName))

void SliceDetails::TileUIController::Open(UnityEngine::Transform* parent)
{
    get_gameObject()->SetActive(true);
    get_transform()->SetParent(parent, false);
}

void SliceDetails::TileUIController::Close()
{
    get_gameObject()->SetActive(false);
}

void SliceDetails::TileUIController::Init(UnityEngine::Transform* parent)
{
    get_transform()->SetParent(parent, false);
    getLogger().info("%s", to_utf8(csstrtostr(parent->get_name())).c_str());
    getLogger().info("%s", to_utf8(csstrtostr(parent->get_parent()->get_name())).c_str());
    getLogger().info("%s", "mainUIStart");
    auto yeye = QuestUI::BeatSaberUI::CreateFloatingScreen(Vector2(150.0f, 120.0f), Vector3(-0.1f, 3.8f, 2.5f), Vector3(-30.0f, 0.0f, 0.0f), 0.0f, false, false, 2);
    yeye->get_transform()->SetParent(this->get_transform());

    Sprite* bloqSprite = QuestUI::BeatSaberUI::Base64ToSprite(spr_bloq_base64);
    auto vertfuuck = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(yeye->get_transform());
    vertfuuck->set_childControlHeight(true);

    Sprite* arrowSprite = QuestUI::BeatSaberUI::Base64ToSprite(spr_arrow_base64);

    static auto backgroundName = il2cpp_utils::createcsstr("round-rect-panel", il2cpp_utils::StringType::Manual);
    auto fog = QuestUI::ArrayUtil::First(Resources::FindObjectsOfTypeAll<Material*>(), [](Material* x) { return to_utf8(csstrtostr(x->get_name())) == "UIFogBG"; });

    auto parentHoriz = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(vertfuuck->get_transform());
    parentHoriz->set_padding(RectOffset::New_ctor(4, 4, 4, 4)); 
    auto a = parentHoriz->get_gameObject()->AddComponent<ContentSizeFitter*>();
    a->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    a->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
    auto bg = parentHoriz->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
    bg->ApplyBackgroundWithAlpha(backgroundName, 0.5f);
    bg->background->set_material(fog);

    auto column = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(parentHoriz->get_transform());
    
    auto mat_UINoGlow = QuestUI::ArrayUtil::First(Resources::FindObjectsOfTypeAll<Material*>(), [](Material* x) { return to_utf8(csstrtostr(x->get_name())) == "UINoGlow"; });

    Transform* rowParent;
    Transform* gridParent;
    for (int i = 0; i < 18; i++)
    {
        if (i % 9 == 0) {
			auto shi = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(column->get_transform());
            shi->set_padding(RectOffset::New_ctor(4, 4, 4, 4)); 
            gridParent = shi->get_transform();
            shi->set_spacing(1);

            auto row = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(gridParent->get_transform());
            row->set_childControlWidth(true);
            auto a2 = row->get_gameObject()->AddComponent<ContentSizeFitter*>();
            a2->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
            a2->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
            rowParent = row->get_transform();
            row->set_spacing(1);
		}
		if (i % 3 == 0) {
			auto row = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(gridParent->get_transform());
            row->set_childControlWidth(true);
            auto a2 = row->get_gameObject()->AddComponent<ContentSizeFitter*>();
            a2->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
            a2->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
            rowParent = row->get_transform();
            row->set_spacing(1);
		}
        auto image = QuestUI::BeatSaberUI::CreateImage(rowParent->get_transform(), bloqSprite, Vector2(0, 0), Vector2(10, 10));
        auto noteUI = image->get_gameObject()->AddComponent<NoteUI*>();
        ColorType colorType = ColorType(i >= 9 ? 1 : 0);
        auto cutDirection = OrderedNoteCutDirection(i % 9);
        noteUI->Init(cutDirection, colorType);

        if (colorType == ColorType::ColorA)
		    leftNoteTiles.push_back(noteUI->get_gameObject());
	    else if (colorType == ColorType::ColorB)
            rightNoteTiles.push_back(noteUI->get_gameObject());
    }
}

void SliceDetails::TileUIController::SelectTile(int index)
{
    
}