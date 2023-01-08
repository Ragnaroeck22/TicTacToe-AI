//
// Created by 22max on 08.01.2023.
//

#include "AiCore.h"

AiCore::AiCore()
{

}

void AiCore::Update()
{

     for (int i = 0; i < 9; i++)
     {
         if (currentNode->planningBoard.fields[i]->state == UNMARKED)
         {


         }
     }

}

void AiCore::Draw()
{

}

int AiCore::calcNodeScores(std::shared_ptr<AiNode> rootNode)
{
    bool matchTie = true;

    if (currentNode->planningBoard.winConditionMet(MARKED_BY_AI))
    {
        return 1;
    }
    if (currentNode->planningBoard.winConditionMet(MARKED_BY_PLAYER))
    {
        return -1;
    }

    // Set all possible children
    for (int i = 0; i < 9; i++)
    {
        if (currentNode->planningBoard.fields[i]->state == UNMARKED)
        {
            matchTie = false; // If a node can be placed, the match can't be a tie
            rootNode->children.push_back(std::make_shared<AiNode>(currentNode));
            if (rootNode->children.back()->isAiTurn)
            {
                rootNode->children.back()->planningBoard.fields[i]->state = MARKED_BY_AI;
            }
        }
    }

    if (matchTie) // If no winning conditions were met and no fields could be marked, the match is a tie
    {
        return 0;
    }


    // If no winning condition / tie is met, calc score based on all the children's scores
    // (That's the recursive part)
    for (int i = 0; i < currentNode->children.size(); i++)
    {
        currentNode->nodeScore = currentNode->nodeScore + calcNodeScores(currentNode->children[i]);
    }



}

