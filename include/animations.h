#ifndef ANIMATIONS_H_
#define ANIMATIONS_H_

#include "textures.h"

#define ANIM_SPEED 0.05f

typedef struct Animation {
    texture_id_t* sprites;
    texture_id_t current_sprite;
    int number_of_sprites;
    int index_of_current_sprite;
    
    float speed;
    float duration_left;
    void (*animation_update)(struct Animation* self);
} animation_t;

void animation_update(animation_t* self);
void draw_animation(animation_t animation, Vector2 pos);

#endif /* ANIMATIONS_H_ */
