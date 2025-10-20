/** @file   screen.c
    @author S. M. Riordan
    @date   14 Oct 2025
    @brief  C file that encapsulates functions relating to the display for game.c
*/

#include "screen.h"

bool isReadyButtonPressed(void)
{
    return pio_input_get(PD7_PIO);  /* PD7 HIGH = pressed */ 
}

void setBlueLed(bool ledOn)
{
    pio_output_set(PC2_PIO, ledOn);  /* Active high */
}


void drawPlayer(uint8_t playerPosition)
{
    tinygl_draw_point(tinygl_point(playerPosition, PLAYER_HORIZONTAL_POSITION), 1);  /* LED ON */ 
}

void removePlayer(uint8_t playerPosition)
{
    tinygl_draw_point(tinygl_point(playerPosition, PLAYER_HORIZONTAL_POSITION), 0);  /* LED OFF */
}


void displayGameWon(void)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("WINNER ");
    for (int i = 0; i < 1000; i++) {
        pacer_wait();
        tinygl_update();
    }
}
void displayGameLose(void)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("GAME OVER ");
    for (int i = 0; i < 1000; i++) {
        pacer_wait();
        tinygl_update();
    }
}

void drawMapWindow(const Level_t* level, uint8_t scrollOffset) 
{
    const uint8_t* bitMap = level->bitMap;
    uint8_t levelLength = level->levelLength;
    for (int col = 0; col < 7; col++) {
        uint8_t columnBits = bitMap[(scrollOffset + col) % levelLength];

        for (int row = 0; row < 5; row++) {
            bool pixelOn = (columnBits >> row) & 1;
            if (pixelOn) {
                tinygl_draw_point(tinygl_point(col, row), 1);  /* LED ON */ 
            } else {
                tinygl_draw_point(tinygl_point(col, row), 0);  /* LED OFF */
            }
        }
    }
}



