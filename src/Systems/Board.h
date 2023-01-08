//
// Created by 22max on 07.01.2023.
//

#pragma once

#include <vector>
#include <memory>

#include "Field.h"

class Board {

    // Attributes
public:
    std::vector<std::shared_ptr<Field>> fields;
    /*
     Fields are counted like this:

     0 | 1 | 2
     ----------
     3 | 4 | 5
     ----------
     6 | 7 | 8

     */

    std::vector<Rectangle> fieldRecs;
    float fieldSize;


    // Hover
    int fieldHovered;
    bool drawHover = false;


    // Turn management
    bool playerTurn = true;

    // Win condition
    bool gameOver = false;
    bool playerWon = false;
    bool AIWon = false;

    // Methods
public:
    Board();
    void Update();
    void Draw();

    bool winConditionMet(FieldState side);

};
