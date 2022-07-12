#pragma once

#pragma warning(disable : 4244)

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

#define Cout std::cout
#define Wout std::wcout
#define Cin std::cin
#define Endl std::endl

//�������������� � ������ ����� ������.
namespace DUBLIB {

	//�������������� �������������� �������� � ���������.
	std::string ConvertNumberToString(int Value);

	//��������������� std::string � std::wstring.
	std::wstring ToWstring(std::string Str);

}

//������ �� ��������.
namespace DUBLIB {

	//������� ��������� ����� �������� � ������ ������ (ASCII).
	std::string DeleteFirstCharacters(std::string Str, unsigned int Amount);

	//������� ��������� ����� �������� � ������ ������ (Unicode).
	std::wstring DeleteFirstCharacters(std::wstring Str, unsigned int Amount);

	//������� ��������� ����� �������� � ����� ������ (ASCII).
	std::string DeleteLastCharacters(std::string Str, unsigned int Amount);

	//������� ��������� ����� �������� � ����� ������ (Unicode).
	std::wstring DeleteLastCharacters(std::wstring Str, unsigned int Amount);

	//������� ������� � ������� ��������� �� ������ � ����� ������ (ASCII).
	std::string Trim(std::string Str);

	//������� ������� � ������� ��������� �� ������ � ����� ������ (Unicode).
	std::wstring Trim(std::wstring Str);

	//�������� ������ �� ��������� ����� (ASCII). 
	std::string CutToLength(std::string Str, unsigned int Length);

	//�������� ������ �� ��������� ����� (Unicode). 
	std::wstring CutToLength(std::wstring Str, unsigned int Length);

	//��������� ����������� ������������ ������ ������ ������ ������. ���� ������ ������ ������� ������, �� ������� � �� ���������� ����� (ASCII).
	bool CheckForSimilarity(std::string FirstStr, std::string SecondStr);

	//��������� ����������� ������������ ������ ������ ������ ������. ���� ������ ������ ������� ������, �� ������� � �� ���������� ����� (Unicode).
	bool CheckForSimilarity(std::wstring FirstStr, std::wstring SecondStr);

	//��������� ������ �� ��������� ������� �� ��������� (ASCII).
	std::vector<std::string> Split(std::string Str, char Marker);

	//��������� ������ �� ��������� ������� �� ��������� (Unicode).
	std::vector<std::wstring> Split(std::wstring Str, wchar_t Marker);

}

//�������������� �������.
namespace DUBLIB {

	//���������� ������������ ������������ ��������������� ����������� ��� ����������������� ���������� �� ��� Y.
	sf::Vector2f CalculateScaleY(sf::Vector2u FormSize, sf::Vector2u PictureSize, double DesiredRelatioToForm);

}

//������ ������ � ���������� ������� Evolv.
namespace DUBLIB {

	//���������� �������� ������� ���������� ������� � ����� (ASCII).
	std::string GetMarkeredStringFromFile(std::string File, std::string Marker);

	//���������� �������� ������� ���������� ������� � ����� (Unicode).
	std::wstring GetMarkeredStringFromFile(std::wstring File, std::wstring Marker);

	//���������� �������� ������� ���������� ������� � ����� � ����������� ��� � bool (ASCII).
	bool GetMarkeredBoolFromFile(std::string File, std::string Marker);

	//���������� �������� ������� ���������� ������� � ����� � ����������� ��� � bool (Unicode).
	bool GetMarkeredBoolFromFile(std::wstring File, std::wstring Marker);

	//���������� ������ ����� � ��������������� �������� (ASCII).
	std::vector<std::string> GetMarkeredStringsArrayFromFile(std::string File, std::string Marker);

	//���������� ������ ����� � ��������������� �������� (Unicode).
	std::vector<std::wstring> GetMarkeredStringsArrayFromFile(std::wstring File, std::wstring Marker);

}

//Debug-�������.
namespace DUBLIB {

	//������� � ������� ���������� ������� (std::string).
	void PrintVector(std::vector<std::string> Value);

	//������� � ������� ���������� ������� (std::wstring).
	void PrintVector(std::vector<std::wstring> Value);

	//������� � ������� ���������� ������� (unsigned int).
	void PrintVector(std::vector<unsigned int> Value);

}