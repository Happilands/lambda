//
// Created by daanp on 07/02/2024.
//

#include "Variable.h"
#include "Lambda.h"

std::shared_ptr<Expression> Variable::createCopy() {
    if(copyInProgress)
        return copyInProgress->getVariable();
    else {
        return shared_from_this();
    }
}