/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <exception>
#include "open_target/File.hpp"
#include "exception/SettingsException.hpp"

#ifdef __unix__
 #include <sys/stat.h>
#endif


File::File(const std::string &path, const fileMode &mode)
	: _path(path),
	_mode(mode)
{
	if (mode == F_IN)
		_fs.open(path, std::fstream::in);
	else
		_fs.open(path, std::fstream::out | std::fstream::trunc);
	if (!isOpen())
		throw ise::SettingsException(ise::WARNING, "Can't open file '" + path + "'");
}

File::~File()
{
	if (isOpen())
		this->_fs.close();
}

bool File::isOpen() const noexcept
{
	return _fs.is_open();
}

std::stringstream File::getContent() const noexcept
{
	std::stringstream	stream;

	stream << _fs.rdbuf();
	return stream;
}

/*========================= isFile =======================*/
#ifdef __unix__
bool File::isFile(const std::string &path)
{
	struct	stat s;

	return stat(path.c_str(), &s) == 0 && s.st_mode & S_IFREG;
}
#elif _WIN32
bool File::isFile(const std::string &path)
{
	std::fstream	fs;
	fs.open(path.c_str());
	if (fs.rdstate() == std::ios_base::failbit)
		return false;
	fs.close();
	return true;
}
#endif

void File::writeContent(const std::string &line) noexcept
{
	_fs << line;
}