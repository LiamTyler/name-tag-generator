#pragma once

#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace UI {

	class UIManager;

	enum class POSITION_TYPE {
		ABSOLUTE,
		RELATIVE_TO_WINDOW,

		NUM_POSITION_TYPE_OPTIONS
	};

	enum class SCALE_TYPE {
		RELATIVE_TO_WINDOW,
		RELATIVE_TO_SIZE,
		ABSOLUTE,

		NUM_SCALE_TYPE_OPTIONS
	};

	enum class ALIGNMENT {
		CENTERED,
		TOP_LEFT,

		NUM_ALIGNMENT_OPTIONS
	};

	class Widget {
	public:
		virtual ~Widget() {}

		virtual void Render() const = 0;

		friend bool operator<(const Widget& w1, const Widget& w2);

		UIManager* getManager() const { return manager_; }
		glm::vec2 getPosition() const { return position_; }
		glm::vec2 getScale() const { return scale_; }
		float getRotation() const { return rotation_; }
		glm::vec2 getSize() const { return size_; }
		float getDepth() const { return depth_; }
		POSITION_TYPE getPositionType() const { return positionType_; }
		SCALE_TYPE getScaleType() const { return scaleType_; }
		ALIGNMENT getAlignment() const { return alignment_; }
		bool isVisible() const { return isVisible_; }

		void setPosition(const glm::vec2& pos);
		void setScale(const glm::vec2& scale);
		void setRotation(float rot);
		void setSize(const glm::vec2& s);
		void setDepth(float depth);
		void setPositionType(POSITION_TYPE p);
		void setScaleType(SCALE_TYPE s);
		void setAlignment(ALIGNMENT a);
		void setVisible(bool b);

	protected:
		Widget(
			UIManager* manager = nullptr,
			const glm::vec2& pos = glm::vec2(0),
			const glm::vec2& scale = glm::vec2(1),
			float rot = 0,
			const glm::vec2& size = glm::ivec2(100),
			float depth = 0,
			POSITION_TYPE posType = POSITION_TYPE::RELATIVE_TO_WINDOW,
			SCALE_TYPE scaleType = SCALE_TYPE::RELATIVE_TO_SIZE,
			ALIGNMENT alignment = ALIGNMENT::CENTERED,
			bool visible = true);

		UIManager* manager_;
		glm::vec2 position_;
		glm::vec2 scale_;
		float rotation_;
		glm::vec2 size_;
		float depth_;
		POSITION_TYPE positionType_;
		SCALE_TYPE scaleType_;
		ALIGNMENT alignment_;
		bool isVisible_;
	};

}  // namespace UI
