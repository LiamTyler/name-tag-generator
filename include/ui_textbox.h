#pragma once

#include "include/ui_widget.h"

namespace UI {
	class Textbox : public Widget {
	public:
		explicit Textbox(UIManager* manager);
		Textbox(UIManager* manager, const std::string& str);

		void Render() const override;

		std::string getText() const { return text_; }
		glm::vec4 getColor() const { return color_; }

		void setText(const std::string& text);
		void setColor(const glm::vec4& color);

	protected:
		std::string text_;
		glm::vec4 color_;
	};

}  // namespace UI