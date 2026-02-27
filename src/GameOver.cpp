#include "game_over.h"
#include "bn_sprite_text_generator.h"
#include "bn_vector.h"
#include "common_fixed_8x16_font.h"
#include "bn_sprite_ptr.h"

bn::sprite_text_generator text_generator(common::fixed_8x16_sprite_font);
bn::vector<bn::sprite_ptr, 16> game_over_sprites;

void GameOver()
{
    game_over_sprites.clear();
    text_generator.generate(0, 0, "GAME OVER", game_over_sprites);
}