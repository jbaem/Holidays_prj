#include "ABackground.h"

void ABackground::OnRender(Gdiplus::Graphics* InGraphics)
{
	if (!Image)
		return;

	InGraphics->DrawImage(
		Image,
		0.0f, 0.0f,
		Size.X, Size.Y
	);
}
