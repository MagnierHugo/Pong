#include <stdio.h>
#include <string.h>

#include "pong.h"
#include "key_checks.h"


static bool KeyCheck(struct PressedKey key, SDL_Keycode keycode) {

	if (key.keyCode == keycode && key.isPressed == true) return true;
	return false;
}

static bool BorderCheck(struct SDL_Rect rect, struct Sides sides) {

	struct Sides sidesChecked;

	if (sides.UP) {
		if (rect.y > 0) sidesChecked.UP = true;
	}
	if (sides.Down) {
		if (rect.y + rect.h < 600) sidesChecked.Down = true;
	}
	if (sides.Right) {
		if (rect.x > 0) sidesChecked.Right = true;
	}
	if (sides.Left) {
		if (rect.x + rect.w > 0) sidesChecked.Left = true;
	}
}

void PlayerEntityMovement(struct GameObject gameObject, struct PressedKey pressedKeys[10], int nbrKeys) {

	if (strcmp(gameObject.name, "LeftPlayer")) {

		for (int keyIndex = 0; keyIndex < nbrKeys; keyIndex++) {

			struct PressedKey key = pressedKeys[keyIndex];
			if (KeyCheck(key, SDLK_z) && gameObject.rect.y + gameObject.rect.h > WINDOW_HEIGTH) {
				gameObject.rect.y += gameObject.movement.y;
			}
			if (key.keyCode == SDLK_s && key.isPressed == true) {
				gameObject.rect.y -= gameObject.movement.y;
			}
		}
	}
	else {

		for (int keyIndex = 0; keyIndex < nbrKeys; keyIndex++) {

			struct PressedKey key = pressedKeys[keyIndex];
			if (key.keyCode == SDLK_UP && key.isPressed == true) {
				gameObject.rect.y += gameObject.movement.y;
			}
			if (key.keyCode == SDLK_DOWN && key.isPressed == true) {
				gameObject.rect.y -= gameObject.movement.y;
			}
		}
	}
}