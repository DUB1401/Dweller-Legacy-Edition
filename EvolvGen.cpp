#include <SFML/Graphics.hpp>

#include "EvolvGen.h"

//�������������� � ������ ����� ������.
namespace DUBLIB {

	//�������������� �������������� �������� � ��������� (ASCII).
	std::string ConvertNumberToString(int Value) {
		std::stringstream Out;
		Out << Value;
		return Out.str();
	}

	//��������������� std::string � std::wstring.
	std::wstring ToWstring(std::string Str) {
		std::wstring to_wstring(Str.begin(), Str.end());
		return to_wstring;
	}

}

//������ �� ��������.
namespace DUBLIB {

	//������� ��������� ����� �������� � ������ ������ (ASCII).
	std::string DeleteFirstCharacters(std::string Str, unsigned int Amount) {
		Str.erase(0, Amount);
		return Str;
	}

	//������� ��������� ����� �������� � ������ ������ (Unicode).
	std::wstring DeleteFirstCharacters(std::wstring Str, unsigned int Amount) {
		Str.erase(0, Amount);
		return Str;
	}

	//������� ��������� ����� �������� � ����� ������ (ASCII).
	std::string DeleteLastCharacters(std::string Str, unsigned int Amount) {
		for (unsigned int i = 0; i < Amount; i++) if (Str.length() != 0) Str.pop_back();
		return Str;
	}

	//������� ��������� ����� �������� � ����� ������ (Unicode).
	std::wstring DeleteLastCharacters(std::wstring Str, unsigned int Amount) {
		for (unsigned int i = 0; i < Amount; i++) if (Str.length() != 0) Str.pop_back();
		return Str;
	}

	//������� ������� � ������� ��������� �� ������ � ����� ������ (ASCII).
	std::string Trim(std::string Str) {
		bool Stop = false;
		while (Str.length() > 0 && !Stop) {
			if (Str.front() == ' ' || Str.front() == '\t') Str = DeleteFirstCharacters(Str, 1); else Stop = true;
		}
		Stop = false;
		while (Str.length() > 0 && !Stop) {
			if (Str.back() == ' ' || Str.back() == '\t') Str = DeleteLastCharacters(Str, 1); else Stop = true;
		}
		return Str;
	}

	//������� ������� � ������� ��������� �� ������ � ����� ������ (Unicode).
	std::wstring Trim(std::wstring Str) {
		bool Stop = false;
		while (Str.length() > 0 && !Stop) {
			if (Str.front() == ' ' || Str.front() == '\t') Str = DeleteFirstCharacters(Str, 1); else Stop = true;
		}
		Stop = false;
		while (Str.length() > 0 && !Stop) {
			if (Str.back() == ' ' || Str.back() == '\t') Str = DeleteLastCharacters(Str, 1); else Stop = true;
		}
		return Str;
	}

	//�������� ������ �� ��������� ����� (ASCII). 
	std::string CutToLength(std::string Str, unsigned int Length) {
		std::string Bufer;
		for (unsigned int i = 0; i < Str.length(); i++) if (i != Length) Bufer.push_back(Str[i]); else return Bufer;
		return Str;
	}

	//�������� ������ �� ��������� ����� (Unicode). 
	std::wstring CutToLength(std::wstring Str, unsigned int Length) {
		std::wstring Bufer;
		for (unsigned int i = 0; i < Str.length(); i++) if (i != Length) Bufer.push_back(Str[i]); else return Bufer;
		return Str;
	}

	//��������� ����������� ������������ ������ ������ ������ ������. ���� ������ ������ ������� ������, �� ������� � �� ���������� ����� (ASCII).
	bool CheckForSimilarity(std::string FirstStr, std::string SecondStr) {
		if ((unsigned int)FirstStr.length() > (unsigned int)SecondStr.length()) CutToLength(FirstStr, (unsigned int)SecondStr.length());
		for (unsigned int i = 0; i < FirstStr.length(); i++) if (SecondStr[i] != FirstStr[i]) return false;
		return true;

	}

