#include "animations.h"
#include "textures.h"

#include <raylib.h>

void animation_update(animation_t* self) {
    float dt = GetFrameTime();
    self->duration_left -= dt;

    if (self->duration_left <= 0.0f) {
        self->duration_left = self->speed;
        self->current_sprite = self->sprites[self->index_of_current_sprite++];

        if (self->index_of_current_sprite > self->number_of_sprites) {
            self->index_of_current_sprite = 0;
            self->current_sprite = self->sprites[self->index_of_current_sprite];
        }
    }
}

void draw_animation(animation_t animation, Vector2 pos) {
    Rectangle dest = {
        .x = pos.x,
        .y = pos.y,
        .width = TEXTURE_SCALE * ATLAS_HTEXTURES_SIZE,
        .height = TEXTURE_SCALE * ATLAS_HTEXTURES_SIZE,
    };
    DrawTexturePro(atlas, textures[animation.current_sprite], dest, (Vector2){0.0f, 0.0f},
                   0.0f, WHITE);
}
