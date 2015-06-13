#ifndef _SPLITCELL_DATGUI_SHADER_HPP_
#define _SPLITCELL_DATGUI_SHADER_HPP_

namespace splitcell
{
    namespace datgui
    {
        class Shader
        {
            unsigned int m_Id;
            
            public:
                Shader(const char* name, unsigned char* data, unsigned int length);
                ~Shader();
            
                unsigned int id()
                {
                    return m_Id;
                }
        };
    }
}

#endif