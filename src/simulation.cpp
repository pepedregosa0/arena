#include "simulation.h"

// Inicializa la simulación
void InitSimulationMap(SimulationMap &sim)
{
	// Aquí puedes inicializar el estado si lo necesitas
	for (int y = 0; y < GRID_HEIGHT; y++)
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			sim.map[y][x] = EMPTY;						   // Inicializa todo a vacío
			sim.colorOffset[y][x] = GetRandomValue(0, 20); // Asigna un valor aleatorio entre 0 y 255
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