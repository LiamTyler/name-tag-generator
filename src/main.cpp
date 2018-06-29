#include "progression.h"

#include "include/ui_manager.h"
#include "include/ui_image.h"
#include "include/ui_textbox.h"

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

	
	UI::Image uimage(&uiManager, "C:/Users/Tyler/Pictures/pikachu.png");
	std::cout << "scale 1: " << uimage.getScale().x << " " << uimage.getScale().y << std::endl;
	uimage.setScale(glm::vec2(.5f, .5f));
	std::cout << "scale 2: " << uimage.getScale().x << " " << uimage.getScale().y << std::endl;
	uimage.setPositionType(UI::POSITION_TYPE::ABSOLUTE);
	uimage.setPosition(glm::ivec2(200, 200));
	uimage.setDepth(-2);

	UI::Textbox tb1(&uiManager, "BAE BOO!");
	tb1.setPosition({ 150, 200 });
	tb1.setColor({ .5, .8, .2, 1.0 });


	UI::Textbox tb2(&uiManager, "I got text working :)");
	tb2.setPosition({ 150, 200 });
	tb2.setColor({ .3, .7, .9, 1.0 });
	tb2.setDepth(-1);


	glm::mat4 projection = glm::ortho<float>(0.0f, SW, 0.0f, SH, -10, 10);
	uiManager.SetProjection(projection);

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
                float dx = (float) -event.motion.xrel;
                float dy = (float) -event.motion.yrel;
            }
        }

        float dt = window.GetDT();

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		uiManager.Render();


        window.EndFrame();
    }

    return 0;
}
