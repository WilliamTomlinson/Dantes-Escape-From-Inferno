/**  @file    game.c
     @authors S. M. Riordan
              W. R. J. Tomlinson
     @date    09/10/2025
     @brief   Implements a two-player platformer game for the UCFK4 using a scrolling LED matrix display,
              synchronised player readiness and win/loss detection via IR communication.

     @note    
              This game functions as a multiplayer platformer. Both players compete against one another
              in a scrolling bitmap that gets progressively faster.
              Since the bitmap will be of a fixed length, the bitmap shall loop, with each loop scrolling 
              faster than the other.
                
              Lose Condition: Player falls to the bottom of the map, OR, player "collides" with the "edge" 
              of an upcoming platform.
                
              How To Play: Game is played with bitmap scrolling from physical top to physical bottom of the UCFK4.
              Up: Jump
              Down: Fall

              A player wins by the other player confirming the lose condition.
*/


#include <system.h>
#include <pacer.h>
#include <navswitch.h>
#include <ir_uart.h>
#include <tinygl.h>
#include <font5x7_1.h>
#include <pio.h>
#include "level.h"
#include "world.h"
#include "player.h"
#include "screen.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10
#define SCROLL_RATE 10


/* redefining navswtiches to aligign with landscape arangement */
#define NAVSW_NORTH NAVSWITCH_WEST
#define NAVSW_EAST NAVSWITCH_NORTH
#define NAVSW_SOUTH NAVSWITCH_EAST
#define NAVSW_WEST NAVSWITCH_SWITCH
#define NAVSW_PUSH NAVSWITCH_PUSH

#define LOSE_MESSAGE 'L'
#define READY_MESSAGE 'R'
#define GAME_WIDTH 7
#define GAME_HEIGHT 5

/* Finite State Machine to handle game flow */
typedef enum {
    STATE_IDLE,
    STATE_READY_WAIT,
    STATE_COUNTDOWN,
    STATE_PLAYING
} GameState_t;

static GameState_t gameState = STATE_IDLE;
static uint8_t levelNumber = 0;
static uint16_t countdownTimer = 0;
static uint8_t scrollOffset = 0;

/**
 * @brief Displays idle screen and waits for local player to press the ready button.
 *        Once pressed, send 'R' over IR and transition to the READY_WAIT state.
 */
void runIdleScreen(void)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("PRESS TO READY ");
    if (isReadyButtonPressed()) {
        setBlueLed(true);
        ir_uart_putc('R');
        tinygl_text("WAITING FOR OTHER PLAYER ");
        gameState = STATE_READY_WAIT;
    }
}

/**
 * @brief Waits for the opponent to send a READY signal over IR.
 *        Once received, begin countdown.
 */
void runReadyWait(void)
{
    if (ir_uart_read_ready_p()) {
        if (ir_uart_getc() == 'R') {
            gameState = STATE_COUNTDOWN;
            countdownTimer = 0;
        }
    }
}

/**
 * @brief Displays "3 → 2 → 1 → GO!" and transitions to PLAYING state.
 */
void runCountdown(void)
{
    countdownTimer++;
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    if (countdownTimer < 500)
        tinygl_text("3");
    else if (countdownTimer < 1000)
        tinygl_text("2");
    else if (countdownTimer < 1500)
        tinygl_text("1");
    else {
        tinygl_text("GO!");
        gameState = STATE_PLAYING;
        scrollOffset = 0;
    }
}

/**
 * @brief Handles active gameplay, including map rendering, player input,
 *        collision detection and win/loss conditions.
 */
void runGame(void) {
    /* Resets and creats game world */ 
    const Level_t* level = levels[levelNumber];
    worldLoadLevel(level);

    /* Initialised the player */ 
    Player_t player;
    playerInit(&player);
    bool gameOn = true;

    while(gameOn) {
        pacer_wait();
        navswitch_update();

        /* Dealing with player */
        if (navswitch_push_event_p(NAVSW_NORTH) & (player.state == ONGROUND)) {
            playerJump(&player);
            player.state = AIRBORNE;
        }
        playerUpdateMotion(&player);
        if (!playerBoundaryCheckAndResolver(&player)) {
            playerCollisionCheckandResolver(&player);
        }
        uint8_t scrollOffset = worldToGridIndex(player.body.transform.x) - 1;
        uint8_t playerHeight = worldToGridIndex(player.body.transform.y);
        bool isAlive = isPlayerAlive(&player);

        /* Set display output */
        drawPlayer(playerHeight);
        drawMapWindow(level, scrollOffset);

        tinygl_update();
        
        /* Checks game outcome*/
        if (ir_uart_read_ready_p()) {
            if (ir_uart_getc() == LOSE_MESSAGE) {
                setBlueLed(false);

                displayGameWon();
                }
                
                gameState = STATE_IDLE;
                gameOn = false;

        } else if (!isAlive) {
            setBlueLed(false);
            ir_uart_getc();
            ir_uart_putc(LOSE_MESSAGE);

            displayGameLose();
            
            gameState = STATE_IDLE;
            gameOn = false;
        }
    }
}


int main (void)
{
    system_init();
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    navswitch_init();
    ir_uart_init();
    pacer_init(PACER_RATE);

    pio_config_set(PC2_PIO, PIO_OUTPUT_LOW);  /* Blue LED off */
    pio_config_set(PD7_PIO, PIO_INPUT);       /* Ready button input (external pull-up) */

    while (1)
    {
        pacer_wait();
        tinygl_update();
        navswitch_update();
        switch (gameState) {
            case STATE_IDLE:
                runIdleScreen();
                break;
            case STATE_READY_WAIT:
                runReadyWait();
                break;
            case STATE_COUNTDOWN:
                runCountdown();
                break;
            case STATE_PLAYING:
                runGame();
                break;
        }
    }
    return 0;
}