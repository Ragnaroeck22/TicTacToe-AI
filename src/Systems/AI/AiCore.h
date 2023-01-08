//
// Created by 22max on 08.01.2023.
//

#pragma once

#include "AiNode.h"

class AiCore {

public:
    std::shared_ptr<AiNode> currentNode;



public:

    AiCore();
    void Update();
    void Draw();

    int calcNodeScores(std::shared_ptr<AiNode> rootNode);

};


