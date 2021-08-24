#include "UI/MainUIController.hpp"
#include "UI/TileUI.hpp"
#include "SliceProcessor.hpp"
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

DEFINE_TYPE(SliceDetails, MainUIController);

#define MakeDelegate(DelegateType, object, varName) (il2cpp_utils::MakeDelegate<DelegateType>(classof(DelegateType), object, varName))

void SliceDetails::MainUIController::Open(UnityEngine::Transform* parent)
{
    getLogger().info("%s", "mainUIOpen");
    get_gameObject()->SetActive(true);
    get_transform()->SetParent(parent, false);
    getLogger().info("%s", to_utf8(csstrtostr(parent->get_name())).c_str());
    getLogger().info("%s", to_utf8(csstrtostr(parent->get_parent()->get_name())).c_str());
    tileUIInstance->get_gameObject()->SetActive(false);
}

void SliceDetails::MainUIController::Close()
{
    get_gameObject()->SetActive(false);
    tileUIInstance->Close();
}

void SliceDetails::MainUIController::SetTileScores()
{
    for (int i = 0; i < noteGridTiles.size(); i++) {
		TMPro::TextMeshProUGUI* text = noteGridTiles.at(i)->get_transform()->GetComponentInChildren<TMPro::TextMeshProUGUI*>();
		if (SliceProcessorInstance->tiles.at(i).atLeastOneNote)
			text->set_text(System::String::Format(il2cpp_utils::createcsstr("{0:0.00}"), il2cpp_utils::createcsstr(std::to_string(SliceProcessorInstance->tiles.at(i).scoreAverage))));
		else
			text->set_text(il2cpp_utils::createcsstr(""));
	}
}

void SliceDetails::MainUIController::Init(UnityEngine::Transform* parent)
{
    get_transform()->SetParent(parent, false);
    getLogger().info("%s", to_utf8(csstrtostr(parent->get_name())).c_str());
    getLogger().info("%s", to_utf8(csstrtostr(parent->get_parent()->get_name())).c_str());
    getLogger().info("%s", "mainUIStart");
    auto yeye = QuestUI::BeatSaberUI::CreateFloatingScreen(Vector2(150.0f, 120.0f), Vector3(0.0f, 2.5f, 3.0f), Vector3(-30.0f, 0.0f, 0.0f), 0.0f, false, false, 2);
    yeye->get_transform()->SetParent(this->get_transform());

    Sprite* bloqSprite = QuestUI::BeatSaberUI::Base64ToSprite(spr_bloq_base64);
    auto vertfuuck = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(yeye->get_transform());
    vertfuuck->set_childControlHeight(true);

    GameObject* swagshit = GameObject::New_ctor(il2cpp_utils::createcsstr("Slice Details Tile UI"));
    SliceDetails::TileUIController* d = swagshit->AddComponent<SliceDetails::TileUIController*>();
    tileUIInstance = d;
    tileUIInstance->Init(get_transform()->get_parent());
    getLogger().info("%p", tileUIInstance);
    swagshit->SetActive(false);

    static auto backgroundName = il2cpp_utils::createcsstr("round-rect-panel", il2cpp_utils::StringType::Manual);
    auto fog = QuestUI::ArrayUtil::First(Resources::FindObjectsOfTypeAll<Material*>(), [](Material* x) { return to_utf8(csstrtostr(x->get_name())) == "UIFogBG"; });

    //tiles
    auto parentHoriz = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(vertfuuck->get_transform());
    parentHoriz->set_padding(RectOffset::New_ctor(4, 4, 4, 4)); 
    auto a = parentHoriz->get_gameObject()->AddComponent<ContentSizeFitter*>();
    a->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    a->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
    auto bg = parentHoriz->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
    bg->ApplyBackgroundWithAlpha(backgroundName, 0.5f);
    bg->background->set_material(fog);

    auto column = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(parentHoriz->get_transform());
    
    auto mat_UINoGlow = QuestUI::ArrayUtil::First(Resources::FindObjectsOfTypeAll<Material*>(), [](Material* x) { return to_utf8(csstrtostr(x->get_name())) == "UINoGlow"; });

    int index = 0;
    for (int i = 0; i < 3; i++)
    {
        auto row = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(column->get_transform());
        row->set_childControlWidth(true);
        auto a2 = row->get_gameObject()->AddComponent<ContentSizeFitter*>();
        a2->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
        a2->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
        for (int i = 0; i < 4; i++)
        {
            auto image = QuestUI::BeatSaberUI::CreateImage(row->get_transform(), bloqSprite, Vector2(0, 0), Vector2(10, 10));
            image->set_material(mat_UINoGlow);
            image->set_color(Color(0.58f, 0.58f, 0.58f, 1));
            auto layoutThingFucker = image->get_gameObject()->AddComponent<LayoutElement*>();
            layoutThingFucker->set_preferredHeight(10);
            layoutThingFucker->set_preferredWidth(10);  
            auto a2 = image->get_gameObject()->AddComponent<ContentSizeFitter*>();
            a2->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
            a2->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
            auto buttlolol = image->get_gameObject()->AddComponent<UnityEngine::UI::Button*>();
            std::function<void()> fun = [index, this](){
                tileUIInstance->Open(get_transform()->get_parent());
                tileUIInstance->SelectTile(index);
            };
            buttlolol->get_onClick()->AddListener(il2cpp_utils::MakeDelegate<UnityAction*>(classof(UnityAction*), fun));
            ColorBlock colorVar = buttlolol->get_colors();
            colorVar.set_normalColor(Color(0.80f, 0.80f, 0.80f, 1));
            colorVar.set_highlightedColor(Color(0.9f, 0.9f, 0.9f, 1));
            colorVar.set_fadeDuration(0.0f);
            buttlolol->set_colors(colorVar);
            auto sus = QuestUI::BeatSaberUI::CreateText(image->get_transform(), "", true, Vector2(0, 0), Vector2(10, 10));
            sus->set_alignment(TMPro::TextAlignmentOptions::Center);
            sus->set_fontSize(3);
            index++;
            noteGridTiles.push_back(image->get_gameObject());
        }
    }
    //SetTileScores();
}