//
// Created by 22max on 08.01.2023.
//

#include "AiCore.h"

AiCore::AiCore()
{

}

void AiCore::Update()
{


}

void AiCore::Draw()
{

}

int AiCore::calcNodeScores(std::shared_ptr<AiNode> currentNode)
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
        // If the checked field is unmarked, create a child with a mark of the respective color (AI or Player)
        if (currentNode->planningBoard.fields[i]->state == UNMARKED)
        {
            matchTie = false; // If a node can be placed, the match can't be a tie

            //std::shared_ptr<AiNode> helper;
            currentNode->children.push_back(std::make_shared<AiNode>(currentNode));
            //helper = std::make_shared<AiNode>(currentNode);



            if (currentNode->isAiTurn)
            {
                currentNode->children.back()->planningBoard.fields[i]->state = MARKED_BY_AI;
                //helper->planningBoard.fields[i]->state = MARKED_BY_AI;
            }
            else
            {
                currentNode->children.back()->planningBoard.fields[i]->state = MARKED_BY_PLAYER;
                //helper->planningBoard.fields[i]->state = MARKED_BY_PLAYER;
            }
            //currentNode->children.push_back(helper);
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

    // Return the final score for further assessment
    return currentNode->nodeScore;

}

