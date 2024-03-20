#include <stdio.h>
#include <stdbool.h>

#include "pong.h"


bool KeyCheck(struct PressedKey key, SDL_Keycode keycode) {

	if (key.keyCode == keycode && key.isPressed == true) return true;
	return false;
}