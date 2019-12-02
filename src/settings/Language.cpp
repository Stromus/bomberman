/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by simong,
*/

#include <algorithm>
#include "settings/Settings.hpp"
#include "open_target/File.hpp"
#include "exception/SettingsException.hpp"
#include "settings/Language.hpp"

Language	Language::singleton;

Language *Language::getInstance()
{
	return &singleton;
}

Language::Language()
	: _actual(EN), _isUpdated(false)
{
	try {
		setLanguages();
		setTranslation(_actual);
	}
	catch (const ise::SettingsException &error) {
		exit(84);
	}
}

void Language::setLanguages()
{
	try {
		File file("res/lang/languages.txt", File::fileMode::F_IN);
		std::stringstream stream = file.getContent();
		std::string line;

		while (getline(stream, line))
			fillLangStruct(line);
	}
	catch (const ise::SettingsException &error) {
		std::cerr << error.what() << std::endl;
	}
}

bool Language::isUnicodeAlreadyExist(const std::string &line) const noexcept
{
	for (auto &lang : _languages) {
		if (lang.code == _corresToLanguageCode.at(line))
			return true;
	}
	return false;
}

void Language::checkSeparator(const std::string &line, const int &nb) const
{
	if (std::count(line.begin(), line.end(), ':') != nb)
		throw ise::SettingsException(ise::CONFIGURATION, \
			"In res/lang/languages.txt: \"" + line + """\": need 2 ':' separator.\t[LINE SKIPPED]\"");
}

void Language::checkUnicode(const std::string &unicode) const
{
	if (_corresToLanguageCode.find(unicode) == _corresToLanguageCode.end())
		throw ise::SettingsException(ise::CONFIGURATION, \
			"In res/lang/languages.txt: \"" + unicode + """\": Invalid language's unicode.\t[LINE SKIPPED]\"");
	if (isUnicodeAlreadyExist(unicode))
		throw ise::SettingsException(ise::CONFIGURATION, \
			"In res/lang/languages.txt: \"" + unicode + """\": Multiple definition of the unicode.\t[LINE SKIPPED]\"");
}


void Language::fillLangStruct(std::string &line)
{
	Lang lang;
	std::string unicode;
	std::string flags;

	try {
		checkSeparator(line, 2);
		unicode = line.substr(0, line.find(':'));
		checkUnicode(unicode);
		line.erase(0, unicode.size() + 1);
		lang.code = _corresToLanguageCode.at(unicode);
		lang.flag = "res/sprite/icon/" + line.substr(0, line.find(':'));
		line.erase(0, line.find(':') + 1);
		lang.path = "res/lang/" + line;
		_languages.push_back(lang);
	}
	catch (const ise::SettingsException &error) {
		std::cerr << error.what() << std::endl;
	}
}

Language::Lang Language::getCorrespondLanguageStruct(const Language::languageCode &langCode) const
{
	for (auto &lang : _languages)
		if (lang.code == langCode)
			return lang;
	exit(84);
}

void Language::checkTextID(const std::string &textid)
{
	if (_corresToTextID.find(textid) == _corresToTextID.end())
		throw ise::SettingsException(ise::CONFIGURATION, "The text ID '" + textid + "' not found.");
	if (_translate.find(_corresToTextID[textid]) != _translate.end())
		throw ise::SettingsException(ise::CONFIGURATION, "The text ID '" + textid + "' already defined.");
}

void Language::checkContainer(const std::string &line) const
{
	if (line.front() != '"' || line.back() != '"' || std::count(line.begin(), line.end(), '"') != 2)
		throw ise::SettingsException(ise::CONFIGURATION, "The translation \"" + line + "\"isn't set inside \"\" like: \"text\".");
}

void Language::checkCodeFile(const std::string &line) const
{
	if (line.size() < 5)
		throw ise::SettingsException(ise::CONFIGURATION, \
			"You need to have \"code:[LanguageCode]\\n\" in the beginning of your file. -- Invalid file.");
	std::string	code = line.substr(0, 5);
	if (code != "code:")
		throw ise::SettingsException(ise::CONFIGURATION, \
			"You need to have \"code:[LanguageCode]\\n\" in the beginning of your file. -- Invalid file.");
	if (_corresToLanguageCode.find(line.substr(5, line.size())) == _corresToLanguageCode.end())
		throw ise::SettingsException(ise::CONFIGURATION, \
			"You need to have \"code:[LanguageCode]\\n\" in the beginning of your file. -- Invalid file.");
}

void Language::setTranslation(const languageCode &langCode)
{
	Lang	lang = getCorrespondLanguageStruct(langCode);
	std::stringstream	stream;
	std::string		line;
	std::string		textId;
	int			i = 1;

	try {
		File file(lang.path, File::fileMode::F_IN);
		stream = file.getContent();
		while (getline(stream, line)) {
			try {
				if (i++ == 1) {
					checkCodeFile(line);
					continue;
				}
				checkSeparator(line, 1);
				textId = line.substr(0, line.find(':'));
				checkTextID(textId);
				line.erase(0, textId.size() + 1);
				checkContainer(line);
				line.erase(0, 1);
				line = line.substr(0, line.size() - 1);
				_translate.insert(std::pair<textID, std::wstring>(
					_corresToTextID.at(textId), stows(line)));
			}
			catch (const ise::SettingsException &error) {
				std::cerr << error.what() << std::endl;
			}
		}
	}
	catch (const ise::SettingsException &error) {
		std::cerr << error.what() << std::endl;
	}
	checkUnloadTranslation();
}

void Language::checkUnloadTranslation() const
{
	for (auto &id : _corresToTextID) {
		try {
			if (_translate.find(id.second) == _translate.end())
				throw ise::SettingsException(ise::CONFIGURATION, ("ID '" + id.first + \
					"' isn't define in the translation: " + std::to_string(_actual)));
		}
		catch (const ise::SettingsException &error) {
			std::cerr << error.what() << std::endl;
		}
	}
}

std::wstring Language::stows(const std::string &in) const noexcept
{
	std::wstring out(in.begin(), in.end());

	return out;
}

const std::wstring Language::getTranslate(const Language::textID &id)
{
	std::wstring translation;

	checkCurrentLoadedLanguage();
	try {
		if (_translate.find(id) == _translate.end())
			throw ise::SettingsException(ise::WARNING, \
				"Can't get the translation associated with id '" + \
				std::to_string(id) + "'");
		translation = _translate.at(id);
	}
	catch (const ise::SettingsException &error) {
		std::cerr << error.what() << std::endl;
	}
	return translation;
}

void Language::checkCurrentLoadedLanguage() noexcept
{
	if (Settings::getInstance()->getLanguage() != _actual) {
		_actual = Settings::getInstance()->getLanguage();
		_translate.clear();
		setTranslation(_actual);
	}
}

Language::languageCode Language::convertStringToCode(const std::string &line)
{
	try {
		return (this->_corresToLanguageCode.at(line));
	}
	catch (const std::out_of_range &e) {
		throw ise::SettingsException(ise::WARNING, "language '" + line + "' do not exist");
	}
}

const std::string &Language::convertCodeToString(const languageCode &code)
{
	for (auto &pairLanguageCode : this->_corresToLanguageCode) {
		if (code == pairLanguageCode.second)
			return (pairLanguageCode.first);
	}
	return (_corresToLanguageCode.find("EN")->first);
}

const std::vector<Language::Lang> Language::getLanguagesList() const noexcept
{
	return this->_languages;
}

void Language::setUpdated(const bool &isUpdated) noexcept
{
	this->_isUpdated = isUpdated;
}

const bool Language::isLanguageUpdated() noexcept
{
	if (_isUpdated) {
		this->_isUpdated = false;
		return (true);
	}
	return (false);
}