//
//  shader.hpp
//  SystemCEvents
//
//  Created by Armen Khachatryan on 03/10/2019.
//  Copyright © 2019 Armen Khachatryan. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <stdio.h>
#include <vector>
#include "instruction.hpp"
#include <iostream>

class Shader {
    
    std::vector<Instruction> instructions;
    
public:
    Shader () {}
    
    void createShaderFromList (std::vector<std::string> stringList) {
        for (int i=0; i< stringList.size(); i++){
            instructions.push_back(Instruction(stringList[i]));
        }
    }
    
    void pirntShader () {
        std::cout << "The shader is: " << std::endl;
        for (int i=0; i< instructions.size(); i++){
            std::cout << instructions[i].getInstructionName() << std::endl;
        }
    }
    
    Instruction getInstruction (unsigned int index) {
        if (index > instructions.size()) {
            std::cerr << "Instruction index: " << index << " is bigger then shader size";
            exit(1);
        } else {
            return instructions[index];
        }
    }
    
private:
    
};
#endif /* shader_hpp */
