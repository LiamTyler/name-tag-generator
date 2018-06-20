#include "include/ui_image.h"

namespace UI {
	Image::Image() :
		position(glm::ivec2(0, 0)),
		scale(glm::vec2(1, 1)),
		rotation(0),
		depth(0)
	{
	}

	Image::Image(const std::string& filename) :
		position(glm::ivec2(0, 0)),
		scale(glm::vec2(1, 1)),
		rotation(0),
		depth(0),
		texture_(filename)
	{
	}

	glm::vec2 Image::GetEffectiveSize() const {
		return scale * glm::vec2(texture_.GetWidth(), texture_.GetHeight());
	}

	void Image::Render(Shader& shader) const {
		glm::vec2 size = scale * glm::vec2(texture_.GetWidth(), texture_.GetHeight());

		GLfloat vertices[6][4] = {
			{ -1, -1, 0.0, 1.0 },
			{ -1, 1,  0.0, 0.0 },
			{ 1, -1,  1.0, 1.0 },

			{ -1, 1, 0.0, 0.0 },
			{ 1, -1, 1.0, 1.0 },
			{ 1, 1,	 1.0, 0.0 }
		};
		glm::mat4 model(1);
		model = glm::translate(model, glm::vec3(position.x, position.y, 0));
		model = glm::rotate(model, rotation, glm::vec3(0, 0, 1));
		model = glm::scale(model, glm::vec3(size.x / 2, size.y / 2, 1));
		glUniformMatrix4fv(shader["model"], 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(shader["depth"], depth);

		glBindTexture(GL_TEXTURE_2D, texture_.GetHandle());
		glUniform1i(shader["tex"], 0);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glDrawArrays(GL_TRIANGLES, 0, 6);

	}
}