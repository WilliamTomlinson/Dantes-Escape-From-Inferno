# File:   Makefile
# Author: S. M. Riordan & W. R. J. Tomlinson
# Date:   15/10/2025 (Refactored for maintainability)
# Descr:  Makefile for game

# --- Configuration ---
# Tools
CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size
RM = rm -rf

# MCU and optimization settings
MCU = atmega32u2
OPTIMIZE = -Os

# Name of the final output file (without extension)
TARGET = game

# --- Build Directories ---
# All output files will be placed here
BUILD_DIR = build

# --- Compiler and Linker Flags ---
# Add all directories containing header files to the -I flags
INCLUDE_DIRS = -I. \
               -I../fun-kit_api/utils \
               -I../fun-kit_api/fonts \
               -I../fun-kit_api/drivers \
               -I../fun-kit_api/drivers/avr \
               -Imodules

# CFLAGS for compiling. -MMD -MP are for automatic dependency generation
CFLAGS = -mmcu=$(MCU) $(OPTIMIZE) -Wall -Wstrict-prototypes -Wextra -g $(INCLUDE_DIRS) -MMD -MP
# LDFLAGS for linking. Add libraries like -lm here
LDFLAGS = -lm

# --- Source Files ---
# List all your .c source files here.
# This is the ONLY list you should ever need to edit.
SRCS = \
    game.c \
    ../fun-kit_api/drivers/avr/ir_uart.c \
    ../fun-kit_api/drivers/avr/pio.c \
    ../fun-kit_api/drivers/avr/prescale.c \
    ../fun-kit_api/drivers/avr/system.c \
    ../fun-kit_api/drivers/avr/timer.c \
    ../fun-kit_api/drivers/avr/timer0.c \
    ../fun-kit_api/drivers/avr/usart1.c \
    ../fun-kit_api/drivers/navswitch.c \
    ../fun-kit_api/drivers/display.c \
    ../fun-kit_api/drivers/ledmat.c \
    ../fun-kit_api/utils/font.c \
    ../fun-kit_api/utils/pacer.c \
    ../fun-kit_api/utils/tinygl.c \
    modules/level.c \
    modules/math.c \
    modules/physics.c \
    modules/player.c \
    modules/screen.c \
    modules/world.c

# --- Automatic File Generation ---
# Automatically create a list of object files in the BUILD_DIR
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))
# Automatically create a list of dependency files
DEPS = $(OBJS:.o=.d)
# Define the final executable and hex file paths
EXECUTABLE = $(BUILD_DIR)/$(TARGET).out
HEX_FILE = $(BUILD_DIR)/$(TARGET).hex

# Tell make where to find source files
VPATH = $(sort $(dir $(SRCS)))

# --- Main Targets ---

# Default target: build the executable and the hex file
.PHONY: all
all: $(EXECUTABLE) $(HEX_FILE)

# Link the executable from all the object files
$(EXECUTABLE): $(OBJS)
	@echo "Linking..."
	$(CC) -mmcu=$(MCU) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Size of $(EXECUTABLE):"
	$(SIZE) $@

# Create the .hex file from the .out file
$(HEX_FILE): $(EXECUTABLE)
	@echo "Creating HEX file..."
	$(OBJCOPY) -O ihex $< $@

# Program the device
.PHONY: program
program: $(HEX_FILE)
	@echo "Programming device..."
	dfu-programmer $(MCU) erase
	dfu-programmer $(MCU) flash $(HEX_FILE)
	dfu-programmer $(MCU) start

# Clean the build directory
.PHONY: clean
clean:
	@echo "Cleaning project..."
	-$(RM) $(BUILD_DIR)

# --- Generic Compilation Rule ---
# This single rule compiles any .c file into a .o file in the build directory
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# This rule creates the build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $@

# --- Include Auto-Generated Dependencies ---
# This will include all the .d files created by the compiler.
# The leading '-' tells make not to complain if the files don't exist yet.
-include $(DEPS)```