#pragma once

#include "../EvolvGen.h"

//��������� ��������.
class Settings {
private:

	//������������� ��������� ����� std::string � std::wstring.
	struct Ustring {
	protected:

		//������������� ������������� ������ ����� std::string.
		void SetString(std::string Str) {
			U_String = Str;
		}
		//������������� ������������� ������ ����� std::string.
		void SetWstring(std::wstring Str) {
			U_Wstring = Str;
		}
		//������������� ������ ����� std::string.
		std::string U_String;
		//������������� ������ ����� std::wstring.
		std::wstring U_Wstring;

	public:

		//�����������: ������.
		Ustring() {}
		//�����������: ����� ������.
		Ustring(const char* U_String) {
			SetString(U_String);
			SetWstring(DUBLIB::ToWstring(U_String));
		}
		//�����������: ����� ������.
		Ustring(const wchar_t* U_Wstring) {
			SetString(DUBLIB::ToString(U_Wstring, DUBLIB::Encodings::ANSI));
			SetWstring(U_Wstring);
		}
		//�����������: ����� ������.
		Ustring(std::wstring U_Wstring) {
			SetString(DUBLIB::ToString(U_Wstring, DUBLIB::Encodings::UTF8));
			SetWstring(U_Wstring);
		}
		//���������� ������������� ������ ����� std::string.
		std::string AsString() {
			return U_String;
		}
		//���������� ������������� ������ ����� std::wstring.
		std::wstring AsWstring() {
			return U_Wstring;
		}

	};

	//---> ������ ������.
	//=======================================================================================================================//
	//������� � ������� bool �������� ��� ������� ����� �������������� ������ � ��������� ����� �� ����� ������.
	void PrintBool(bool Value);
	//������� � ������� int �������� �����.
	void PrintInt(int Value);
	//������� �� ����� ������.
	void Empl();

public:

	//---> ������ � ����������.
	//=======================================================================================================================//
	//������ ����.
	Ustring Version = "1.0.0 pre-alpha";
	//������ ���������� SFML.
	Ustring Sfml = "2.5.1";

	//---> ��������� �����������.
	//=======================================================================================================================//
	//������ ����.
	unsigned int WindowWidth = 1280;
	//������ ����.
	unsigned int WindowHeight = 720;
	//������������ �� ������������ �������������.
	bool VerticalSync = false;
	//����� FPS.
	unsigned int FramerateLimit = 0;
	//������������� �����.
	bool Fullscreen = false;
	//����������� �� ������� FPS.
	bool ShowFPS = false;

	//---> ��������� ��������� ����.
	//=======================================================================================================================//
	//��������������� ������.
	bool Music = true;
	//��������������� �������� ��������.
	bool Sounds = true;
	//�����������.
	Ustring Local = "RU";
	//�������� ������������� �����������.
	Ustring Texturepack = "Standart";
	//�������� ������.
	Ustring Font = "Arialuni.ttf";
	//�������� ����������� ������.
	Ustring PixelFont = "Unifont 14.0.04.ttf";

	//---> ������ ������.
	//=======================================================================================================================//
	//�����������: �������� �� ����� ��������.
	Settings(std::wstring Path);
	//�������� �� ����� ��������.
	void LoadFromFile(std::wstring Path);
	//������� � ������� ��� ���������.
	void Print();
};