#ifndef PLAYER_H
#define PLAYER_H

#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_sprite_item.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_vector.h>
#include <bn_string.h>

#include "bn_sprite_items_character.h"
#include "common_fixed_8x16_font.h"

//int MAX_CHARS = 22;

class Player
{
public:
    Player(int start_x, int start_y, bn::fixed player_speed, bn::size player_size, bn::fixed hp);
    /**
     * Update the position and bounding box of the player based on d-pad movement.
     */
    void update();

    /**
     * Displays a number at the given position
     */
    void show_Player_Hp(int x, int y);

    // Create the sprite. This will be moved to a constructor
    bn::sprite_ptr sprite;
    bn::fixed speed;                                  // The speed of the player
    bn::size size;                                    // The width and height of the sprite
    bn::rect bounding_box;                            // The rectangle around the sprite for checking collision
    bn::vector<bn::sprite_ptr, 22> hp_sprites; // Sprites to display player hp
    bn::sprite_text_generator text_generator;         // Text generator for hp
    bn::fixed playerHP;
};
#endif