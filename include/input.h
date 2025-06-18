#pragma once

#include <raylib.h>
#include "simulation.h"

extern int radius;
extern int selectedMaterial;
extern bool exitWindow;

// Modifica HandleInput para usar el material seleccionado
void HandleInput(SimulationMap &sim);

// Actualiza la física de la simulación
void UpdateSimulationMap(SimulationMap &sim);