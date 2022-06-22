#pragma once

class IndexBuffer
{
private:
    unsigned int m_ModuleID;
    const void* data;
public:
    IndexBuffer(const unsigned int* data, unsigned int count, unsigned int mode);
    ~IndexBuffer();

    unsigned int getID() { return m_ModuleID; }
    void Bind() const;
	void Unbind() const;
};