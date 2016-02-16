#include "DIY_Level_GUI.h"
#include <ModelManager.h>

std::string IntToString(int i_);

DIY_Level_GUI::DIY_Level_GUI(Level *level_, int par_, int objectives_) 
: par(par_), objectives(objectives_), strokes(0), shotPower(0)
{
	Vec2 ParLabelLocation = Vec2(150, -50);
	Vec2 StrokeLabelLocation = ParLabelLocation + Vec2(0, -80);
	Vec2 ObjectivesLabelLocation = StrokeLabelLocation + Vec2(0, -80);

	/* GUI IMAGES */
	{
		Vec2 ShotPowerMeterLocation = Vec2(-350, 65);

		ModelManager::getInstance()->loadTexture("DIY_LEVEL_GUI_SHOT_METER", "Images/Level GUI/ShotPowerMeter.png");
		ShotPowerMeter = new GuiImage(level_, "DIY_LEVEL_GUI_SHOT_METER", ShotPowerMeterLocation + Vec2(2, 0), ScreenAnchor::BOTTOM_RIGHT);
		ShotPowerMeter->drawType = UI_DRAW_TYPE::RAINBOW;

		ModelManager::getInstance()->loadTexture("DIY_LEVEL_GUI_SHOT_FRAME", "Images/Level GUI/ShotPowerMeterFrame.png");
		ShotPowerMeterFrame = new GuiImage(level_, "DIY_LEVEL_GUI_SHOT_FRAME", ShotPowerMeterLocation, ScreenAnchor::BOTTOM_RIGHT);

		ModelManager::getInstance()->loadTexture("DIY_LEVEL_GUI_BACKGROUND", "Images/Level GUI/GUI_Background.png");
		ParBackground = new GuiImage(level_, "DIY_LEVEL_GUI_BACKGROUND", ParLabelLocation + Vec2(35, 5), ScreenAnchor::TOP_LEFT);
		StrokeBackground = new GuiImage(level_, "DIY_LEVEL_GUI_BACKGROUND", StrokeLabelLocation + Vec2(35, 5), ScreenAnchor::TOP_LEFT);
		ObjectivesBackground = new GuiImage(level_, "DIY_LEVEL_GUI_BACKGROUND", ObjectivesLabelLocation + Vec2(35, 5), ScreenAnchor::TOP_LEFT);
	}

	/* LABELS */
	{
		//Fonts
		FontManager::getInstance()->GenerateFont("DIY_LEVEL_GUI_TEXT", 40, "Font/ostrich-regular.ttf");
		FontManager::getInstance()->GenerateFont("DIY_LEVEL_GUI_COUNT", 50, "Font/ostrich-black.ttf");

		ParLabel = new Label(level_, "Par", FontManager::getInstance()->GetFont("DIY_LEVEL_GUI_TEXT"), ParLabelLocation, ScreenAnchor::TOP_LEFT, Colour::Yellow()); 
		StrokeLabel = new Label(level_, "Strokes", FontManager::getInstance()->GetFont("DIY_LEVEL_GUI_TEXT"), StrokeLabelLocation, ScreenAnchor::TOP_LEFT, Colour::Yellow());
		ObjectivesLabel = new Label(level_, "Objectives Remaining", FontManager::getInstance()->GetFont("DIY_LEVEL_GUI_TEXT"), ObjectivesLabelLocation, ScreenAnchor::TOP_LEFT, Colour::Yellow());

		ParCountLabel = new Label(level_, IntToString(par), FontManager::getInstance()->GetFont("DIY_LEVEL_GUI_COUNT"), ParLabelLocation + Vec2(175, 0), ScreenAnchor::TOP_LEFT, Colour::Yellow());
		StrokeCountLabel = new Label(level_, IntToString(strokes), FontManager::getInstance()->GetFont("DIY_LEVEL_GUI_COUNT"), StrokeLabelLocation + Vec2(175, 0), ScreenAnchor::TOP_LEFT, Colour::Yellow());
		ObjectivesCountLabel = new Label(level_, IntToString(objectives), FontManager::getInstance()->GetFont("DIY_LEVEL_GUI_COUNT"), ObjectivesLabelLocation + Vec2(175, 0), ScreenAnchor::TOP_LEFT, Colour::Yellow());
	}
}

DIY_Level_GUI::~DIY_Level_GUI()
{
}

void DIY_Level_GUI::Update(float timeStep_)
{
	ShotPowerMeter->drawPercent = shotPower;
}

void DIY_Level_GUI::SetObjectivesRemaining(int objectives_)
{
	objectives = objectives_;

	ObjectivesCountLabel->SetText(IntToString(objectives_));
}

void DIY_Level_GUI::PlayerTookAStroke(int strokeIncrement)
{
	strokes += strokeIncrement;

	StrokeCountLabel->SetText(IntToString(strokes));
}

std::string IntToString(int i_)
{
	char buffer[10];
	std::string text;

	_itoa_s(i_, buffer, 10);

	text = buffer;

	return text;
}