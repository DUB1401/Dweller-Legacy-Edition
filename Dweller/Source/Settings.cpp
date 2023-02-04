#include "Settings.h"

//---> Settings
//=======================================================================================================================//

//Выводит в консоль bool красного или зелёного цвета соответственно логике и переводит вывод на новую строку.
void Settings::PrintBool(bool Value) {
	if (Value) {
		DUBLIB::SetWindowsConsoleColor(DUBLIB::CMD_Colors::clLightGreen);
		Wout << "true" << Endl;
		DUBLIB::SetWindowsConsoleColor(DUBLIB::CMD_Colors::clLightGray);
	}
	else {
		DUBLIB::SetWindowsConsoleColor(DUBLIB::CMD_Colors::clLightRed);
		Wout << "false" << Endl;
		DUBLIB::SetWindowsConsoleColor(DUBLIB::CMD_Colors::clLightGray);
	}
}

//Выводит в консоль int голубого цвета.
void Settings::PrintInt(int Value) {
	DUBLIB::SetWindowsConsoleColor(DUBLIB::CMD_Colors::clCyan);
	Wout << Value;
	DUBLIB::SetWindowsConsoleColor(DUBLIB::CMD_Colors::clLightGray);
}

//Переход на новую строку.
void Settings::Empl() {
	Wout << Endl;
}

//Конструктор: загрузка из файла настроек.
Settings::Settings(std::wstring Path) {
	LoadFromFile(Path);
}

//Загрузка из файла настроек.
void Settings::LoadFromFile(std::wstring Path) {
	//---> Версии и объявления.
	//=======================================================================================================================//
	Version = DUBLIB::GetMarkeredStringFromFile(Path, L"version");
	Sfml = DUBLIB::GetMarkeredStringFromFile(Path, L"sfml");

	//---> Настройки видеовывода.
	//=======================================================================================================================//
	WindowWidth = DUBLIB::GetMarkeredIntFromFile(Path, L"window-width");
	WindowHeight = DUBLIB::GetMarkeredIntFromFile(Path, L"window-height");
	VerticalSync = DUBLIB::GetMarkeredBoolFromFile(Path, L"window-verticalSync");
	FramerateLimit = DUBLIB::GetMarkeredIntFromFile(Path, L"window-framerateLimit");
	Fullscreen = DUBLIB::GetMarkeredBoolFromFile(Path, L"window-fullscreen");
	ShowFPS = DUBLIB::GetMarkeredBoolFromFile(Path, L"window-showFPS");

	//---> Настройки окружения игры.
	//=======================================================================================================================//
	Music = DUBLIB::GetMarkeredBoolFromFile(Path, L"game-music");
	Sounds = DUBLIB::GetMarkeredBoolFromFile(Path, L"game-sounds");
	Local = DUBLIB::GetMarkeredStringFromFile(Path, L"game-local");
	Texturepack = DUBLIB::GetMarkeredStringFromFile(Path, L"game-texturepack");
	Font = DUBLIB::GetMarkeredStringFromFile(Path, L"game-font");
	PixelFont = DUBLIB::GetMarkeredStringFromFile(Path, L"game-font-pixel");
}

//Выводит в консоль все настройки.
void Settings::Print() {
	Cout << "Game version: " << Version.AsString() << Endl;
	Wout << L"SFML: " << Sfml.AsWstring() << Endl;
	Wout << L"============================================================" << Endl;
	Wout << L"Winodow size: "; PrintInt(WindowWidth); Wout << L"x"; PrintInt(WindowHeight); Empl();
	Wout << L"Vertical Sync enabled: "; PrintBool(VerticalSync);

	Wout << L"Framerate limit: ";
	if (FramerateLimit) { PrintInt(FramerateLimit); Empl(); }
	else PrintBool(FramerateLimit);

	Wout << L"Fullscreen mode: "; PrintBool(Fullscreen);
	Wout << L"Show FPS: "; PrintBool(ShowFPS);
	Wout << L"============================================================" << Endl;
	Wout << L"Playing music: "; PrintBool(Music);
	Wout << L"Playing sounds: "; PrintBool(Sounds);
	Wout << L"Local: " << Local.AsWstring() << Endl;
	Wout << L"Texturepack name: " << Texturepack.AsWstring() << Endl;
	Wout << L"Font: " << Font.AsWstring() << Endl;
	Wout << L"Pixel font: " << PixelFont.AsWstring() << Endl;
}