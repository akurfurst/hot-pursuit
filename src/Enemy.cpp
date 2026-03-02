#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_math.h>

#include "Player.h"
#include "Enemy.h"
#include "create_bounding_box.h"
#include "bn_sprite_items_villain.h"

Enemy::Enemy(int start_x, int start_y, bn::fixed e_speed, bn::size e_size, int min_x, int min_y, int max_x, int max_y, bn::random rng) : sprite(bn::sprite_items::villain.create_sprite(start_x, start_y)),
                                                                                                                                         speed(e_speed),
                                                                                                                                         size(e_size),
                                                                                                                                         bounding_box(create_bounding_box(sprite, size)),
                                                                                                                                         RNG(rng),
                                                                                                                                         MIN_X(min_x),
                                                                                                                                         MIN_Y(min_y),
                                                                                                                                         MAX_X(max_x),
                                                                                                                                         MAX_Y(max_y)
{
}

void Enemy::update(Player &player)
{

    bn::fixed distX = player.sprite.x() - sprite.x();
    bn::fixed distY = player.sprite.y() - sprite.y();
    bn::fixed move = bn::sqrt((distX * distX) + (distY * distY));
    if (move != 0)
    {
        sprite.set_position((sprite.x() + ((distX / move)) * speed), (sprite.y() + ((distY / move)) * speed));
    }

    if (bounding_box.intersects(player.bounding_box))
    {
        player.playerHP -= 1;
        player.sprite.set_x(RNG.get_int(MIN_X, MAX_Y));
        player.sprite.set_y(RNG.get_int(MIN_Y, MAX_Y));

        if (player.playerHP <= 0)
        {
            player.playerHP = 0; // normalizes player hp
        }
    }

    bounding_box = create_bounding_box(sprite, size);
}