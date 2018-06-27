#pragma once

#include "starter.h"
#include "include/ui_widget.h"

namespace UI {

	class Image : public Widget {
	public:
		explicit Image(UIManager* manager);
		Image(UI::UIManager* manager, const std::string& filename);

		void Render() const override;

		void SetImage(const std::string& fname);
		void SetImage(const ::Image& image);

	private:
		Texture texture_;
	};

}  // namespace UI