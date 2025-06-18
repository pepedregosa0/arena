#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include "../include/raygui.h"
#include <iostream>
#include <iomanip>

using namespace std;

enum SimMaterial
{
	EMPTY = 0,
	SAND = 1,
	WATER = 2,
	WOOD = 3
};
unsigned int LENGHT = 2560, WIDTH = 1440;
const int GRID_WIDTH = 2560/4;
const int GRID_HEIGHT = 1510/4;
const int PIXEL_SIZE = 4; 
int radius = 3; // Puedes ajustar el radio aquí
int selectedMaterial = SAND;

// Estructura para el estado del simulador
struct SimulationMap
{
	int map[GRID_HEIGHT][GRID_WIDTH] = {EMPTY};
	unsigned char colorOffset[GRID_HEIGHT][GRID_WIDTH] = {0}; // valor entre 0-255
};

// Inicializa la simulación
void InitSimulationMap(SimulationMap &sim)
{
	// Aquí puedes inicializar el estado si lo necesitas
	for (int y = 0; y < GRID_HEIGHT; y++)
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			sim.map[y][x] = EMPTY; // Inicializa todo a vacío	
			sim.colorOffset[y][x] = GetRandomValue(0, 20); // Asigna un valor aleatorio entre 0 y 255
		}

}

// Modifica HandleInput para usar el material seleccionado
void HandleInput(SimulationMap &sim)
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		Vector2 mouse = GetMousePosition();
		int x = mouse.x / PIXEL_SIZE;
		int y = mouse.y / PIXEL_SIZE;
		if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT)
		{
			for (int dy = -radius; dy <= radius; dy++)
			{
				for (int dx = -radius; dx <= radius; dx++)
				{
					if (dx * dx + dy * dy <= radius * radius) // Verifica si está dentro del círculo
					{
						int newX = x + dx;
						int newY = y + dy;
						if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT)
						{
							if (sim.map[newY][newX] == EMPTY || selectedMaterial == EMPTY)
							{
								switch (selectedMaterial)
								{
								case SAND:
								case WATER:
									if (GetRandomValue(0, 10) == 4)
										sim.map[newY][newX] = selectedMaterial;
									break;
								case WOOD:
								case EMPTY:
									sim.map[newY][newX] = selectedMaterial;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

// Actualiza la física de la simulación
void UpdateSimulationMap(SimulationMap &sim)
{
	for (int y = GRID_HEIGHT - 2; y >= 0; y--)
	{
		for (int x = GRID_WIDTH - 1; x >= 0; x--)
		{
			switch (sim.map[y][x])
			{
			case EMPTY:
				break;
			case SAND:
				if (sim.map[y + 1][x] == EMPTY)
				{
					sim.map[y][x] = EMPTY;
					sim.map[y + 1][x] = SAND;
				}
				// Ambas diagonales libres, elige aleatoriamente
				else if (
					x > 0 && x < GRID_WIDTH - 1 &&
					sim.map[y + 1][x - 1] == EMPTY &&
					sim.map[y + 1][x + 1] == EMPTY)
				{
					if (GetRandomValue(0, 1) == 0)
					{
						sim.map[y][x] = EMPTY;
						sim.map[y + 1][x - 1] = SAND;
					}
					else
					{
						sim.map[y][x] = EMPTY;
						sim.map[y + 1][x + 1] = SAND;
					}
				}
				else if (x > 0 && sim.map[y + 1][x - 1] == EMPTY)
				{
					sim.map[y][x] = EMPTY;
					sim.map[y + 1][x - 1] = SAND;
				}
				else if (x < GRID_WIDTH - 1 && sim.map[y + 1][x + 1] == EMPTY)
				{
					sim.map[y][x] = EMPTY;
					sim.map[y + 1][x + 1] = SAND;
				}
				break;

			case WATER:
				if (sim.map[y + 1][x] == EMPTY)
				{
					sim.map[y][x] = EMPTY;
					sim.map[y + 1][x] = WATER;
				}
				// Ambas diagonales libres, elige aleatoriamente
				else if (
					x > 0 && x < GRID_WIDTH - 1 &&
					sim.map[y + 1][x - 1] == EMPTY &&
					sim.map[y + 1][x + 1] == EMPTY)
				{
					if (GetRandomValue(0, 1) == 0)
					{
						sim.map[y][x] = EMPTY;
						sim.map[y + 1][x - 1] = WATER;
					}
					else
					{
						sim.map[y][x] = EMPTY;
						sim.map[y + 1][x + 1] = WATER;
					}
				}
				else if (x > 0 && sim.map[y + 1][x - 1] == EMPTY)
				{
					sim.map[y][x] = EMPTY;
					sim.map[y + 1][x - 1] = WATER;
				}
				else if (x < GRID_WIDTH - 1 && sim.map[y + 1][x + 1] == EMPTY)
				{
					sim.map[y][x] = EMPTY;
					sim.map[y + 1][x + 1] = WATER;
				}
				// Si no hay espacio abajo, intenta mover hacia los lados
				else if (x > 0 && x < GRID_WIDTH - 1 &&
					sim.map[y][x - 1] == EMPTY &&
					sim.map[y][x + 1] == EMPTY)
				{
					if (GetRandomValue(0, 1) == 0)
					{
						sim.map[y][x] = EMPTY;
						sim.map[y][x - 1] = WATER;
					}
					else
					{
						sim.map[y][x] = EMPTY;
						sim.map[y][x + 1] = WATER;
					}
				}
				else if (x > 0 && sim.map[y][x - 1] == EMPTY)
				{
					sim.map[y][x] = EMPTY;
					sim.map[y][x - 1] = WATER;
				}
				else if (x < GRID_WIDTH - 1 && sim.map[y][x + 1] == EMPTY)
				{
					sim.map[y][x] = EMPTY;
					sim.map[y][x + 1] = WATER;
				}
				break;
			}
		}
	}
}

Color DarkenColor(Color base, unsigned char offset)
{
	int r = base.r - offset;
	int g = base.g - offset;
	int b = base.b - offset;
	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;
	return (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, 255};
}


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

	bool exitWindow = false;

	SimulationMap sim;
	InitSimulationMap(sim);

	Image img = GenImageColor(GRID_WIDTH, GRID_HEIGHT, BLANK);
	Texture2D tex = LoadTextureFromImage(img);

	// game loop
	while (!exitWindow) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		if (WindowShouldClose() || IsKeyPressed(KEY_X)) exitWindow = true;

		float wheel = GetMouseWheelMove();
		if (wheel)
		{
			radius += wheel;
			if (radius < 1)
				radius = 1; // Asegúrate de que el radio no sea menor que 1
			else if (radius > 100)
				radius = 10; // Limita el radio a un máximo de 10
		}
		if (IsKeyPressed(KEY_V))
		selectedMaterial = EMPTY;
		if (IsKeyPressed(KEY_A))
		selectedMaterial = SAND;
		if (IsKeyPressed(KEY_W))
		selectedMaterial = WATER;
		if (IsKeyPressed(KEY_F))
		selectedMaterial = WOOD;
		
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
