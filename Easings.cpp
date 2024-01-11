#include "Easings.h"

float EaseInBack(float frame) {
	const float a = 1.70158f;
	const float b = a + 1;

	return b * frame * frame * frame - a * frame * frame;
}