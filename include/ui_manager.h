#pragma once

#include <nanogui/nanogui.h>
#include <ft2build.h>
#include FT_FREETYPE_H

// #include "include/ui_widget.h"
#include "include/shader.h"
#include "glm/glm.hpp"

namespace UI {
	class Widget;

	struct Character {
		GLuint TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		GLuint Advance;
	};

	class UIManager {

	public:
		UIManager();
		~UIManager();

		bool Init(
			const std::string& font,
			int font_size,
			const std::string& text_vert,
			const std::string& text_frag,
			const std::string& image_vert,
			const std::string& image_frag
		);

		void AddWidget(Widget* w);
		void RemoveWidget(Widget* w);

		void Render();
		
		bool ChangeFont(const std::string& font, int size);

		void SetProjection(float min_x, float max_x, float min_y,
			float max_y, float min_z, float max_z);
		void SetProjection(const glm::mat4& P);

		Progression::Shader& getImageShader() { return imageShader_; }
		GLuint getImageVAO() const { return imageVAO_; }

		Progression::Shader& getTextShader() { return textShader_; }
		GLuint getTextVAO() const { return textVAO_; }
		GLuint getTextVBO() const { return textVBO_; }


		std::string GetFont() const { return font_; }
		int GetFontSize() const { return font_size_; }
		const Character& GetCharacter(char c) { return characters_[c]; }
		glm::mat4 getProjection() const { return projection_; }

	private:
		bool LoadFont();

		Progression::Shader textShader_;
		Progression::Shader imageShader_;

		std::vector<Widget*> widgets_;

		glm::mat4 projection_;

		FT_Library ft_;
		FT_Face face_;
		std::string font_;
		int font_size_;
		// Character characters_[128];
		std::unordered_map<char, Character> characters_;

		GLuint textVAO_;
		GLuint textVBO_;
		GLuint imageVAO_;
		GLuint imageVBO_;
	};
}  // namespace UI
