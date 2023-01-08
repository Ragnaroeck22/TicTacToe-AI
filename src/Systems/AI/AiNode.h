//
// Created by 22max on 08.01.2023.
//

#pragma once

#include <memory>
#include <vector>
#include "../Board.h"

class AiNode {

public:

    Board planningBoard;

    std::vector<std::shared_ptr<AiNode>> children;
    std::shared_ptr<AiNode> parent;
    bool isAiTurn;

    int nodeScore = 0;


public:
    AiNode(); // Constructor FOR THE ROOT NODE ONLY
    AiNode(std::shared_ptr<AiNode> parentNode);

};
