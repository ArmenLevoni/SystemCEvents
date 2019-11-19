//
//  instruction.hpp
//  SystemCEvents
//
//  Created by Armen Khachatryan on 03/10/2019.
//  Copyright © 2019 Armen Khachatryan. All rights reserved.
//

#ifndef instruction_hpp
#define instruction_hpp

#include <stdio.h>
#include "transaction.hpp"
#include <string>


class Instruction
{
    
public:
    Instruction(std::string name)  {
        instruction_name = name;
    }
    
    std::string getInstructionName () {
        return instruction_name;
    }
    void setInstructionName (std::string name) {
        instruction_name = name;
    }

private:
    std::string instruction_name;

};

typedef Transaction<Instruction> InstructionTransaction;

#endif /* instruction_hpp */
