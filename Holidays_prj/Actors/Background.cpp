#include "Background.h"

void Background::OnRender(Gdiplus::Graphics* InGraphics)
{
	if (!Image)
		return;

	InGraphics->DrawImage(
		Image,
		0.0f, 0.0f,
		Size.X, Size.Y
	);
}
