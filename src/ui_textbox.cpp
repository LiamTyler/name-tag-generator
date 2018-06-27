#include "include/ui_textbox.h"
#include "include/ui_manager.h"

namespace UI {
	Textbox::Textbox(UIManager* manager) :
		Widget(manager),
		text_(""),
		color_(glm::vec4(1))
	{
	}

	Textbox::Textbox(UIManager* manager, const std::string& str) :
		Widget(manager),
		text_(str),
		color_(glm::vec4(1))
	{
	}

	void Textbox::Render() const {
		if (!text_.length())
			return;
		auto& shader = manager_->getTextShader();
		auto vao = manager_->getTextVAO();
		auto vbo = manager_->getTextVBO();

		shader.Enable();
		glUniformMatrix4fv(shader["projection"], 1, GL_FALSE, glm::value_ptr(manager_->getProjection()));
		glUniform3f(shader["textColor"], color_.x, color_.y, color_.z);
		glUniform1f(shader["depth"], depth_);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao);

		float x = position_.x;
		float y = position_.y;

		std::string::const_iterator c;
		for (c = text_.begin(); c != text_.end(); c++)
		{
			const auto& ch = manager_->GetCharacter(*c);

			float xpos = x + ch.Bearing.x * scale_.x;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * scale_.y;

			float w = ch.Size.x * scale_.x;
			float h = ch.Size.y * scale_.y;
			float vertices[6][4] = {
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			glUniform1i(shader["tex"], 0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			glDrawArrays(GL_TRIANGLES, 0, 6);
			x += (ch.Advance >> 6) * scale_.x;
		}
	}

	void Textbox::setText(const std::string& text) {
		text_ = text;
	}

	void Textbox::setColor(const glm::vec4& color) {
		color_ = color;
	}

}  // namespace UI