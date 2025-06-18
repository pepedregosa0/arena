#include "input.h"

int radius = 3;
int selectedMaterial = SAND;
bool exitWindow = false;

// Modifica HandleInput para usar el material seleccionado
void HandleInput(SimulationMap &sim)
{
	if (WindowShouldClose() || IsKeyPressed(KEY_X))
		exitWindow = true;

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