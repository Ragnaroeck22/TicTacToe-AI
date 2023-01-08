//
// Created by 22max on 07.01.2023.
//

#pragma once

#include "../Enums.h"
#include "raylib.h"

class Field {

// Attributes
public:
    FieldState state = UNMARKED;


// Methods

    void Update();
    void Draw(Vector2 position, float fieldSize);

};
