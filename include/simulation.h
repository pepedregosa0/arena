#pragma once

#include "config.h"
#include <raylib.h>

// Estructura para el estado del simulador
struct SimulationMap
{
	int map[GRID_HEIGHT][GRID_WIDTH] = {EMPTY};
	unsigned char colorOffset[GRID_HEIGHT][GRID_WIDTH] = {0}; // valor entre 0-255
};

void InitSimulationMap(SimulationMap &sim);
void UpdateSimulationMap(SimulationMap &sim);
