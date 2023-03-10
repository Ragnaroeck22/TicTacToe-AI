#include <cstdlib>

#include "raylib.h"

#include "config.h"

#include <string>

#include "Functions.h"
#include "Systems/Board.h"
#include "Systems/AI/AiCore.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // ======== INIT ========

    Board board;
    AiCore ai;

    TraceLog(LOG_INFO, std::to_string(board.fields[8]->state).c_str());

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // ======== UPDATE ========

        board.Update();


        if (!board.playerWon && !board.AIWon)
        {
            // Execute AI-Turn

            if (!board.playerTurn)
            {
                // Setup root node
                ai.rootNode = std::make_shared<AiNode>();
                CopyBoardFields(board, ai.rootNode->planningBoard);


                // Calculate child scores (generate node tree)
                ai.rootNode->nodeScore = ai.calcNodeScores(ai.rootNode);

                // Determine best child (child with highest score)
                std::shared_ptr<AiNode> bestChild = ai.rootNode->children[0];


                for (int i = 0; i < ai.rootNode->children.size(); i++)
                {
                    if (ai.rootNode->children[i]->nodeScore > bestChild->nodeScore)
                        bestChild = ai.rootNode->children[i];
                }

                // Make a move
                CopyBoardFields(bestChild->planningBoard, board);

                // AI turn over
                board.playerTurn = true;

                if (board.winConditionMet(MARKED_BY_AI))
                {
                    board.AIWon = true;
                }




            }
        }

        // ======== DRAW ========
        BeginDrawing();
            ClearBackground(BLACK);


            board.Draw();

            if (board.playerWon)
            {
                DrawTextEx(GetFontDefault(), "PLAYER WON",
                           {GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "PLAYER WON", 30, 1).x / 2,
                            GetScreenHeight() / 2 - MeasureTextEx(GetFontDefault(), "PLAYER WON", 30, 1).y / 2},
                            30, 1, GREEN);
            }

        if (board.AIWon)
        {
            DrawTextEx(GetFontDefault(), "AI WON",
                       {GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "AI WON", 30, 1).x / 2,
                        GetScreenHeight() / 2 - MeasureTextEx(GetFontDefault(), "AI WON", 30, 1).y / 2},
                       30, 1, GREEN);
        }


        EndDrawing();
    } // Main game loop end

    // ======== DE-INIT ========

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
