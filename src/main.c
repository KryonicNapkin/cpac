// texture size: 16px
// texture size: 32px
// grid size height: 28
//           width:  31
//
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

#include "textures.h"
#include "animations.h"

#define WINDOW_WIDTH             1280
#define WINDOW_HEIGHT            1024

#define FONT_FILENAME            "font.TTF"
#define FONT_FONTSIZE            32

#define LEVEL_WIDTH              28
#define LEVEL_HEIGHT             31
#define LEVEL_CELL_SIZE          16

#define CELL_SOLID               0x01
#define CELL_SOLID_GHOST_DOOR    0x02
#define CELL_NOT_SOLID           0x04
#define CELL_NOT_SOLID_ENERGIZER 0x08
#define CELL_NOT_SOLID_DOT       0x10

typedef struct {
    Vector2 pos;
    int cell_idx;

    bool low_texture;
    Texture2D texture;
    int facing_rotation;
    int speed;
} entity_t;

const texture_id_t level_layout[LEVEL_WIDTH * LEVEL_HEIGHT] = {
    W1_C31,   W1_3,      W1_3,     W1_3,  W1_3,     W1_3,     W1_3,  W1_3,     W1_3,     W1_3,  W1_3,     W1_3,     W1_3,  W2_3_C32, W2_3_C31, W1_3,  W1_3,     W1_3,     W1_3,  W1_3,     W1_3,     W1_3,  W1_3,     W1_3,     W1_3,  W1_3,     W1_3,      W1_C32,
    W1_1,     DOT,       DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   W2_2,     W2_1,     DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,       W1_2,
    W1_1,     DOT,       W2_S_C31, W2_4,  W2_4,     W2_S_C32, DOT,   W2_S_C31, W2_4,     W2_4,  W2_4,     W2_S_C32, DOT,   W2_2,     W2_1,     DOT,   W2_S_C31, W2_4,     W2_4,  W2_4,     W2_S_C32, DOT,   W2_S_C31, W2_4,     W2_4,  W2_S_C32, DOT,       W1_2,  
    W1_1,     ENERGIZER, W2_2,     EMPTY, EMPTY,    W2_1,     DOT,   W2_2,     EMPTY,    EMPTY, EMPTY,    W2_1,     DOT,   W2_2,     W2_1,     DOT,   W2_2,     EMPTY,    EMPTY, EMPTY,    W2_1,     DOT,   W2_2,     EMPTY,    EMPTY, W2_1,     ENERGIZER, W1_2,
    W1_1,     DOT,       W2_S_C41, W2_3,  W2_3,     W2_S_C42, DOT,   W2_S_C41, W2_3,     W2_3,  W2_3,     W2_S_C42, DOT,   W2_S_C41, W2_S_C42, DOT,   W2_S_C41, W2_3,     W2_3,  W2_3,     W2_S_C42, DOT,   W2_S_C41, W2_3,     W2_3,  W2_S_C42, DOT,       W1_2,
    W1_1,     DOT,       DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,       W1_2,
    W1_1,     DOT,       W2_S_C31, W2_4,  W2_4,     W2_S_C32, DOT,   W2_S_C31, W2_S_C32, DOT,   W2_S_C31, W2_4,     W2_4,  W2_4,     W2_4,     W2_4,  W2_4,     W2_S_C32, DOT,   W2_S_C31, W2_S_C32, DOT,   W2_S_C31, W2_4,     W2_4,  W2_S_C32, DOT,       W1_2, 
    W1_1,     DOT,       W2_S_C41, W2_3,  W2_3,     W2_S_C42, DOT,   W2_2,     W2_1,     DOT,   W2_S_C41, W2_3,     W2_3,  W2_C32,   W2_C31,   W2_3,  W2_3,     W2_S_C42, DOT,   W2_2,     W2_1,     DOT,   W2_S_C41, W2_3,     W2_3,  W2_S_C42, DOT,       W1_2,
    W1_1,     DOT,       DOT,      DOT,   DOT,      DOT,      DOT,   W2_2,     W2_1,     DOT,   DOT,      DOT,      DOT,   W2_2,     W2_1,     DOT,   DOT,      DOT,      DOT,   W2_2,     W2_1,     DOT,   DOT,      DOT,      DOT,   DOT,      DOT,       W1_2,
    W1_C41,   W1_4,      W1_4,     W1_4,  W1_4,     W1_S_C32, DOT,   W2_2,     W2_C41,   W2_4,  W2_4,     W2_S_C32, EMPTY, W2_2,     W2_1,     EMPTY, W2_S_C31, W2_4,     W2_4,  W2_C42,   W2_1,     DOT,   W1_S_C31, W1_4,     W1_4,  W1_4,     W1_4,      W1_C42,
    EMPTY,    EMPTY,     EMPTY,    EMPTY, EMPTY,    W1_1,     DOT,   W2_2,     W2_C31,   W2_3,  W2_3,     W2_S_C42, EMPTY, W2_S_C41, W2_S_C42, EMPTY, W2_S_C41, W2_3,     W2_3,  W2_C32,   W2_1,     DOT,   W1_2,     EMPTY,    EMPTY, EMPTY,    EMPTY,     EMPTY,
    EMPTY,    EMPTY,     EMPTY,    EMPTY, EMPTY,    W1_1,     DOT,   W2_2,     W2_1,     EMPTY, EMPTY,    EMPTY,    EMPTY, EMPTY,    EMPTY,    EMPTY, EMPTY,    EMPTY,    EMPTY, W2_2,     W2_1,     DOT,   W1_2,     EMPTY,    EMPTY, EMPTY,    EMPTY,     EMPTY,
    EMPTY,    EMPTY,     EMPTY,    EMPTY, EMPTY,    W1_1,     DOT,   W2_2,     W2_1,     EMPTY, W3_C31,   W3_4,     W3_4,  W3_D1,    W3_D2,    W3_4,  W3_4,     W3_C32,   EMPTY, W2_2,     W2_1,     DOT,   W1_2,     EMPTY,    EMPTY, EMPTY,    EMPTY,     EMPTY,
    W1_3,     W1_3,      W1_3,     W1_3,  W1_3,     W1_S_C42, DOT,   W2_S_C41, W2_S_C42, EMPTY, W3_2,     EMPTY,    EMPTY, EMPTY,    EMPTY,    EMPTY, EMPTY,    W3_1,     EMPTY, W2_S_C41, W2_S_C42, DOT,   W1_S_C41, W1_3,     W1_3,  W1_3,     W1_3,      W1_3,
    EMPTY,    EMPTY,     EMPTY,    EMPTY, EMPTY,    EMPTY,    DOT,   EMPTY,    EMPTY,    EMPTY, W3_2,     EMPTY,    EMPTY, EMPTY,    EMPTY,    EMPTY, EMPTY,    W3_1,     EMPTY, EMPTY,    EMPTY,    DOT,   EMPTY,    EMPTY,    EMPTY, EMPTY,    EMPTY,     EMPTY,
    W1_4,     W1_4,      W1_4,     W1_4,  W1_4,     W1_S_C32, DOT,   W2_S_C31, W2_S_C32, EMPTY, W3_2,     EMPTY,    EMPTY, EMPTY,    EMPTY,    EMPTY, EMPTY,    W3_1,     EMPTY, W2_S_C31, W2_S_C32, DOT,   W1_S_C31, W1_4,     W1_4,  W1_4,     W1_4,      W1_4,
    EMPTY,    EMPTY,     EMPTY,    EMPTY, EMPTY,    W1_1,     DOT,   W2_2,     W2_1,     EMPTY, W3_C41,   W3_3,     W3_3,  W3_3,     W3_3,     W3_3,  W3_3,     W3_C42,   EMPTY, W2_2,     W2_1,     DOT,   W1_2,     EMPTY,    EMPTY, EMPTY,    EMPTY,     EMPTY,
    EMPTY,    EMPTY,     EMPTY,    EMPTY, EMPTY,    W1_1,     DOT,   W2_2,     W2_1,     EMPTY, EMPTY,    EMPTY,    EMPTY, EMPTY,    EMPTY,    EMPTY, EMPTY,    EMPTY,    EMPTY, W2_2,     W2_1,     DOT,   W1_2,     EMPTY,    EMPTY, EMPTY,    EMPTY,     EMPTY,
    EMPTY,    EMPTY,     EMPTY,    EMPTY, EMPTY,    W1_1,     DOT,   W2_2,     W2_1,     EMPTY, W2_S_C31, W2_4,     W2_4,  W2_4,     W2_4,     W2_4,  W2_4,     W2_S_C32, EMPTY, W2_2,     W2_1,     DOT,   W1_2,     EMPTY,    EMPTY, EMPTY,    EMPTY,     EMPTY,
    W1_C31,   W1_3,      W1_3,     W1_3,  W1_3,     W1_S_C42, DOT,   W2_S_C41, W2_S_C42, EMPTY, W2_S_C41, W2_3,     W2_3,  W2_C32,   W2_C31,   W2_3,  W2_3,     W2_S_C42, EMPTY, W2_S_C41, W2_S_C42, DOT,   W1_S_C41, W1_3,     W1_3,  W1_3,     W1_3,      W1_C32,
    W1_1,     DOT,       DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   W2_2,     W2_1,     DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,       W1_2,
    W1_1,     DOT,       W2_S_C31, W2_4,  W2_4,     W2_S_C32, DOT,   W2_S_C31, W2_4,     W2_4,  W2_4,     W2_S_C32, DOT,   W2_2,     W2_1,     DOT,   W2_S_C31, W2_4,     W2_4,  W2_4,     W2_S_C32, DOT,   W2_S_C31, W2_4,     W2_4,  W2_S_C32, DOT,       W1_2,
    W1_1,     DOT,       W2_S_C41, W2_3,  W2_C32,   W2_1,     DOT,   W2_S_C41, W2_3,     W2_3,  W2_3,     W2_S_C42, DOT,   W2_S_C41, W2_S_C42, DOT,   W2_S_C41, W2_3,     W2_3,  W2_3,     W2_S_C42, DOT,   W2_2,     W2_C31,   W2_3,  W2_S_C42, DOT,       W1_2,
    W1_1,     ENERGIZER, DOT,      DOT,   W2_2,     W2_1,     DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   W2_2,     W2_1,     DOT,   DOT,      ENERGIZER, W1_2,
    W2_1_C41, W2_4,      W2_S_C32, DOT,   W2_2,     W2_1,     DOT,   W2_S_C31, W2_S_C32, DOT,   W2_S_C31, W2_4,     W2_4,  W2_4,     W2_4,     W2_4,  W2_4,     W2_S_C32, DOT,   W2_S_C31, W2_S_C32, DOT,   W2_2,     W2_1,     DOT,   W2_S_C31, W2_4,      W2_2_C42,
    W2_1_C31, W2_3,      W2_S_C42, DOT,   W2_S_C41, W2_S_C42, DOT,   W2_2,     W2_1,     DOT,   W2_S_C41, W2_3,     W2_3,  W2_C32,   W2_C31,   W2_3,  W2_3,     W2_S_C42, DOT,   W2_2,     W2_1,     DOT,   W2_S_C41, W2_S_C42, DOT,   W2_S_C41, W2_3,      W2_2_C32,
    W1_1,     DOT,       DOT,      DOT,   DOT,      DOT,      DOT,   W2_2,     W2_1,     DOT,   DOT,      DOT,      DOT,   W2_2,     W2_1,     DOT,   DOT,      DOT,      DOT,   W2_2,     W2_1,     DOT,   DOT,      DOT,      DOT,   DOT,      DOT,       W1_2,
    W1_1,     DOT,       W2_S_C31, W2_4,  W2_4,     W2_4,     W2_4,  W2_C42,   W2_C41,   W2_4,  W2_4,     W2_S_C32, DOT,   W2_2,     W2_1,     DOT,   W2_S_C31, W2_4,     W2_4,  W2_C42,   W2_C41,   W2_4,  W2_4,     W2_4,     W2_4,  W2_S_C32, DOT,       W1_2, 
    W1_1,     DOT,       W2_S_C41, W2_3,  W2_3,     W2_3,     W2_3,  W2_3,     W2_3,     W2_3,  W2_3,     W2_S_C42, DOT,   W2_S_C41, W2_S_C42, DOT,   W2_S_C41, W2_3,     W2_3,  W2_3,     W2_3,     W2_3,  W2_3,     W2_3,     W2_3,  W2_S_C42, DOT,       W1_2,
    W1_1,     DOT,       DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,      DOT,   DOT,      DOT,       W1_2,
    W1_C41,   W1_4,      W1_4,     W1_4,  W1_4,     W1_4,     W1_4,  W1_4,     W1_4,     W1_4,  W1_4,     W1_4,     W1_4,  W1_4,     W1_4,     W1_4,  W1_4,     W1_4,     W1_4,  W1_4,     W1_4,     W1_4,  W1_4,     W1_4,     W1_4,  W1_4,     W1_4,      W1_C42,
};

