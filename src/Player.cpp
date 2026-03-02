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
#include "Player.h"
#include "create_bounding_box.h"



void Player::update()
{
    if (bn::keypad::right_held())
    {
        sprite.set_x(sprite.x() + speed);
    }
    if (bn::keypad::left_held())
    {
        sprite.set_x(sprite.x() - speed);
    }
    // TODO: Add logic for up and down
    if (bn::keypad::up_held())
    {
        sprite.set_y(sprite.y() - speed);
    }
    if (bn::keypad::down_held())
    {
        sprite.set_y(sprite.y() + speed);
    }

    bounding_box = create_bounding_box(sprite, size);

    hp_sprites.clear();
    show_Player_Hp(-70, -50);
}

void Player::show_Player_Hp(int x, int y)
{
    bn::string<22> text = "HP: ";
    bn::string<22> number_string = bn::to_string<22>(playerHP);
    text_generator.generate(x, y, text + number_string, hp_sprites);
}

Player::Player(int start_x, int start_y, bn::fixed player_speed, bn::size player_size, bn::fixed hp) : sprite(bn::sprite_items::character.create_sprite(start_x, start_y)),
                                                                                                       speed(player_speed),
                                                                                                       size(player_size),
                                                                                                       bounding_box(create_bounding_box(sprite, size)),
                                                                                                       hp_sprites(bn::vector<bn::sprite_ptr, 22>()), // Start with empty vector for score sprites
                                                                                                       text_generator(bn::sprite_text_generator(common::fixed_8x16_sprite_font)),
                                                                                                       playerHP(hp)
{
}