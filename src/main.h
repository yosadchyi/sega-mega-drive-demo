#ifndef _MAIN_INCLUDED
#define _MAIN_INCLUDED

typedef struct Vector2 {
    fix32 x;
    fix32 y;
} Vector2;

#define SPRITE_COUNT (1)
#define PLAYER_SPRITE_INDEX (0)

#define TILE_SZ (8)

#define WORLD_W (40)
#define WORLD_H (28)

#define GROUND_Y (FIX32(WORLD_H * 8 / 2))
#define GRAVITY (fix32Div(300, 10))

#endif /* _MAIN_INCLUDED */