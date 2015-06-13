#include "Shader.hpp"

#include "OpenGL.hpp"
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace splitcell::datgui;

Shader::Shader(const char* filename, unsigned char* buffer, unsigned int length) : m_Id(0)
{
    long len = strlen( filename );

    int type = -1;
    if( strcmp( filename + len - 3, ".fs" ) == 0 )
    {
        type = GL_FRAGMENT_SHADER;
    }
    else if( strcmp( filename + len - 3, ".vs" ) == 0 )
    {
        type = GL_VERTEX_SHADER;
    }

    m_Id = glCreateShader(type);  

    std::string shaderData((const char*)buffer, length);
#ifdef PREFIX_SHADER_GL_VERSION
    shaderData = std::string("#version 120\n") + shaderData;
    const char* data = shaderData.c_str();
    glShaderSource(m_Id, 1, (const char**)&data, NULL);
#else
    const char* data = shaderData.c_str();
    glShaderSource(m_Id, 1, (const char**)&data, NULL);
#endif
        
    glCompileShader(m_Id);
    
    int status;
    
    glGetShaderiv(m_Id, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        char infobuffer[2048];
        int infobufferlen = 0;
        glGetShaderInfoLog(m_Id, 2047, &infobufferlen, infobuffer);
        infobuffer[infobufferlen] = 0;
        if( infobufferlen != 0 )
        {
            if( strstr( infobuffer, "error" ) == NULL )
            {
                printf("Shader::Load - warnings from GLSL while compiling '%s'\n", filename);
                printf("-----------------------------------------------------------------------\n");
                printf("%s", infobuffer);
                printf("");
            }
            else
            {
                printf("Shader::Load - errors from GLSL while compiling '%s'\n", filename);
                printf("-----------------------------------------------------------------------\n");
                printf("%s\n", infobuffer);
                printf("\n");
            }
        }
    }
}

Shader::~Shader()
{
    if(m_Id != 0)
    {
        glDeleteShader( m_Id );
    }
}