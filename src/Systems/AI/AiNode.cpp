//
// Created by 22max on 08.01.2023.
//

#include "AiNode.h"

#include "../../Functions.h"

AiNode::AiNode()
{
    parent = nullptr;
    isAiTurn = true;
}

AiNode::AiNode(std::shared_ptr<AiNode> parentNode)
{
    parent = parentNode;

    CopyBoardFields(parent->planningBoard, planningBoard);

    isAiTurn = !parentNode->isAiTurn;
}

