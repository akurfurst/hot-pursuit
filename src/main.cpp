#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_math.h>
#include <bn_random.h>

#include "game_over.h"
#include "common_fixed_8x16_font.h"
#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_villain.h"
#include "bn_sprite_items_character.h"
#include "bn_sprite_items_square.h"
#include "Player.h"
#include "create_bounding_box.h"
#include "Enemy.h"
#include "ScoreDisplay.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// Number of characters required to show two of the longest numer possible in an int (-2147483647)
static constexpr int MAX_CHARS = 22;

// Score location
static constexpr int SCORE_X = -70;
static constexpr int SCORE_Y = -70;

// High score location - will follow basic score
static constexpr int HIGH_SCORE_X = SCORE_X;
static constexpr int HIGH_SCORE_Y = SCORE_Y + 10;

// HP LOCATIONS - will follow highscore location
static constexpr int HP_X = HIGH_SCORE_X;
static constexpr int HP_Y = HIGH_SCORE_Y + 10;

// MaxPlayer HP
static constexpr int MAX_PLAYER_HP = 3;

// max enemys
static constexpr int MAX_ENEMY = 5;

// Enemy spawns
int NEXT_ENEMY_SCORE = 500;

// random number generator
bn::random RNG;

int main()
{
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay(SCORE_X, SCORE_Y, HIGH_SCORE_X, HIGH_SCORE_Y);

    // Create a player and initialize it
    // TODO: we will move the initialization logic to a constructor.
    Player player = Player(44, 22, 3, PLAYER_SIZE, MAX_PLAYER_HP);
    // Enemy enemy = Enemy(0, 0, 2, ENEMY_SIZE);

    // enemy vector
    bn::vector<Enemy, MAX_ENEMY> enemys = {};
    enemys.push_back(Enemy(0, 0, 2, ENEMY_SIZE, MIN_X, MIN_Y, MAX_X, MAX_Y, RNG));

    // bn::sprite_ptr enemy_sprite = bn::sprite_items::villain.create_sprite(-30, 22);
    // bn::rect enemy_bounding_box = create_bounding_box(enemy_sprite, ENEMY_SIZE);
    while (true)
    {
        player.update();
        // enemy.update(player);

        for (Enemy &enemy : enemys)
        {
            enemy.update(player);
        }

        // Reset the current score and player position if the player collides with enemy

        if (player.playerHP <= 0)
        {
            scoreDisplay.resetScore();
            GameOver();
            enemys.clear();
            enemys.push_back(Enemy(0, 0, 2, ENEMY_SIZE, MIN_X, MIN_Y, MAX_X, MAX_Y, RNG));
        }

        // spawn new enemy if score has increased by 1000
        if (scoreDisplay.score >= NEXT_ENEMY_SCORE && enemys.size() < MAX_ENEMY)
        {
            enemys.push_back(Enemy(0, 0, 2, ENEMY_SIZE, MIN_X, MIN_Y, MAX_X, MAX_Y, RNG));
            NEXT_ENEMY_SCORE += 500;
        }

        //stop player from going off screen
        if(player.sprite.x() >= MAX_X) player.sprite.set_x(MAX_X);
        if(player.sprite.x() <= MIN_X) player.sprite.set_x(MIN_X);
        if(player.sprite.y() >= MAX_Y) player.sprite.set_y(MAX_Y);
        if(player.sprite.y() <= MIN_Y) player.sprite.set_y(MIN_Y);

        // Update the scores and disaply them
        scoreDisplay.update();

        bn::core::update();
    }
}
