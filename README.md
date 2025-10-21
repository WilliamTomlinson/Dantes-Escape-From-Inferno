    
# Dantes Escape From Inferno

> A side scrolling versus game programmed in C that is made for the UC Fun-Kit 4.

<h3>  
    <p align="center">
        <i>🔥 Can you escape the hellscape? 🔥</i>
    </p>
</h3>

<p align="center">    
    <font color="red">
    DISCLAIMER: This game is currently non functional
    </font>
</p>

  

## About The Project

### background

This is a continuation of a game produced from a university group project for an computed/embedded systems course.

### The Game

Dantes escape from inferno is a side scrolling two player game where the objective is to survive for as long as you can against your opponent. The game has nine levels in correspondance with the nine circles of hell. Each level ends when your opponent looses, and you are the winner. Levels have rounds where for each round the levels map will loop back on itself increasing the speed multiplier. Each player has health points, health points are deducted for colliding with obstacles, when health runs out the game you lose that level.

### Hardware

The game is developed to work with the UCFK4 or NSKF. The Fun-Kits have a 7x5 dot matrix display, 4 direction push joy switch, and a tactile button. When the game is in two player mode the devices must be aimed at eachother.

## TODO

>   Things needing or currently being worked on
-   More levels
-   Single player mode


See the [open issues](https://github.com/your-username/Project-Name/issues) for a full list of proposed features (and known issues).

## Getting Started

> Follow these steps to get a local copy up and running.

### Prerequisites

*   UC Fun-Kit 4 or Not So Fun Kit 2
*   AVR-GCC
*   avr-binutils
*   Make
*   dfu-util

### Installation

1.  Clone the repo
    ```sh
    git clone --recurse-submodules https://github.com WilliamTomlinson/Dantes-Escape-From-Inferno.git
    ```
2.  Navigate to the game directory
    ```sh
    cd Dantes-Escape-From-Inferno/game/
    ```
3.  Connect two of either UCFK4 or NSFK2 to PC

4.  Upload the game running the following command twice
    ```sh
    make program
    ```

### Usage

To be explained.

<!--
Controls:
    Action:     Navswitch Direction:
    Jump        North
    Fall        South

To initialise "Ready-Up" sequence with between players:
    - Press "SW3" to display "LED1" ready indicator,
    - Once both players are ready, the game starts!

Once the game is over, the players will be returned to the "Ready-Up" screen.
-->
## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are greatly appreciated.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".

    Fork the Project

    Create your Feature Branch (git checkout -b feature/AmazingFeature)

    Commit your Changes (git commit -m 'feat: Add some AmazingFeature')

    Push to the Branch (git push origin feature/AmazingFeature)

    Open a Pull Request


## Authors

    William R.J. Tomlison - @WilliamTomlinson

    Samuel M. Riordan - Not on GitHub afaik
See also the list of contributors who participated in this project.
## Acknowledgements

A section to give credit.

    Phillip Hoff - Creator of the UC Fun-Kit

## License

Distributed under the MIT License. See LICENSE.txt for more information.