#ifndef ENEMY_H
#define ENEMY_H

#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_random.h>

#include "Player.h"

// Enemy class 
class Enemy
{

public:
    Enemy(int start_x, int start_y, bn::fixed e_speed, bn::size e_size, int min_x, int min_y, int max_x, int max_y, bn::random rng);

    void update(Player &player);

    bn::sprite_ptr sprite;
    bn::fixed speed;
    bn::size size;
    bn::rect bounding_box;
    bn::random RNG;
    int MIN_X;
    int MIN_Y;
    int MAX_X;
    int MAX_Y;
};

#endif