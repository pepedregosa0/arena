#include "utils.h"

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