typedef struct {
    texture_id_t level_layout[LEVEL_WIDTH * LEVEL_HEIGHT];

} level_t;

typedef struct {
    float dt;
    int level_num;
    level_t active_level;

} game_t;

Texture2D atlas;

void render_game(void);
void draw_texture(bool is_high_texture, texture_id_t texture_id, Vector2 pos);

int main(int argc, char* argv[]) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "cman");

    Font font = LoadFontEx(FONT_FILENAME, FONT_FONTSIZE, NULL, 0);
    atlas = LoadTexture(ATLAS_FILENAME);

    animation_t cman_anim = {
        .sprites = (texture_id_t[]){C1_A1, C1_A2},
        .number_of_sprites = 2,
        .index_of_current_sprite = 0,
        .current_sprite = C1_A1,

        .speed = ANIM_SPEED,
        .duration_left = ANIM_SPEED,
        .animation_update = animation_update,
    };

    while (!WindowShouldClose()) {
        cman_anim.animation_update(&cman_anim);

        BeginDrawing(); {
            ClearBackground(ORANGE);
            render_game();
            draw_animation(cman_anim, (Vector2){250.0f, 256.0f});
        } EndDrawing();

    }

    UnloadTexture(atlas);
    UnloadFont(font);
    CloseWindow();

    return 0;
}

