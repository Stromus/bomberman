/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_DIRECTORY_HPP
#define INDIE_STUDIO_DIRECTORY_HPP

#include <sys/types.h>
#include <string>
#include <vector>

#ifdef __unix__
 #include <dirent.h>

#elif _WIN32
 #include <windows.h>
 #include <tchar.h>
 #include <strsafe.h>
 #pragma comment(lib, "User32.lib")

#endif

class Directory {

public:
	explicit Directory(const std::string &path);
	~Directory();

public:
	static bool	isDir(const std::string &path);
	void		updateDir();
	bool		isDirOpen();
	bool		containFile(const std::string &file);

	std::vector<std::string>	getFilesOfDir();
	std::string			getPathOfDir();

private:
	void	readDir();

private:
#ifdef __unix__
	DIR				*_dir;
#elif _WIN32
	WIN32_FIND_DATA	_ffd;
	HANDLE			_file;
	TCHAR			_dir[MAX_PATH];
#endif
	std::string			_path;
	std::vector <std::string>	_files;
};

#endif //INDIE_STUDIO_DIRECTORY_HPP
