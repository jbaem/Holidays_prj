#include "Utilities.h"
#include "Enums.h"

bool IsAcuteTriangle(float side1, float side2, float hypotenuse)
{
	return side1 * side1 + side2 * side2 <= hypotenuse * hypotenuse;
}