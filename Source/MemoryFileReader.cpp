#include "MemoryFileReader.hpp"

using namespace splitcell::datgui;

static bool isBigEndian(void)
{
    union 
    {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1; 
}


MemoryFileReader::MemoryFileReader(MemoryFile* file) :
	m_File(file),
	m_IsSystemBigEndian(isBigEndian()),
	m_DataPosition(0)
{
}

MemoryFileReader::~MemoryFileReader()
{
}

int MemoryFileReader::readInt()
{
	if(m_DataPosition+4 > m_File->size())
	{
		return 0;
	}

	unsigned char* bytes = &m_File->bytes()[m_DataPosition];
	m_DataPosition += 4;
	
	if(m_IsSystemBigEndian)
	{
		unsigned char sbytes[4] = { bytes[3], bytes[2], bytes[1], bytes[0] };
		return *reinterpret_cast<int*>(sbytes);
	}
	return *reinterpret_cast<int*>(bytes);
}

unsigned int MemoryFileReader::read(unsigned char* bytes, unsigned int length)
{
	unsigned int readCount = 0;
	for(int i = 0; i < length && m_DataPosition < m_File->size(); i++)
	{
		bytes[i] = m_File->bytes()[m_DataPosition];
		m_DataPosition++;
		readCount++;
	}
	return readCount;
}

unsigned int MemoryFileReader::readUnsignedInt()
{
	if(m_DataPosition+4 > m_File->size())
	{
		return 0;
	}
	unsigned char* bytes = &m_File->bytes()[m_DataPosition];
	m_DataPosition += 4;

	if(m_IsSystemBigEndian)
	{
		unsigned char sbytes[4] = { bytes[3], bytes[2], bytes[1], bytes[0] };
		return *reinterpret_cast<unsigned int*>(sbytes);
	}
	return *reinterpret_cast<unsigned int*>(bytes);
}

float MemoryFileReader::readFloat()
{
	if(m_DataPosition+4 > m_File->size())
	{
		return 0;
	}
	unsigned char* bytes = &m_File->bytes()[m_DataPosition];
	m_DataPosition += 4;

	if(m_IsSystemBigEndian)
	{
		unsigned char sbytes[4] = { bytes[3], bytes[2], bytes[1], bytes[0] };
		return *reinterpret_cast<float*>(sbytes);
	}
	return *reinterpret_cast<float*>(bytes);

	return 0;
}

short MemoryFileReader::readShort()
{
	if(m_DataPosition+2 > m_File->size())
	{
		return 0;
	}
	unsigned char* bytes = &m_File->bytes()[m_DataPosition];
	m_DataPosition += 2;

	if(m_IsSystemBigEndian)
	{
		unsigned char sbytes[2] = { bytes[1], bytes[0] };
		return *reinterpret_cast<short*>(sbytes);
	}
	return *reinterpret_cast<short*>(bytes);
}

unsigned short MemoryFileReader::readUnsignedShort()
{
	if(m_DataPosition+2 > m_File->size())
	{
		return 0;
	}
	unsigned char* bytes = &m_File->bytes()[m_DataPosition];
	m_DataPosition += 2;

	if(m_IsSystemBigEndian)
	{
		unsigned char sbytes[2] = { bytes[1], bytes[0] };
		return *reinterpret_cast<unsigned short*>(sbytes);
	}
	return *reinterpret_cast<unsigned short*>(bytes);
}

std::string MemoryFileReader::readString()
{
	unsigned int length = readUnsignedInt();
	std::string str(length, 0);

	if(read((unsigned char*)str.c_str(), length) == length)
	{
		return str;
	}

	return std::string();
}