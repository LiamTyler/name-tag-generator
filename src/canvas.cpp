#include "include/canvas.h"
#include <iostream>


UICanvas::UICanvas(Widget *parent) : GLCanvas(parent) {
	const std::string root = "C:/Users/Tyler/Documents/name-tag-generator/";

	uiManager_ = new UI::UIManager;
	bool ret = uiManager_->Init(
		root + "fonts/arial.ttf",
		48,
		root + "shaders/text.vert",
		root + "shaders/text.frag",
		root + "shaders/ui_image.vert",
		root + "shaders/ui_image.frag"
	);
	if (!ret) {
		std::cout << "ui manger failed to init" << std::endl;
		return;
	}


	UI::Image* uimage = new UI::Image(uiManager_, "C:/Users/Tyler/Pictures/pikachu.png");
	std::cout << "scale 1: " << uimage->getScale().x << " " << uimage->getScale().y << std::endl;
	uimage->setScale(glm::vec2(.5f, .5f));
	std::cout << "scale 2: " << uimage->getScale().x << " " << uimage->getScale().y << std::endl;
	uimage->setPositionType(UI::POSITION_TYPE::ABSOLUTE);
	uimage->setPosition(glm::ivec2(200, 200));
	uimage->setDepth(-2);

	UI::Textbox* tb1 = new UI::Textbox(uiManager_, "BAE BOO!");
	tb1->setPosition({ 150, 500 });
	tb1->setColor({ .5, .8, .2, 1.0 });


	UI::Textbox* tb2 = new UI::Textbox(uiManager_, "I got a bunch working :)");
	tb2->setPosition({ 150, 350 });
	tb2->setColor({ .3, .7, .9, 1.0 });
	tb2->setDepth(-1);

	const int W = 1280 - 200;
	const int H = 720;
	setFixedSize(nanogui::Vector2i(W, H));
	glm::mat4 projection = glm::ortho<float>(0.0f, W, 0.0f, H, -10, 10);
	uiManager_->SetProjection(projection);
	
}

UICanvas::~UICanvas() {
	if (uiManager_)
		delete uiManager_;
}

void UICanvas::drawGL() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	uiManager_->Render();
}