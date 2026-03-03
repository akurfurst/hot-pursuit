#include <bn_vector.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_string.h>

#include "common_fixed_8x16_font.h"
#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay(int score_x, int score_y, int high_x, int high_y) : score(0),                                                                  // Start score at 0
                                                                               high_score(0),                                                             // Start high score at 0
                                                                               SCORE_X(score_x),
                                                                               SCORE_Y(score_y),
                                                                               HIGH_SCORE_X(high_x),
                                                                               HIGH_SCORE_Y(high_y),
                                                                               score_sprites(bn::vector<bn::sprite_ptr, ScoreDisplay::MAX_CHARS>()),      // Start with empty vector for score sprites
                                                                               text_generator(bn::sprite_text_generator(common::fixed_8x16_sprite_font)) // Use a new text generator
{
}

void ScoreDisplay::update()
{
    // increase score and update high score if this is the new highest
    score++;
    if (score > high_score)
    {
        high_score = score;
    }

    // Stop displaying previous scores
    score_sprites.clear();

    // Display new scores
    show_number(SCORE_X, SCORE_Y, score, "Score: ");
    show_number(HIGH_SCORE_X, HIGH_SCORE_Y, high_score, "High Score: ");
}

void ScoreDisplay::show_number(int x, int y, int number, bn::string<ScoreDisplay::MAX_CHARS> text)
{
    // Convert number to a string and then display it
    bn::string<ScoreDisplay::MAX_CHARS> number_string = bn::to_string<ScoreDisplay::MAX_CHARS>(number);
    text_generator.generate(x, y, text + number_string, score_sprites);
}

void ScoreDisplay::resetScore()
{
    score = 0;
}