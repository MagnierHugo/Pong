#include <stdio.h>
#include <stdbool.h>

#include "pong.h"


bool CheckZ(struct PressedKey key) {

	if (key.keyCode == SDLK_z && key.isPressed == true) return true;
	return false;
}