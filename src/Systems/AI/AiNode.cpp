//
// Created by 22max on 08.01.2023.
//

#include "AiNode.h"

AiNode::AiNode()
{
    parent = nullptr;
    isAiTurn = true;
}

AiNode::AiNode(std::shared_ptr<AiNode> parentNode)
{
    parent = parentNode;

    planningBoard.fields = parent->planningBoard.fields;

    isAiTurn = !parentNode->isAiTurn;
}

