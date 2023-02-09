//
// Created by 22max on 07.01.2023.
//

#include "Board.h"

Board::Board()
{
    // generate fields
    for (int i = 0; i < 9; i++)
    {
        fields.push_back(std::make_shared<Field>());
    }

    // init field recs
    fieldSize = GetScreenWidth() * 0.3;
    Vector2 startPos = {static_cast<float>(GetScreenWidth() * 0.025), static_cast<float>(GetScreenHeight() * 0.025)};
    Rectangle helperRec = {startPos.x, startPos.y, fieldSize, fieldSize};
    for (int i = 0; i < 9; i++)
    {
        fieldRecs.push_back(helperRec);
        if (i == 2 || i == 5 || i == 8) // If the end of a line has been reached, advance column
        {
            helperRec.x = startPos.x;
            helperRec.y = helperRec.y + fieldSize + GetScreenHeight() * 0.025;
        }
        else
        {
            helperRec.x = helperRec.x + fieldSize + GetScreenWidth() * 0.025;
        }
    }


}

void Board::Update()
{

    // Check hover
    drawHover = false;
    for (int i = 0; i < fieldRecs.size(); i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), fieldRecs[i]))
        {
            fieldHovered = i;
            drawHover = true;
        }
    }

    // Execute player turn
    if (playerTurn)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && drawHover == true) // If hovered field is clicked
        {
            if (fields[fieldHovered]->state == UNMARKED)
            {
                fields[fieldHovered]->state = MARKED_BY_PLAYER;
                if (winConditionMet(MARKED_BY_PLAYER))
                {
                    playerWon = true;
                }
                playerTurn = false;
            }
        }
    }


}

void Board::Draw()
{

    for (int i = 0; i < fieldRecs.size(); i++)
    {
        DrawRectangleRec(fieldRecs[i], WHITE);
    }


    for (int i = 0; i < fields.size(); i++)
    {
        fields[i]->Draw({fieldRecs[i].x + fieldSize / 2, fieldRecs[i].y + fieldSize / 2}, fieldSize * 0.8);
    }

    // Draw hover
    if (drawHover)
    {
        DrawRectangleRec(fieldRecs[fieldHovered], ColorAlpha(BLACK, 0.5));
    }
}

bool Board::winConditionMet(FieldState side)
{
    // This is bullshit

    // player
    if (side == MARKED_BY_PLAYER)
    {
        // center
        if (fields[4]->state == MARKED_BY_PLAYER)
        {
            // Dia top left to bottom right
            if (fields[0]->state == MARKED_BY_PLAYER && fields[8]->state == MARKED_BY_PLAYER)
                return true;

            // Dia top right to bottom left
            if (fields[2]->state == MARKED_BY_PLAYER && fields[6]->state == MARKED_BY_PLAYER)
                return true;

            // Center left to right
            if (fields[3]->state == MARKED_BY_PLAYER && fields[5]->state == MARKED_BY_PLAYER)
                return true;

            // Center top to bottom
            if (fields[1]->state == MARKED_BY_PLAYER && fields[7]->state == MARKED_BY_PLAYER)
                return true;
        }
        // top right
        if (fields[2]->state == MARKED_BY_PLAYER)
        {
            // Top
            if (fields[1]->state == MARKED_BY_PLAYER && fields[0]->state == MARKED_BY_PLAYER)
                return true;

            // Right
            if (fields[2]->state == MARKED_BY_PLAYER && fields[8]->state == MARKED_BY_PLAYER)
                return true;
        }
        // bottom left
        if (fields[6]->state == MARKED_BY_PLAYER)
        {
            // Bottom
            if (fields[7]->state == MARKED_BY_PLAYER && fields[8]->state == MARKED_BY_PLAYER)
                return true;

            // Left
            if (fields[3]->state == MARKED_BY_PLAYER && fields[0]->state == MARKED_BY_PLAYER)
                return true;
        }
        return false;
    }
    // AI
    else
    {
        // center
        if (fields[4]->state == MARKED_BY_AI)
        {
            // Dia top left to bottom right
            if (fields[0]->state == MARKED_BY_AI && fields[8]->state == MARKED_BY_AI)
                return true;

            // Dia top right to bottom left
            if (fields[2]->state == MARKED_BY_AI && fields[6]->state == MARKED_BY_AI)
                return true;

            // Center left to right
            if (fields[3]->state == MARKED_BY_AI && fields[5]->state == MARKED_BY_AI)
                return true;

            // Center top to bottom
            if (fields[1]->state == MARKED_BY_AI && fields[7]->state == MARKED_BY_AI)
                return true;
        }
        // top right
        if (fields[2]->state == MARKED_BY_AI)
        {
            // Top
            if (fields[1]->state == MARKED_BY_AI && fields[0]->state == MARKED_BY_AI)
                return true;

            // Right
            if (fields[2]->state == MARKED_BY_AI && fields[8]->state == MARKED_BY_AI)
                return true;
        }
        // bottom left
        if (fields[6]->state == MARKED_BY_AI)
        {
            // Bottom
            if (fields[7]->state == MARKED_BY_AI && fields[8]->state == MARKED_BY_AI)
                return true;

            // Left
            if (fields[3]->state == MARKED_BY_AI && fields[0]->state == MARKED_BY_AI)
                return true;
        }
        return false;
    }
}