void render_game(void) {
    Rectangle starting_cell = {
        .x = (WINDOW_WIDTH - (LEVEL_WIDTH * ATLAS_LTEXTURES_SIZE * TEXTURE_SCALE)) / 2.0f,
        .y = (WINDOW_HEIGHT - (LEVEL_HEIGHT * ATLAS_LTEXTURES_SIZE * TEXTURE_SCALE)) / 2.0f,
        .width = ATLAS_LTEXTURES_SIZE * TEXTURE_SCALE,
        .height = ATLAS_LTEXTURES_SIZE * TEXTURE_SCALE,
    };
    printf("%.1f, %.1f, %.1f, %.1f\n", starting_cell.x, starting_cell.y, starting_cell.width, starting_cell.height);
    Rectangle current_cell = starting_cell;
    for (int i = 0; i < LEVEL_WIDTH * LEVEL_HEIGHT; ++i) {
        Rectangle source = textures[level_layout[i]];
        DrawTexturePro(atlas, source, current_cell, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

        current_cell.x += ATLAS_LTEXTURES_SIZE * TEXTURE_SCALE;
        if ((i+1) % LEVEL_WIDTH == 0) {
            current_cell.y += ATLAS_LTEXTURES_SIZE * TEXTURE_SCALE;
            current_cell.x = starting_cell.x;
        }
    }
}

void draw_texture(bool is_high_texture, texture_id_t texture_id, Vector2 pos) {
    Rectangle dest = {
        .x = pos.x,
        .y = pos.y,
        .width = TEXTURE_SCALE * ((is_high_texture) ? ATLAS_HTEXTURES_SIZE : ATLAS_LTEXTURES_SIZE),
        .height = TEXTURE_SCALE * ((is_high_texture) ? ATLAS_HTEXTURES_SIZE : ATLAS_LTEXTURES_SIZE),
    };

    DrawTexturePro(atlas, textures[texture_id], dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
}