	//��������� ����������� ������������ ������ ������ ������ ������. ���� ������ ������ ������� ������, �� ������� � �� ���������� ����� (Unicode).
	bool CheckForSimilarity(std::wstring FirstStr, std::wstring SecondStr) {
		if ((unsigned int)FirstStr.length() > (unsigned int)SecondStr.length()) CutToLength(FirstStr, (unsigned int)SecondStr.length());
		for (unsigned int i = 0; i < (unsigned int)FirstStr.length(); i++) if (SecondStr[i] != FirstStr[i]) return false;
		return true;

	}

}

//�������������� �������.
namespace DUBLIB {

	//���������� ������������ ������������ ��������������� ����������� ��� ����������������� ���������� �� ��� Y.
	sf::Vector2f CalculateScaleY(sf::Vector2u FormSize, sf::Vector2u PictureSize, double DesiredRelatioToForm) {
		//��������� �������� ������� � ������������� �� ������ ���.
		double Relatio = (double)PictureSize.y / (double)FormSize.y;
		//�� ������� ��� ��������� ������ ���������.
		double ScaleY = DesiredRelatioToForm / Relatio;

		//��������, �� ������� �� ��� X �� ����� �����, ����� ��������� �� �� �������� ��� ������ ���.
		if (PictureSize.x * ScaleY > FormSize.x - 1) {
			double Relatio = (double)PictureSize.x / (double)FormSize.x;
			ScaleY = 1.0 / Relatio;
		}
		
		return sf::Vector2f((float)ScaleY, (float)ScaleY);
	}

}

//������ ������ � ���������� ������� Evolv.
namespace DUBLIB {

	//���������� �������� ������� ���������� ������� � ����� (ASCII).
	std::string GetMarkeredStringFromFile(std::string File, std::string Marker) {
		std::ifstream Read;
		Read.open(File);
		std::string Answer = "";

		std::string Bufer;
		while (getline(Read, Bufer)) {
			if (DUBLIB::CheckForSimilarity(Marker + ":", Bufer)) {
				Answer = DUBLIB::Trim(DUBLIB::DeleteFirstCharacters(Bufer, (unsigned int)Marker.length() + 1));
				Read.close();
			}
		}
		return Answer;
	}

	//���������� �������� ������� ���������� ������� � ����� (Unicode).
	std::wstring GetMarkeredStringFromFile(std::wstring File, std::wstring Marker) {
		std::wifstream Read;
		Read.open(File);
		std::wstring Answer = L"";
		std::wstring Bufer;
		while (getline(Read, Bufer)) {
			if (DUBLIB::CheckForSimilarity(Marker + L":", Bufer)) {
				Answer = DUBLIB::Trim(DUBLIB::DeleteFirstCharacters(Bufer, (unsigned int)Marker.length() + 1));
				Read.close();
			}
		}
		return Answer;
	}

	//���������� �������� ������� ���������� ������� � ����� � ����������� ��� � bool (ASCII).
	bool GetMarkeredBoolFromFile(std::string File, std::string Marker) {
		std::ifstream Read;
		Read.open(File);
		std::string Answer = "";
		std::string Bufer;

		while (getline(Read, Bufer)) {
			if (DUBLIB::CheckForSimilarity(Marker + ":", Bufer)) {
				Answer = DUBLIB::Trim(DUBLIB::DeleteFirstCharacters(Bufer, (unsigned int)Marker.length() + 1));
				Read.close();
			}
		}
		//������� ���� �������� � ������ �������.
		for (unsigned int i = 0; i < Answer.length(); i++) {
			Answer[i] = tolower(Answer[i]);
		}
		//������������ ������������� ��������.
		if (Answer == "true" || Answer == "1") return true; else return false;
	}

