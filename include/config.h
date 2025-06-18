#pragma once

constexpr unsigned int LENGHT = 2560, WIDTH = 1440;
constexpr int GRID_WIDTH = 2560 / 4;
constexpr int GRID_HEIGHT = 1510 / 4;
constexpr int PIXEL_SIZE = 4;

enum SimMaterial
{
	EMPTY = 0,
	SAND = 1,
	WATER = 2,
	WOOD = 3
};
