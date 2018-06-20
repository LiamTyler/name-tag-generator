#pragma once

#include "starter.h"

namespace UI {
	class Image {
		friend class UIManager;
	public:
		Image();
		Image(const std::string& filename);

		glm::vec2 GetEffectiveSize() const;

		glm::ivec2 position;
		glm::vec2 scale;
		float rotation;
		float depth;
		void Render(Shader& shader) const;


	private:
		Texture texture_;
	};
}