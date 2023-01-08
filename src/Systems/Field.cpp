//
// Created by 22max on 07.01.2023.
//

#include "Field.h"

void Field::Update()
{

}

void Field::Draw(Vector2 position, float fieldSize)
{
    switch (state)
    {
        case UNMARKED:
            // Draw / do nothing
            break;

        case MARKED_BY_PLAYER:
            DrawCircle(position.x, position.y, fieldSize / 2, BLUE);
            break;

        case MARKED_BY_AI:
            DrawTriangle(
                    {position.x - fieldSize / 2, position.y + fieldSize / 2}, // Bottom left
                    {position.x + fieldSize / 2, position.y + fieldSize / 2}, // Bottom right
                    {position.x, position.y - fieldSize / 2}, // Top
                    RED
                    );
            break;
    }
}

