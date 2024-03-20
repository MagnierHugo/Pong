#pragma once

struct Vector2 { float X, Y; };

float Magnitude(struct Vector2 vec);

struct Vector2 Normalize(struct Vector2* vec);