	//���������� �������� ������� ���������� ������� � ����� � ����������� ��� � bool (Unicode).
	bool GetMarkeredBoolFromFile(std::wstring File, std::wstring Marker) {
		std::wifstream Read;
		Read.open(File);
		std::wstring Answer = L"";
		std::wstring Bufer;

		while (getline(Read, Bufer)) {
			if (DUBLIB::CheckForSimilarity(Marker + L":", Bufer)) {
				Answer = DUBLIB::Trim(DUBLIB::DeleteFirstCharacters(Bufer, (unsigned int)Marker.length() + 1));
				Read.close();
			}
		}
		//������� ���� �������� � ������ �������.
		for (unsigned int i = 0; i < Answer.length(); i++) {
			Answer[i] = tolower(Answer[i]);
		}
		//������������ ������������� ��������.
		if (Answer == L"true" || Answer == L"1") return true; else return false;
	}

	//���������� ������ ����� � ��������������� �������� (ASCII).
	std::vector<std::string> GetMarkeredStringsArrayFromFile(std::string File, std::string Marker) {
		std::vector<std::string> Bufer;

		std::ifstream Read;
		Read.open(File); 
		std::string StrBufer = "";

		while (getline(Read, StrBufer)) if (DUBLIB::CheckForSimilarity(Marker + ":", StrBufer)) Bufer.push_back(DUBLIB::Trim(DUBLIB::DeleteFirstCharacters(StrBufer, (unsigned int)Marker.length() + 1)));
	
		Read.close();
		return Bufer;
	}

	//���������� ������ ����� � ��������������� �������� (Unicode).
	std::vector<std::wstring> GetMarkeredStringsArrayFromFile(std::wstring File, std::wstring Marker) {
		std::vector<std::wstring> Bufer;

		std::wifstream Read;
		Read.open(File);
		std::wstring StrBufer = L"";

		while (getline(Read, StrBufer)) if (DUBLIB::CheckForSimilarity(Marker + L":", StrBufer)) Bufer.push_back(DUBLIB::Trim(DUBLIB::DeleteFirstCharacters(StrBufer, (unsigned int)Marker.length() + 1)));

		Read.close();
		return Bufer;
	}

	//��������� ������ �� ��������� ������� �� ��������� (ASCII).
	std::vector<std::string> Split(std::string Str, char Marker) {
		std::string Bufer = "";
		std::vector<std::string> Lines;
		for (unsigned int i = 0; i < Str.length(); i++) if (Str[i] != Marker) Bufer += Str[i]; else {
			Lines.push_back(Bufer);
			Bufer = "";
		}
		if (Bufer != "") Lines.push_back(Bufer);
		return Lines;
	}

	//��������� ������ �� ��������� ������� �� ��������� (Unicode).
	std::vector<std::wstring> Split(std::wstring Str, wchar_t Marker) {
		std::wstring Bufer = L"";
		std::vector<std::wstring> Lines;
		for (unsigned int i = 0; i < Str.length(); i++) if (Str[i] != Marker) Bufer += Str[i]; else {
			Lines.push_back(Bufer);
			Bufer = L"";
		}
		if (Bufer != L"") Lines.push_back(Bufer);
		return Lines;
	}

}

//Debug-�������.
namespace DUBLIB {

	//������� � ������� ���������� ������� (std::string).
	void PrintVector(std::vector<std::string> Value) {
		for (unsigned int i = 0; i < Value.size(); i++) Cout << "Element " << i << " : \"" << Value[i] << "\"\n";
	}

	//������� � ������� ���������� ������� (std::wstring).
	void PrintVector(std::vector<std::wstring> Value) {
		for (unsigned int i = 0; i < Value.size(); i++) Wout << L"Element " << i << L" : \"" << Value[i] << L"\"\n";
	}

	//������� � ������� ���������� ������� (unsigned int).
	void PrintVector(std::vector<unsigned int> Value) {
		for (unsigned int i = 0; i < Value.size(); i++) Cout << "Element " << i << " : \"" << Value[i] << "\"\n";
	}

}

