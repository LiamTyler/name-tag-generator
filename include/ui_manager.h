#pragma once

#include "starter.h"
#include "include/ui_image.h"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace UI {
	class UIManager {
		struct Character {
			GLuint TextureID;
			glm::ivec2 Size;
			glm::ivec2 Bearing;
			GLuint Advance;
		};

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

		void SetParameters(float min_x, float max_x, float min_y,
			float max_y, float min_z, float max_z);
		void SetProjection(const glm::mat4& P);
		
		bool ChangeFont(const std::string& font, int size);

		void RenderText(const std::string& text, float x, float y, float scale, glm::vec3 color);
		void RenderImage(const UI::Image& image);

		std::string GetFont() const { return font_; }
		int GetFontSize() const { return font_size_; }

	private:
		bool LoadFont();

		Shader textShader_;
		Shader imageShader_;

		glm::mat4 projection_;

		FT_Library ft_;
		FT_Face face_;
		std::string font_;
		int font_size_;
		// Character characters_[128];
		std::unordered_map<GLchar, Character> characters_;

		GLuint textVAO_;
		GLuint textVBO_;
		GLuint imageVAO_;
		GLuint imageVBO_;
	};
}