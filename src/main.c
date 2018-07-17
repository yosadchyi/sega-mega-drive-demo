#include <genesis.h>
#include "gfx.h"
#include "main.h"

/*
 * Static data
 */
static const fix32 dt = fix32Div(FIX32(1), FIX32(24));
static Sprite sprites[1];
static Vector2 character_pos = {FIX32(1), GROUND_Y};
static Vector2 character_vel = {0, 0};

/*
 * Shorthands
 */
#define PLAYER_SPRITE (&sprites[PLAYER_SPRITE_INDEX])

/*
 * Functions
 */
static void init_tileset(void);
static void draw_background(void);
static void init_character(Vector2 *pos);
static void process_input();
static void simulate_physics();

/*
 * Implementation of functions
 */
int main(int argc, char **argv) {
    VDP_setScreenWidth320();
    SPR_init(4 * TILE_SZ);
    JOY_init();
    init_tileset();
    draw_background();
    init_character(&character_pos);

    while (1) {
        process_input();
        simulate_physics();
        SPR_update(sprites, SPRITE_COUNT);
        VDP_waitVSync();
    }

    SPR_end();

    return 0;
}

void draw_background() {
    VDP_fillTileMapRect(VDP_PLAN_B, TILE_ATTR_FULL(PAL2, 0, 0, 0, TILE_USERINDEX + 5), 0, 0, WORLD_W, WORLD_H);
    VDP_fillTileMap(VDP_PLAN_B, TILE_ATTR_FULL(PAL2, 0, 1, 0, TILE_USERINDEX + 2), (WORLD_H + 4) / 2 * 64, WORLD_W);
}

void init_tileset() {
    VDP_loadBMPTileData(tileset.image, TILE_USERINDEX, tileset.w / TILE_SZ, tileset.h / TILE_SZ, tileset.w / TILE_SZ);
    VDP_setPalette(PAL2, tileset.palette->data);
}

void init_character(Vector2 *pos) {
    VDP_setPalette(PAL1, knight_def.palette->data);
    SPR_initSprite(PLAYER_SPRITE, &knight_def, fix32ToInt(pos->x), fix32ToInt(pos->y),
                   TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}

void process_input() {
    Vector2 *vel = &character_vel;
    u16 state = JOY_readJoypad(JOY_1);
    int xdir = 0;

    if (state & BUTTON_LEFT) {
        xdir = -1;
    } else if (state & BUTTON_RIGHT) {
        xdir = 1;
    }
    if ((state & BUTTON_A) && vel->y == 0) {
        vel->y = FIX32(-24);
    }

    vel->x = FIX32(16 * xdir);

    if (xdir != 0) {
        SPR_setAttribut(PLAYER_SPRITE, TILE_ATTR(PAL1, TRUE, FALSE, xdir < 0));
    }
}

void simulate_physics() {
    Vector2 *pos = &character_pos;
    Vector2 *vel = &character_vel;

    pos->x += fix32Mul(vel->x, dt);
    pos->y += fix32Mul(vel->y, dt);

    if (pos->y < GROUND_Y) {
        vel->y += fix32Mul(GRAVITY, dt);
    } else {
        vel->y = 0;
        pos->y = GROUND_Y;
    }

    SPR_setPosition(PLAYER_SPRITE, fix32ToInt(pos->x), fix32ToInt(pos->y));
}
