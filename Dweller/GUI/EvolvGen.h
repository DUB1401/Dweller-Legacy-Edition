#pragma once

#pragma warning(disable : 4018)
#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#pragma warning(disable : 4305)

#define Wout std::wcout
#define Cout std::cout
#define Endl std::endl
#define Cin std::cin


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <map>

// Перечисления и типы данных.
namespace DUBLIB {

	// Стандартные цвета, доступные для установки в консоль Windows.
	enum class CMD_Colors { clBlack = 0, clBlue, clGreen, clCyan, clRed, clMagenta, clBrown, clLightGray, clDarkGrey, clLightBlue, clLightGreen, clLightCyan, clLightRed, clLightMagenta, clYellow, clWhite };

	// Типы строковых кодировок.
	enum class Encodings { ANSI = 0, UTF8, UTF16, UTF32 };

}

// Преобразование и анализ типов данных.
namespace DUBLIB {

	// Преобразование целочисленного значения в строковое.
	std::string ConvertNumberToString(int Value);

	// Преобразовывает std::string в std::wstring.
	std::wstring ToWstring(std::string Str);

	// Преобразовывает std::wstring в std::string.
	std::string ToString(std::wstring Str, Encodings FromEncoding);

	// Инвертирование значения переменной типа bool.
	bool InvertBool(bool Value);
}

// Работа со строками.
namespace DUBLIB {

	// Удаляет указанное число символов с начала строки (ASCII).
	std::string DeleteFirstCharacters(std::string Str, unsigned int Amount);

	// Удаляет указанное число символов с начала строки (Unicode).
	std::wstring DeleteFirstCharacters(std::wstring Str, unsigned int Amount);

	// Удаляет указанное число символов с конца строки (ASCII).
	std::string DeleteLastCharacters(std::string Str, unsigned int Amount);

	// Удаляет указанное число символов с конца строки (Unicode).
	std::wstring DeleteLastCharacters(std::wstring Str, unsigned int Amount);

	// Удаляет пробелы и символы табуляции из начала и конца строки (ASCII).
	std::string Trim(std::string Str);

	// Удаляет пробелы и символы табуляции из начала и конца строки (Unicode).
	std::wstring Trim(std::wstring Str);

	// Обрезает строку до указанной длины (ASCII). 
	std::string CutToLength(std::string Str, unsigned int Length);

	// Обрезает строку до указанной длины (Unicode). 
	std::wstring CutToLength(std::wstring Str, unsigned int Length);

	// Проверяет посимвольно соответствие первой строки второй строке. Если первая строка длиннее второй, то усекает её до одинаковой длины (ASCII).
	bool CheckForSimilarity(std::string FirstStr, std::string SecondStr);

	// Проверяет посимвольно соответствие первой строки второй строке. Если первая строка длиннее второй, то усекает её до одинаковой длины (Unicode).
	bool CheckForSimilarity(std::wstring FirstStr, std::wstring SecondStr);

	// Разбивает строку по вхождению символа на подстроки (ASCII).
	std::vector<std::string> Split(std::string Str, char Marker);

	// Разбивает строку по вхождению символа на подстроки (Unicode).
	std::vector<std::wstring> Split(std::wstring Str, wchar_t Marker);

}

// Математические функции.
namespace DUBLIB {

	// Возвращает максимальные коэффициенты масштабирования изображения для пропорционального увеличения по оси Y.
	sf::Vector2f CalculateScaleY(sf::Vector2u FormSize, sf::Vector2u PictureSize, double DesiredRelatioToForm);

}

// Методы работы с текстовыми файлами Evolv.
namespace DUBLIB {

	// Возвращает значение первого найденного маркера в файле (ASCII).
	std::string GetMarkeredStringFromFile(std::string File, std::string Marker);

	// Возвращает значение первого найденного маркера в файле (UTF-16).
	std::wstring GetMarkeredStringFromFile(std::wstring File, std::wstring Marker);

	// Возвращает целочисленное значение первого найденного маркера в файле (ASCII).
	int GetMarkeredIntFromFile(std::string File, std::string Marker);

	// Возвращает целочисленное значение первого найденного маркера в файле (UTF-16).
	int GetMarkeredIntFromFile(std::wstring File, std::wstring Marker);

	// Возвращает значение первого найденного маркера в файле и форматирует его в bool (ASCII).
	bool GetMarkeredBoolFromFile(std::string File, std::string Marker);

	// Возвращает значение первого найденного маркера в файле и форматирует его в bool (UTF-16).
	bool GetMarkeredBoolFromFile(std::wstring File, std::wstring Marker);

	// Возвращает вектор строк с соответствующим маркером (ASCII).
	std::vector<std::string> GetMarkeredStringsArrayFromFile(std::string File, std::string Marker);

	// Возвращает вектор строк с соответствующим маркером (UTF-16).
	std::vector<std::wstring> GetMarkeredStringsArrayFromFile(std::wstring File, std::wstring Marker);

}

// Debug-функции.
namespace DUBLIB {

	// Выводит в консоль содержимое вектора (std::string).
	void PrintVector(std::vector<std::string> Value);

	// Выводит в консоль содержимое вектора (std::wstring).
	void PrintVector(std::vector<std::wstring> Value);

	// Выводит в консоль содержимое вектора (unsigned int).
	void PrintVector(std::vector<unsigned int> Value);

}

// Методы работы с Windows.
namespace DUBLIB {

	// Задаёт цвет текста консоли.
	void SetWindowsConsoleColor(CMD_Colors TextColor);

}