#include "include/ui_widget.h"
#include "include/ui_manager.h"

namespace UI {

	Widget::Widget(UIManager* manager, const glm::vec2& pos,
		const glm::vec2& scale, float rot, const glm::vec2& size, float depth,
		POSITION_TYPE posType, SCALE_TYPE scaleType, ALIGNMENT alignment,
		bool visible) :
		manager_(manager),
		position_(pos),
		scale_(scale),
		rotation_(rot),
		size_(size),
		depth_(depth),
		positionType_(posType),
		scaleType_(scaleType),
		alignment_(alignment),
		isVisible_(visible)
	{
		if (manager_)
			manager_->AddWidget(this);
	}

	bool operator<(const Widget& w1, const Widget& w2) {
		return w1.depth_ < w2.depth_;
	}

	void Widget::setPosition(const glm::vec2& pos) {
		position_ = pos;
	}

	void Widget::setScale(const glm::vec2& scale) {
		scale_ = scale;
	}

	void Widget::setRotation(float rot) {
		rotation_ = rot;
	}

	void Widget::setSize(const glm::vec2& s) {
		size_ = s;
	}

	void Widget::setDepth(float depth) {
		depth_ = depth;
	}

	void Widget::setPositionType(POSITION_TYPE p) {
		positionType_ = p;
	}

	void Widget::setScaleType(SCALE_TYPE s) {
		scaleType_ = s;
	}

	void Widget::setAlignment(ALIGNMENT a) {
		alignment_ = a;
	}

	void Widget::setVisible(bool b) {
		isVisible_ = b;
	}

}  // namespace UI