#pragma once

template<typename T>
T Clamp(T val, T lower_bound, T upper_bound)
{
	if (val < lower_bound) return lower_bound;
	if (val > upper_bound) return upper_bound;
	return val;
}

template<typename T>
T Min(T number1, T number2)
{
	return number1 < number2 ? number1 : number2;
}

template<typename T>
T Max(T number1, T number2)
{
	return number1 > number2 ? number1 : number2;
}

bool IsAcuteTriangle(float side1, float side2, float hypotenuse);