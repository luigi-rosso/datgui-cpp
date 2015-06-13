#include "ShaderProgram.hpp"
#include "OpenGL.hpp"
#include <stdio.h>

using namespace splitcell::datgui;

ShaderProgram::ShaderProgram() : m_Id(0), m_VertexShader(NULL), m_FragmentShader(NULL)
{

}

void ShaderProgram::unload()
{
    if(m_Id)
    {
        if(m_VertexShader)
        {
            glDetachShader(m_Id, m_VertexShader->id());
        }
        if(m_FragmentShader)
        {
            glDetachShader(m_Id, m_FragmentShader->id());
        }
        
        glDeleteProgram(m_Id);
    }

    for(auto a : m_Attributes)
    {
        delete a;
    }

    m_Attributes.clear();
    m_Uniforms.clear();

    delete m_VertexShader;
    delete m_FragmentShader;
}

bool ShaderProgram::load(MemoryFile* vertexShader, MemoryFile* fragmentShader, std::vector<ShaderAttribute> attributes, std::vector<ShaderUniform> uniforms)
{
    unload();
    
    m_FragmentShader = new Shader(fragmentShader->name(), fragmentShader->bytes(), fragmentShader->size());
    m_VertexShader = new Shader(vertexShader->name(), vertexShader->bytes(), vertexShader->size());
    
    m_Id = glCreateProgram();
    glAttachShader(m_Id, m_VertexShader->id());
    glAttachShader(m_Id, m_FragmentShader->id());
    glLinkProgram(m_Id);
    glUseProgram(m_Id);

    for(auto a : attributes)
    {
        int location = glGetAttribLocation(m_Id, a.Name().c_str());
        if(location == -1)
        {
            printf("ShaderProgram::load - couln't find attribute %s (%s | %s).\n", a.Name().c_str(), vertexShader->name(), fragmentShader->name());
        }
        m_Attributes.push_back(new ShaderAttribute(a, location));
    }

    for(auto u : uniforms)
    {
        int l = glGetUniformLocation(m_Id, u.c_str());
        if(l == -1)
        {
            printf("ShaderProgram::load - couln't find uniform %s (%s | %s).\n", u.c_str(), vertexShader->name(), fragmentShader->name());
        }
        m_Uniforms.push_back(l);
    }

    return true;
}

ShaderProgram::~ShaderProgram()
{
    unload();	
}

void ShaderProgram::bind()
{
    glUseProgram(m_Id);
    for(auto a : m_Attributes)
    {
        if(a->Position() == -1)
        { 
            continue;
        }
        glEnableVertexAttribArray(a->Position());
        glVertexAttribPointer(a->Position(), a->Size(), GL_FLOAT, GL_FALSE, a->StrideInBytes(), a->BufferPosition());
    }
}

void ShaderProgram::unbind()
{
    for(auto a : m_Attributes)
    {
        if(a->Position() == -1)
        { 
            continue;
        }
        glDisableVertexAttribArray(a->Position());
    }
}