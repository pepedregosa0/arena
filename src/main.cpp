#define RAYGUI_IMPLEMENTATION
#include <iostream>
#include <raylib.h>
#include "raygui.h"
#include "config.h"
#include "simulation.h"
#include "utils.h"
#include "input.h"

using namespace std;

// Dibuja la simulación
void DrawSimulationMap(const SimulationMap &sim, Image &img, Texture2D &tex)
{
	// Inicializa la imagen con un color de fondo
	ImageClearBackground(&img, BLACK);
	// En cada frame, actualiza los píxeles
	for (int y = 0; y < GRID_HEIGHT; y++)
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			int type = sim.map[y][x];
			unsigned char offset = sim.colorOffset[y][x];
			switch (type) {
				case SAND: ImageDrawPixel(&img, x, y, DarkenColor(GOLD, offset)); break;
				case WATER: ImageDrawPixel(&img, x, y, DarkenColor(BLUE, offset)); break;
				case WOOD: ImageDrawPixel(&img, x, y, DarkenColor(BROWN, offset)); break;
				default: ImageDrawPixel(&img, x, y, BLACK); break;
			}
		}
	UpdateTexture(tex, img.data);
	DrawTextureEx(tex, {0,0}, 0, PIXEL_SIZE, WHITE);
}

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE | FLAG_FULLSCREEN_MODE);
	InitWindow(LENGHT, WIDTH, "Arena");
	SetTargetFPS(170);

	SimulationMap sim;
	InitSimulationMap(sim);

	Image img = GenImageColor(GRID_WIDTH, GRID_HEIGHT, BLANK);
	Texture2D tex = LoadTextureFromImage(img);

	// game loop
	while (!exitWindow) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		HandleInput(sim);

		// drawing
		BeginDrawing();
		ClearBackground(BLACK);

		UpdateSimulationMap(sim);
		DrawSimulationMap(sim, img, tex);
		
		DrawFPS(10, 10);
		GuiComboBox((Rectangle){10, 40, 120, 24}, "#28#Vacío(V);#39#Arena(A);#26#Agua(W);#102#WOOD", &selectedMaterial);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}
	
	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
