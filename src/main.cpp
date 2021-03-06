#include <nanogui/nanogui.h>
#include "include/canvas.h"

using namespace std;
using namespace nanogui;

const int SW = 1280;
const int SH = 720;

int main(int arc, char** argv) {
	nanogui::init();
	Screen* screen = new Screen(Vector2i(SW, SH), "Nametag Generator");

	auto controlWindow = new Window(screen, "Controls");
	controlWindow->setPosition(Vector2i(0, 0));
	controlWindow->setFixedSize(Vector2i(200, SH));
	//controlWindow->setLayout(new BoxLayout(
	//	Orientation::Vertical,
	//	Alignment::Middle,
	//	0,   // margin
	//	10) // spacing
	//);
	controlWindow->setLayout(new GroupLayout());

	
	new Label(controlWindow, "Add Image", "sans-bold", 24);
	auto imageAdder = new Button(controlWindow, "Select Image");
	imageAdder->setCallback([&] {
		auto imagePath = file_dialog(
		{
			{ "jpg", "JPG" },
			{ "jpeg", "JPEG" },
			{ "png", "PNG" },
			{ "bmp", "BMP" },
		},
		false);

		std::cout << "Selected image: " << imagePath << std::endl;
	});

	new Label(controlWindow, "Add Texbox", "sans-bold", 24);
	auto textAdder = new TextBox(controlWindow, "");
	textAdder->setEditable(true);
	auto addTextButton = new Button(controlWindow, "Add to nametag");
	addTextButton->setCallback([&] {
		std::cout << "Adding text: " << textAdder->value() << std::endl;
	});

	UICanvas* canvas = new UICanvas(screen);
	canvas->setPosition(Vector2i(200, 0));



	screen->setVisible(true);
	screen->performLayout();

	nanogui::mainloop();

	nanogui::shutdown();
	

	
	/*

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
	*/

    return 0;
}
