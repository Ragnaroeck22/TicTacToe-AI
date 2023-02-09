//
// Created by 22max on 09.02.2023.
//

#include "Functions.h"


void CopyBoardFields(Board &readFrom, Board &writeTo)
{
    for (int i = 0; i < readFrom.fields.size(); i++)
    {
        writeTo.fields[i]->state = readFrom.fields[i]->state;
    }
}
