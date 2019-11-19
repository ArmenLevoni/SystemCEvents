//
//  icache.hpp
//  SystemCEvents
//
//  Created by Armen Khachatryan on 02/10/2019.
//  Copyright © 2019 Armen Khachatryan. All rights reserved.
//

#ifndef icache_hpp
#define icache_hpp
#include <systemc.h>
#include <stdio.h>
#include <array>
#include <map>
#include "shader.hpp"

SC_MODULE(ICache) {

public:
    
    std::map <unsigned int, Shader> shaders;
    
    void before_end_of_elaboration() {

    }
    

    SC_CTOR(ICache)    {
        SC_THREAD(process);
    }
    
    void addShader (unsigned int pc, Shader sr) {
        shaders[pc] = sr;
    }

    void addShaderFromList (unsigned int pc, std::vector<std::string> stringList) {
        Shader s;
        s.createShaderFromList(stringList);
        shaders[pc] = s;
    }

    Instruction getInstrucion (unsigned int initialPc, unsigned int index) {
        if (shaders.find(initialPc) == shaders.end()) {
            std::cerr << "Shader PC: " << initialPc << " does not exist.";
            exit(1);
        } else {
            return shaders[initialPc].getInstruction(index);
        }
    }
    
    Instruction getDelayedInstruction (unsigned int initialPc, unsigned int index) {
        wait(1);
        return getInstrucion(initialPc, index);;
    }
    
    void process() {

    }

private:
    
};
#endif /* icache_hpp */
