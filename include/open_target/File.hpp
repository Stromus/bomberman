/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_FILE_HPP
#define INDIE_STUDIO_FILE_HPP

#include <string>
#include <fstream>
#include <sstream>

class File {
public:
	enum fileMode {
		F_OUT = 0,
		F_IN = 1,
	};

	explicit File(const std::string &path, const fileMode &mode);
	~File();

private:
	bool	isOpen() const noexcept;

public:
	std::stringstream	getContent() const noexcept;
	void			writeContent(const std::string &line) noexcept;
	static bool		isFile(const std::string &path);

private:
	std::string		_path;
	fileMode		_mode;
	std::fstream		_fs;
};

#endif //INDIE_STUDIO_FILE_HPP
