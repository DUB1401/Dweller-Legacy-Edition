#pragma once

#include "../EvolvGen.h"

//Хранилище настроек.
class Settings {
private:

	//Универсальный контейнер строк std::string и std::wstring.
	struct Ustring {
	protected:

		//Устанавливает представление строки через std::string.
		void SetString(std::string Str) {
			U_String = Str;
		}
		//Устанавливает представление строки через std::string.
		void SetWstring(std::wstring Str) {
			U_Wstring = Str;
		}
		//Представление строки через std::string.
		std::string U_String;
		//Представление строки через std::wstring.
		std::wstring U_Wstring;

	public:

		//Конструктор: пустой.
		Ustring() {}
		//Конструктор: задаёт строку.
		Ustring(const char* U_String) {
			SetString(U_String);
			SetWstring(DUBLIB::ToWstring(U_String));
		}
		//Конструктор: задаёт строку.
		Ustring(const wchar_t* U_Wstring) {
			SetString(DUBLIB::ToString(U_Wstring, DUBLIB::Encodings::ANSI));
			SetWstring(U_Wstring);
		}
		//Конструктор: задаёт строку.
		Ustring(std::wstring U_Wstring) {
			SetString(DUBLIB::ToString(U_Wstring, DUBLIB::Encodings::UTF8));
			SetWstring(U_Wstring);
		}
		//Возвращает представление строки через std::string.
		std::string AsString() {
			return U_String;
		}
		//Возвращает представление строки через std::wstring.
		std::wstring AsWstring() {
			return U_Wstring;
		}

	};

	//---> Методы работы.
	//=======================================================================================================================//
	//Выводит в консоль bool красного или зелёного цвета соответственно логике и переводит вывод на новую строку.
	void PrintBool(bool Value);
	//Выводит в консоль int голубого цвета.
	void PrintInt(int Value);
	//Переход на новую строку.
	void Empl();

public:

	//---> Версии и объявления.
	//=======================================================================================================================//
	//Версия игры.
	Ustring Version = "1.0.0 pre-alpha";
	//Версия библиотеки SFML.
	Ustring Sfml = "2.5.1";

	//---> Настройки видеовывода.
	//=======================================================================================================================//
	//Ширина окна.
	unsigned int WindowWidth = 1280;
	//Высота окна.
	unsigned int WindowHeight = 720;
	//Активирована ли вертикальная синхронизация.
	bool VerticalSync = false;
	//Лимит FPS.
	unsigned int FramerateLimit = 0;
	//Полноэкранный режим.
	bool Fullscreen = false;
	//Активирован ли счётчик FPS.
	bool ShowFPS = false;

	//---> Настройки окружения игры.
	//=======================================================================================================================//
	//Воспроизведение музыки.
	bool Music = true;
	//Воспроизведение звуковых эффектов.
	bool Sounds = true;
	//Локализация.
	Ustring Local = "RU";
	//Название используемого текстурпака.
	Ustring Texturepack = "Standart";
	//Название шрифта.
	Ustring Font = "Arialuni.ttf";
	//Название пиксельного шрифта.
	Ustring PixelFont = "Unifont 14.0.04.ttf";

	//---> Методы работы.
	//=======================================================================================================================//
	//Конструктор: загрузка из файла настроек.
	Settings(std::wstring Path);
	//Загрузка из файла настроек.
	void LoadFromFile(std::wstring Path);
	//Выводит в консоль все настройки.
	void Print();
};