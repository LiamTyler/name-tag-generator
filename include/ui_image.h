#pragma once

#include "include/ui_widget.h"
#include "include/image.h"
#include "include/texture.h"

namespace UI {

	class Image : public Widget {
	public:
		explicit Image(UIManager* manager);
		Image(UI::UIManager* manager, const std::string& filename);

		void Render() const override;

		void SetImage(const std::string& fname);
		void SetImage(const Progression::Image& image);

	private:
		Progression::Texture texture_;
	};

}  // namespace UI
