#ifndef _SPLITCELL_DATGUI_SHADERPROGRAM_HPP_
#define _SPLITCELL_DATGUI_SHADERPROGRAM_HPP_

#ifndef _SPLITCELL_DATGUI_SHADER_HPP_
#include "Shader.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_SHADERATTRIBUTE_HPP_
#include "ShaderAttribute.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_MEMORYFILE_HPP_
#include "MemoryFile.hpp"
#endif

#include <string>
#include <vector>

namespace splitcell
{
    namespace datgui
    {
        typedef std::string ShaderUniform;
        class ShaderProgram
        {
            unsigned int m_Id;
            Shader* m_VertexShader;
            Shader* m_FragmentShader;

            std::vector<ShaderAttribute*> m_Attributes;
            std::vector<int> m_Uniforms;

            public:
                ShaderProgram();
                ~ShaderProgram();
                void unload();

            public:
                bool load(MemoryFile* vertexShader, MemoryFile* fragmentShader, std::vector<ShaderAttribute> attributes, std::vector<ShaderUniform> uniforms);
                void bind();
                void unbind();

                inline int uniform(int i) 
                {
                    return m_Uniforms[i]; 
                }
        };
    }
}

#endif