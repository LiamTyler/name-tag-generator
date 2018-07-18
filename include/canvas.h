#pragma once

#include <nanogui/nanogui.h>
#include "include/ui_manager.h"
#include "include/ui_image.h"
#include "include/ui_textbox.h"

class UICanvas : public nanogui::GLCanvas {
public:
	explicit UICanvas(nanogui::Widget *parent);
	~UICanvas();
	void drawGL() override;

private:
	UI::UIManager* uiManager_;
};