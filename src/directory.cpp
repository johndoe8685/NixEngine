#include "directory.h"

Directory::Directory(const std::string& path)
	:m_path(path)
{
	processCwd();
	changePath(m_path);
}

Directory::Directory()
{
	processCwd();
}

#ifdef __linux__
void Directory::processCwd()
{
	m_cwd = get_current_dir_name();
}
#endif

#ifdef _WIN64
void Directory::processCwd()
{
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	m_cwd = buff;
}
#endif

void Directory::changePath(std::string path)
{
	m_path = m_cwd + path;
}

std::string Directory::getPath()
{
	return m_path;
}

std::string Directory::getWorkDirectory()
{
	return m_cwd;
}
