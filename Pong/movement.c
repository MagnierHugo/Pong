#include <stdio.h>
#include <string.h>

#include "pong.h"
#include "key_checks.h"


void PlayerEntityMovement(struct GameObject gameObject, struct PressedKey pressedKeys[10], int nbrKeys) {

	if (strcmp(gameObject.name, "LeftPlayer")) {

		for (int keyIndex = 0; keyIndex < nbrKeys; keyIndex++) {

			struct PressedKey key = pressedKeys[keyIndex];
			if (CheckZ(key) && gameObject.rect.y + gameObject.rect.h > WINDOW_HEIGTH) {
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