/** @file   screen.h
    @author S. M. Riordan
    @date   14 Oct 2025
    @brief  Header file that encapsulates functions relating to the display.
*/


#ifndef SCREEN_H
#define SCREEN_H

#include <system.h>
#include <pio.h>
#include <tinygl.h>
#include <pacer.h>
#include "level.h"

#define PLAYER_HORIZONTAL_POSITION 1

bool isReadyButtonPressed(void);

void setBlueLed(bool ledOn);

void drawMapWindow(const Level_t* level, uint8_t scrollOffset);

void drawPlayer(uint8_t playerPosition);

void removePlayer(uint8_t playerPosition);

void displayGameWon(void);

void displayGameLose(void);

#endif /* SCREEN_H */