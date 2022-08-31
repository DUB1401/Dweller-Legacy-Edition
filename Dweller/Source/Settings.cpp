#include "Settings.h"

//---> Settings
//=======================================================================================================================//

//������� � ������� bool �������� ��� ������� ����� �������������� ������ � ��������� ����� �� ����� ������.
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

//������� � ������� int �������� �����.
void Settings::PrintInt(int Value) {
	DUBLIB::SetWindowsConsoleColor(DUBLIB::CMD_Colors::clCyan);
	Wout << Value;
	DUBLIB::SetWindowsConsoleColor(DUBLIB::CMD_Colors::clLightGray);
}

//������� �� ����� ������.
void Settings::Empl() {
	Wout << Endl;
}

//�����������: �������� �� ����� ��������.
Settings::Settings(std::wstring Path) {
	LoadFromFile(Path);
}

//�������� �� ����� ��������.
void Settings::LoadFromFile(std::wstring Path) {
	//---> ������ � ����������.
	//=======================================================================================================================//
	Version = DUBLIB::GetMarkeredStringFromFile(Path, L"version");
	Sfml = DUBLIB::GetMarkeredStringFromFile(Path, L"sfml");

	//---> ��������� �����������.
	//=======================================================================================================================//
	WindowWidth = DUBLIB::GetMarkeredIntFromFile(Path, L"window-width");
	WindowHeight = DUBLIB::GetMarkeredIntFromFile(Path, L"window-height");
	VerticalSync = DUBLIB::GetMarkeredBoolFromFile(Path, L"window-verticalSync");
	FramerateLimit = DUBLIB::GetMarkeredIntFromFile(Path, L"window-framerateLimit");
	Fullscreen = DUBLIB::GetMarkeredBoolFromFile(Path, L"window-fullscreen");
	ShowFPS = DUBLIB::GetMarkeredBoolFromFile(Path, L"window-showFPS");

	//---> ��������� ��������� ����.
	//=======================================================================================================================//
	Music = DUBLIB::GetMarkeredBoolFromFile(Path, L"game-music");
	Sounds = DUBLIB::GetMarkeredBoolFromFile(Path, L"game-sounds");
	Local = DUBLIB::GetMarkeredStringFromFile(Path, L"game-local");
	Texturepack = DUBLIB::GetMarkeredStringFromFile(Path, L"game-texturepack");
	Font = DUBLIB::GetMarkeredStringFromFile(Path, L"game-font");
	PixelFont = DUBLIB::GetMarkeredStringFromFile(Path, L"game-font-pixel");
}

//������� � ������� ��� ���������.
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