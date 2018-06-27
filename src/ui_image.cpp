#include "include/ui_image.h"
#include "include/ui_manager.h"

namespace UI {
	Image::Image(UIManager* manager) :
		Widget(manager),
		texture_()
	{
	}

	Image::Image(UIManager* manager, const std::string& filename) :
		Widget(manager),
		texture_(filename)
	{
		size_ = glm::vec2(texture_.GetWidth(), texture_.GetHeight());
	}

	void Image::Render() const {
		auto& shader = manager_->getImageShader();
		auto vao = manager_->getImageVAO();
		shader.Enable();
		glBindVertexArray(vao);
		glUniformMatrix4fv(shader["projection"], 1, GL_FALSE, glm::value_ptr(manager_->getProjection()));
		// glActiveTexture(GL_TEXTURE0);

		glm::vec2 effectiveSize{ scale_.x * size_.x, scale_.y * size_.y };
		
		glm::mat4 model(1);
		model = glm::translate(model, glm::vec3(position_.x, position_.y, 0));
		model = glm::rotate(model, rotation_, glm::vec3(0, 0, 1));
		model = glm::scale(model, glm::vec3(effectiveSize.x / 2, effectiveSize.y / 2, 1));
		glUniformMatrix4fv(shader["model"], 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(shader["depth"], depth_);

		glBindTexture(GL_TEXTURE_2D, texture_.GetHandle());
		glUniform1i(shader["tex"], 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Image::SetImage(const std::string& fname)
	{
		texture_ = Texture(fname);
	}

	void Image::SetImage(const ::Image& image)
	{
		texture_ = Texture(image);
	}

}  // namespace UI