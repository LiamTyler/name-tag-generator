#include <algorithm>
#include "include/ui_manager.h"
#include "include/ui_widget.h"

namespace UI {
	UIManager::UIManager() :
		font_(""),
		font_size_(-1),
		textVAO_(-1),
		textVBO_(-1),
		imageVAO_(-1),
		imageVBO_(-1)
	{
		
	}

	UIManager::~UIManager() {
		FT_Done_FreeType(ft_);
	}

	bool UIManager::Init(
		const std::string& font,
		int size,
		const std::string& text_vert,
		const std::string& text_frag,
		const std::string& image_vert,
		const std::string& image_frag)
	{
		// init the text stuff
		font_ = font;
		font_size_ = size;
		if (FT_Init_FreeType(&ft_)) {
			std::cout << "Could not init the FT library" << std::endl;
			return false;
		}
		if (!LoadFont()) {
			std::cout << "Failed to load font" << std::endl;
			return false;
		}

		GLfloat vertices[6][4] = {
			{ -1, -1, 0.0, 1.0 },
			{ -1, 1,  0.0, 0.0 },
			{ 1, -1,  1.0, 1.0 },

			{ -1, 1, 0.0, 0.0 },
			{ 1, -1, 1.0, 1.0 },
			{ 1, 1,	 1.0, 0.0 }
		};

		textShader_.AttachShaderFromFile(GL_VERTEX_SHADER, text_vert);
		textShader_.AttachShaderFromFile(GL_FRAGMENT_SHADER, text_frag);
		if (!textShader_.CreateAndLinkProgram())
			return false;
		textShader_.AutoDetectVariables();

		glGenVertexArrays(1, &textVAO_);
		glGenBuffers(1, &textVBO_);
		glBindVertexArray(textVAO_);
		glBindBuffer(GL_ARRAY_BUFFER, textVBO_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(textShader_["vertex"]);
		glVertexAttribPointer(textShader_["vertex"], 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

		// init the image stuff
		imageShader_.AttachShaderFromFile(GL_VERTEX_SHADER, image_vert);
		imageShader_.AttachShaderFromFile(GL_FRAGMENT_SHADER, image_frag);
		if (!imageShader_.CreateAndLinkProgram())
			return false;
		imageShader_.AutoDetectVariables();

		glGenVertexArrays(1, &imageVAO_);
		glGenBuffers(1, &imageVBO_);
		glBindVertexArray(imageVAO_);
		glBindBuffer(GL_ARRAY_BUFFER, imageVBO_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(imageShader_["vertex"]);
		glVertexAttribPointer(imageShader_["vertex"], 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

		return true;
	}

	bool UIManager::LoadFont() {
		if (FT_New_Face(ft_, font_.c_str(), 0, &face_)) {
			std::cout << "failed to load the font: " << font_ << std::endl;
			return false;
		}
		FT_Set_Pixel_Sizes(face_, 0, font_size_);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (GLubyte c = 0; c < 128; c++) {
			if (FT_Load_Char(face_, c, FT_LOAD_RENDER)) {
				std::cout << "Failed to load the glyph: " << (int)c << " = " << (char)c << std::endl;
				continue;
			}
			auto w = face_->glyph->bitmap.width;
			auto h = face_->glyph->bitmap.rows;
			auto bx = face_->glyph->bitmap_left;
			auto by = face_->glyph->bitmap_top;
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				w,
				h,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face_->glyph->bitmap.buffer
			);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character = {
				texture,
				glm::ivec2(w, h),
				glm::ivec2(bx, by),
				face_->glyph->advance.x
			};
			characters_[c] = character;
		}
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		FT_Done_Face(face_);
		return true;
	}

	void UIManager::AddWidget(Widget* w) {
		if (w != nullptr)
			widgets_.push_back(w);
	}

	void UIManager::RemoveWidget(Widget* w) {
		const auto& e = std::find(widgets_.begin(), widgets_.end(), w);
		if (e != widgets_.end())
			widgets_.erase(e);
	}

	void UIManager::Render() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		std::sort(widgets_.begin(), widgets_.end(), [](const Widget* w1, const Widget* w2) -> bool { return *w1 < *w2; });
		for (const auto& w : widgets_) {
			if (w->isVisible()) {
				w->Render();
				std::cout << w->getDepth() << " ";
			}
		}
		std::cout << std::endl;
		glDisable(GL_BLEND);
	}

	// TODO: Delete the old font
	bool UIManager::ChangeFont(const std::string& font, int size) {
		font_ = font;
		font_size_ = size;
		return LoadFont();
	}

	void  UIManager::SetProjection(float min_x, float max_x, float min_y,
		float max_y, float min_z, float max_z)
	{
		SetProjection(glm::ortho(min_x, max_x, min_y, max_y, min_z, max_z));
	}

	void  UIManager::SetProjection(const glm::mat4& P) {
		projection_ = P;
	}

	/*
	void UIManager::RenderImage(const UI::Image& image) {
		imageShader_.Enable();
		glUniformMatrix4fv(imageShader_["projection"], 1, GL_FALSE, glm::value_ptr(projection_));
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(imageVAO_);
		glBindBuffer(GL_ARRAY_BUFFER, imageVBO_);
		image.Render(imageShader_);
	}
	*/
}  // namespace UI