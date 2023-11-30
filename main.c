/*********************************************************************************************
 *
 * @date     ->  11-29-2023
 *
 * @author   ->  Josh Williams
 * 
 * @brief    ->  Recreation of the 2013 "Flappy Bird" game.This file is set up similair to 
 *               the main in the collide.c file.
 *
 * @details  ->  Press/hold the A button to ascend, try to navigate through the obstacles.
 *
 *********************************************************************************************/

#include "flappyBird.c"

int main()
{
    // [1]... Set the mode to mode 0 with bg0 on
    *display_control = MODE0 | MODE1 | BG0_ENABLE | BG1_ENABLE | SPRITE_ENABLE | SPRITE_MAP_1D;

    // [2]... Declare and assign score, fps, num, and count variables
    int score = 0;
    int fps = 0;
    int num = 5;
    int count = 16;

    // [3]... Display a start menu for before the game starts
    while (1)
    {
        // Setup the background
        setup_background0();

        // Update num variable
        num = countDown(count, 1, 6, 11);

        // Break out of loop when num = 0
        if (num == 0)
        {
            break;
        }

        // Display to user countdown of new game
        char str[32];
        sprintf(str, "NEW GAME IN %d", num);
        set_text(str, 8, 8);

        // Deincrement count
        count--;

        // Delay 10000
        delay(10000);
    }

    // [4]... Set num back to 5
    num = 5;

    // [5]... Setup the sprite image data
    setup_sprite_image();

    // [6]... Clear all the sprites on screen now
    sprite_clear();

    // [8]... Create the bird
    struct Koopa koopa;
    koopa_init(&koopa);

    // [9]... Set initial scroll to 0
    int xscroll = 0;
    int yscroll = 0;

    // [10]... Loop forever
    while (1)
    {
        // Set the background
        setup_background();

        // Update the bird
        koopa_update(&koopa, xscroll);
        xscroll++;
        delay(300);

        // Check for jumping
        if (button_pressed(BUTTON_A))
        {
            koopa_jump(&koopa);
            koopa_right(&koopa);
        }
        else
        {
            koopa_stop(&koopa);
        }

        // Check for top collision
        if (check_collision_top(&koopa, xscroll) == 1 | check_collision_bottom(&koopa, xscroll) == 1)
        {
            xscroll--;

            // Clear background/Set-up background0
            clear_background();
            setup_background0();

            // Decrement num variable
            num--;

            // Display GAME OVER! to user / Total Score
            char str[32];
            sprintf(str, "GAME OVER! %s");
            set_text(str, 10, 10);
            char str2[32];
            sprintf(str2, "     TOTAL SCORE %d", score);
            set_text(str2, 6, 4);
            delay(50500);

            // Break out of loop when num = 0
            if (num == 0)
            {
                num = 5;
                break;
            }
        }
        else
        {
            // Increment the speed to make the game more difficult when both these conditions are true
            if (increment_speed(fps) >= 25 && score > 31)
            {
                xscroll++;
            }

            // Increment score by 1 every 70 frames
            fps++;
            if (fps >= 70)
            {
                fps = 0;
                score++;
            }
        }

        // Wait for vblank before scrolling and moving sprites
        wait_vblank();
        *bg0_x_scroll = xscroll;
        *bg0_y_scroll = yscroll;
        sprite_update_all();

        // Delay 500
        delay(500);
    }
}
