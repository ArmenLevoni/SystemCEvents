//
//  ShaderTest.cpp
//  SystemCEvents
//
//  Created by Armen Khachatryan on 03/10/2019.
//  Copyright © 2019 Armen Khachatryan. All rights reserved.
//

#include "ShaderTest.hpp"
#include "shader.hpp"


int main_1 () {
    
    Shader s;
    std::vector<std::string> stringList = {"LD r0 #15", "LD r1 #15", "ADD r0 r0 r1", "ST r0 #15"};
    s.createShaderFromList(stringList);
    s.pirntShader();
    return 0;
}
