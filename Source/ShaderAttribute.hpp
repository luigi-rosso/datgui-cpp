#ifndef _SPLITCELL_DATGUI_SHADERATTRIBUTE_HPP_
#define _SPLITCELL_DATGUI_SHADERATTRIBUTE_HPP_

#include <string>

namespace splitcell
{
    namespace datgui
    {
        class ShaderProgram;
        class ShaderAttribute
        {
            friend class ShaderProgram;

            private:
                std::string m_Name;
                int m_Position;
                unsigned int m_Size;
                unsigned int m_Stride;
                unsigned int m_StrideInBytes;
                unsigned int m_Offset;
                float* m_BufferPosition;
                
                ShaderAttribute(const ShaderAttribute& attribute, int position) : m_Name(attribute.m_Name), m_Position(position), m_Size(attribute.m_Size), m_Stride(attribute.m_Stride), m_StrideInBytes(attribute.m_StrideInBytes), m_Offset(attribute.m_Offset), m_BufferPosition(attribute.m_BufferPosition)
                {
                }

            public:
                ShaderAttribute(std::string name, unsigned int size, unsigned int stride, unsigned int offset) : m_Name(name), m_Position(-1), m_Size(size), m_Stride(stride), m_StrideInBytes(stride*sizeof(float)), m_Offset(offset)
                {
                    float* buffer = NULL;
                    m_BufferPosition = buffer+offset;
                }

                inline std::string Name()
                {
                    return m_Name;
                }

                inline unsigned int Size()
                {
                    return m_Size;
                }

                inline unsigned int Stride()
                {
                    return m_Stride;
                }

                inline unsigned int StrideInBytes()
                {
                    return m_StrideInBytes;
                }

                inline unsigned int Offset()
                {
                    return m_Offset;
                }

                inline int Position()
                {
                    return m_Position;
                }

                inline void Position(int p)
                {
                    m_Position = p;
                }

                inline float* BufferPosition()
                {
                    return m_BufferPosition;
                }
        };
    }
}

#endif