/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <exception>
#include <algorithm>
#include <iostream>
#include "open_target/Directory.hpp"
#include "exception/SettingsException.hpp"

#ifdef __unix__
 #include <sys/stat.h>
#endif

/*======================= Constructor =========================*/
#ifdef __unix__
Directory::Directory(const std::string &path)
	: _dir(nullptr),
	_path(path),
	_files()
{
	_dir = opendir(_path.c_str());
	if (_dir == nullptr)
		throw ise::SettingsException(ise::WARNING, "Can't open directory: '" + path + "'");
	readDir();
}
#elif _WIN32
Directory::Directory(const std::string &path)
{
	std::string	searchPath = path + "\\*";

	_file = ::FindFirstFile(searchPath.c_str(), &_ffd);
	if (_file == INVALID_HANDLE_VALUE)
		throw ise::SettingsException(ise::WARNING, "Can't open directory: '" + path + "'");
	readDir();
}
#endif

/*======================= Destructor =========================*/
#ifdef __linux__
Directory::~Directory()
{
	if (isDirOpen())
		closedir(_dir);
}
#elif _WIN32
Directory::~Directory()
{}
#endif

/*======================= updateDir =========================*/
#ifdef __unix__
void Directory::updateDir()
{
	_files.clear();
	rewinddir(_dir);
	readDir();
}
#elif _WIN32
void Directory::updateDir()
{
	_files.clear();
	readDir();
}
#endif

/*======================= readDir =========================*/
#ifdef __unix__
void Directory::readDir()
{
	struct dirent	*entry;

	while ((entry = readdir(_dir)) != nullptr)
		if (entry->d_type == DT_REG)
			_files.push_back(entry->d_name);
}
#elif _WIN32
void Directory::readDir()
{
	do
	{
		if (!(_ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			_files.push_back(_ffd.cFileName);
	} while (::FindNextFile(_file, &_ffd) != 0);
	::FindClose(_file);
}
#endif

/*======================= isDir =========================*/

#ifdef __unix__
bool Directory::isDir(const std::string &path)
{
	struct	stat s;

	return stat(path.c_str(), &s) == 0 && s.st_mode & S_IFDIR;
}
#elif _WIN32
bool Directory::isDir(const std::string &path)
{
	DWORD ftyp = GetFileAttributesA(path.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;
	return ftyp & FILE_ATTRIBUTE_DIRECTORY;
}
#endif

/*======================= Both Compatibility ===============*/
bool Directory::containFile(const std::string &fileName)
{
	return std::find(_files.begin(), _files.end(), fileName) != _files.end();
}

std::vector<std::string> Directory::getFilesOfDir()
{
	return _files;
}

std::string Directory::getPathOfDir()
{
	return _path;
}

bool Directory::isDirOpen()
{
	return _dir != nullptr;
}