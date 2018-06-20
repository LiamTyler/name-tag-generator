#include "starter.h"

#include "include/ui_image.h"
#include "include/ui_manager.h"

using namespace std;

const int SW = 800;
const int SH = 600;

int main(int arc, char** argv) {
	Window window("Starter Project", SW, SH);

	UI::UIManager uiManager;
	bool ret = uiManager.Init(
		"../fonts/arial.ttf",
		48,
		"../shaders/text.vert",
		"../shaders/text.frag",
		"../shaders/ui_image.vert",
		"../shaders/ui_image.frag"
	);
	if (!ret) {
		cout << "ui manger failed to init" << endl;
		return 1;
	}

	UI::Image uimage("C:/Users/Tyler/Pictures/pikachu.png");
	uimage.scale = glm::vec2(.5, .5);
	uimage.position = glm::ivec2(200, 200);
	uimage.depth = -2;

	glm::mat4 projection = glm::ortho<float>(0.0f, SW, 0.0f, SH, -10, 10);
	uiManager.SetProjection(projection);

    // window.SetRelativeMouse(true);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		uiManager.RenderImage(uimage);

		uiManager.RenderText("BAE BOO!", 350, 300, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		uiManager.RenderText("I got text working :)", 255, 250, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));



        window.EndFrame();
    }

    return 0;
}
