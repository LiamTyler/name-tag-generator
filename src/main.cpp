#include "starter.h"
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

struct Character {
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	//glm::vec4 Verts;
	GLuint Advance;
};

std::unordered_map<GLchar, Character> characters;
GLuint VAO, VBO;

void RenderText(Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	if (!text.length())
		return;
	// Activate corresponding render state	
	//s.Enable();
	glUniform3f(s["textColor"], color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	//glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	//glBindVertexArray(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
}

int SW = 800;
int SH = 600;

int main(int arc, char** argv) {
	Window window("Starter Project", SW, SH);
	Shader shader(
		"Text Shader",
		"../shaders/text.vert",
		"../shaders/text.frag");

	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		cout << "Could not init the FT library" << std::endl;
		return 1;
	}
	FT_Face face;
	if (FT_New_Face(ft, "../fonts/arial.ttf", 0, &face)) {
		std::cout << "failed to load the font" << std::endl;
		return 1;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "Failed to load the glyph: " << (int)c << " = " << (char)c << std::endl;
			continue;
		}
		float w = face->glyph->bitmap.width;
		float h = face->glyph->bitmap.rows;
		float bx = face->glyph->bitmap_left;
		float by = face->glyph->bitmap_top;
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
			face->glyph->bitmap.buffer
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(w, h),
			glm::ivec2(bx, by),
			//glm::vec4(-w / 2, - h / 2)
			face->glyph->advance.x
		};
		characters[c] = character;
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 projection = glm::ortho(0.0f, (float) SW, 0.0f, (float)SH);


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(shader["vertex"]);
	glVertexAttribPointer(shader["vertex"], 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);


    // window.SetRelativeMouse(true);
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        window.StartFrame();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_p:
                        break;
                    case SDLK_SPACE:
					{
						glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
						Image im(SW, SH);
						float* pixels = new float[4 * SW * SH];
						glReadPixels(0, 0, SW, SH, GL_RGBA, GL_FLOAT, pixels);
						int p = 0;
						for (int r = 0; r < SH; r++) {
							for (int c = 0; c < SW; c++) {
								im.SetPixel(SH - 1 - r, c, glm::vec4(pixels[p], pixels[p + 1], pixels[p + 2], pixels[3]));
								p += 4;
							}
						}
						im.SaveImage("test2.jpg");
						delete[] pixels;
					}
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        break;
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                float dx = -event.motion.xrel;
                float dy = -event.motion.yrel;
            }
        }

        float dt = window.GetDT();

        shader.Enable();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniformMatrix4fv(shader["projection"], 1, GL_FALSE, glm::value_ptr(projection));

		RenderText(shader, "BAE BOO!", 250, 300, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		RenderText(shader, "I got text working :)", 225, 250, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));


        window.EndFrame();
    }

    return 0;
}
