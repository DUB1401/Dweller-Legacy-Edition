#include "EvolvGen.h"

//Преобразование и анализ типов данных.
namespace DUBLIB {

	//Преобразование целочисленного значения в строковое.
	std::string ConvertNumberToString(int Value) {
		std::stringstream Out;
		Out << Value;
		return Out.str();
	}

	//Преобразовывает std::string в std::wstring.
	std::wstring ToWstring(std::string Str) {
		std::vector<wchar_t> buf(Str.size());
		std::use_facet<std::ctype<wchar_t>>(std::locale()).widen(Str.data(),
			Str.data() + Str.size(),
			buf.data());
		return std::wstring(buf.data(), buf.size());
	}

	//Преобразовывает std::wstring в std::string.
	std::string ToString(std::wstring Str, Encodings FromEncoding) {
		std::string Result;
		//Преобразование из UTF-8.
		if (FromEncoding == Encodings::UTF8) {
			std::vector<char> Bufer(Str.size());
			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Str.data(), Str.data() + Str.size(), '?', Bufer.data());
			Result = std::string(Bufer.data(), Bufer.size());
		}
		//Преобразование из ASCII.
		if (FromEncoding == Encodings::ANSI) {
			int sz = WideCharToMultiByte(CP_ACP, 0, &Str[0], (int)Str.size(), 0, 0, 0, 0);
			Result = std::string(sz, 0);
			WideCharToMultiByte(CP_ACP, 0, &Str[0], (int)Str.size(), &Result[0], sz, 0, 0);
		}
		return Result;
	}
}

//Работа со строками.
namespace DUBLIB {

	//Удаляет указанное число символов с начала строки (ASCII).
	std::string DeleteFirstCharacters(std::string Str, unsigned int Amount) {
		Str.erase(0, Amount);
		return Str;
	}

	//Удаляет указанное число символов с начала строки (UTF-16).
	std::wstring DeleteFirstCharacters(std::wstring Str, unsigned int Amount) {
		Str.erase(0, Amount);
		return Str;
	}

	//Удаляет указанное число символов с конца строки (ASCII).
	std::string DeleteLastCharacters(std::string Str, unsigned int Amount) {
		for (unsigned int i = 0; i < Amount; i++) if (Str.length() != 0) Str.pop_back();
		return Str;
	}

	//Удаляет указанное число символов с конца строки (UTF-16).
	std::wstring DeleteLastCharacters(std::wstring Str, unsigned int Amount) {
		for (unsigned int i = 0; i < Amount; i++) if (Str.length() != 0) Str.pop_back();
		return Str;
	}

	//Удаляет пробелы и символы табуляции из начала и конца строки (ASCII).
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

	//Удаляет пробелы и символы табуляции из начала и конца строки (UTF-16).
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

	//Обрезает строку до указанной длины (ASCII). 
	std::string CutToLength(std::string Str, unsigned int Length) {
		std::string Bufer;
		for (unsigned int i = 0; i < Str.length(); i++) if (i != Length) Bufer.push_back(Str[i]); else return Bufer;
		return Str;
	}

	//Обрезает строку до указанной длины (UTF-16). 
	std::wstring CutToLength(std::wstring Str, unsigned int Length) {
		std::wstring Bufer;
		for (unsigned int i = 0; i < Str.length(); i++) if (i != Length) Bufer.push_back(Str[i]); else return Bufer;
		return Str;
	}

	//Проверяет посимвольно соответствие первой строки второй строке. Если первая строка длиннее второй, то усекает её до одинаковой длины (ASCII).
	bool CheckForSimilarity(std::string FirstStr, std::string SecondStr) {
		if ((unsigned int)FirstStr.length() > (unsigned int)SecondStr.length()) CutToLength(FirstStr, (unsigned int)SecondStr.length());
		for (unsigned int i = 0; i < FirstStr.length(); i++) if (SecondStr[i] != FirstStr[i]) return false;
		return true;

	}

	//Проверяет посимвольно соответствие первой строки второй строке. Если первая строка длиннее второй, то усекает её до одинаковой длины (UTF-16).
	bool CheckForSimilarity(std::wstring FirstStr, std::wstring SecondStr) {
		if ((unsigned int)FirstStr.length() > (unsigned int)SecondStr.length()) CutToLength(FirstStr, (unsigned int)SecondStr.length());
		for (unsigned int i = 0; i < (unsigned int)FirstStr.length(); i++) if (SecondStr[i] != FirstStr[i]) return false;
		return true;

	}

}

//Математические функции.
namespace DUBLIB {

	//Возвращает максимальные коэффициенты масштабирования изображения для пропорционального увеличения по оси Y.
	sf::Vector2f CalculateScaleY(sf::Vector2u FormSize, sf::Vector2u PictureSize, double DesiredRelatioToForm) {
		//Отношение текущего размера к максимальному по нужной оси.
		double Relatio = (double)PictureSize.y / (double)FormSize.y;
		//Во сколько раз отношение меньше желаемого.
		double ScaleY = DesiredRelatioToForm / Relatio;

		//Проверка, не выходит ли ось X за грани формы, иначе повторить те же действия для второй оси.
		if (PictureSize.x * ScaleY > FormSize.x - 1) {
			double Relatio = (double)PictureSize.x / (double)FormSize.x;
			ScaleY = 1.0 / Relatio;
		}
		
		return sf::Vector2f((float)ScaleY, (float)ScaleY);
	}

}

//Методы работы с текстовыми файлами Evolv.
namespace DUBLIB {

	//Возвращает значение первого найденного маркера в файле (ASCII).
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

	//Возвращает значение первого найденного маркера в файле (Unicode).
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

	//Возвращает целочисленное значение первого найденного маркера в файле (ASCII).
	int GetMarkeredIntFromFile(std::string File, std::string Marker) {
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
		return atoi(Answer.c_str());
	}

	//Возвращает целочисленное значение первого найденного маркера в файле (UTF-16).
	int GetMarkeredIntFromFile(std::wstring File, std::wstring Marker) {
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
		return _wtoi(Answer.c_str());
	}

	//Возвращает значение первого найденного маркера в файле и форматирует его в bool (ASCII).
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
		//Перевод всех символов в нижний регистр.
		for (unsigned int i = 0; i < Answer.length(); i++) {
			Answer[i] = tolower(Answer[i]);
		}
		//Формирование возвращаемого значения.
		if (Answer == "true" || Answer == "1") return true; else return false;
	}

	//Возвращает значение первого найденного маркера в файле и форматирует его в bool (Unicode).
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
		//Перевод всех символов в нижний регистр.
		for (unsigned int i = 0; i < Answer.length(); i++) {
			Answer[i] = tolower(Answer[i]);
		}
		//Формирование возвращаемого значения.
		if (Answer == L"true" || Answer == L"1") return true; else return false;
	}

	//Возвращает вектор строк с соответствующим маркером (ASCII).
	std::vector<std::string> GetMarkeredStringsArrayFromFile(std::string File, std::string Marker) {
		std::vector<std::string> Bufer;

		std::ifstream Read;
		Read.open(File); 
		std::string StrBufer = "";

		while (getline(Read, StrBufer)) if (DUBLIB::CheckForSimilarity(Marker + ":", StrBufer)) Bufer.push_back(DUBLIB::Trim(DUBLIB::DeleteFirstCharacters(StrBufer, (unsigned int)Marker.length() + 1)));
	
		Read.close();
		return Bufer;
	}

	//Возвращает вектор строк с соответствующим маркером (Unicode).
	std::vector<std::wstring> GetMarkeredStringsArrayFromFile(std::wstring File, std::wstring Marker) {
		std::vector<std::wstring> Bufer;

		std::wifstream Read;
		Read.open(File);
		std::wstring StrBufer = L"";

		while (getline(Read, StrBufer)) if (DUBLIB::CheckForSimilarity(Marker + L":", StrBufer)) Bufer.push_back(DUBLIB::Trim(DUBLIB::DeleteFirstCharacters(StrBufer, (unsigned int)Marker.length() + 1)));

		Read.close();
		return Bufer;
	}

	//Разбивает строку по вхождению символа на подстроки (ASCII).
	std::vector<std::string> Split(std::string Str, char Marker) {
		std::string Bufer = "";
		std::vector<std::string> Lines;
		for (unsigned int i = 0; i < Str.length(); i++) if (Str[i] != Marker) Bufer += Str[i]; else {
			Lines.push_back(Bufer);
			Bufer = "";
		}
		Lines.push_back(Bufer);
		return Lines;
	}

	//Разбивает строку по вхождению символа на подстроки (Unicode).
	std::vector<std::wstring> Split(std::wstring Str, wchar_t Marker) {
		std::wstring Bufer = L"";
		std::vector<std::wstring> Lines;
		for (unsigned int i = 0; i < Str.length(); i++) if (Str[i] != Marker) Bufer += Str[i]; else {
			Lines.push_back(Bufer);
			Bufer = L"";
		}
		Lines.push_back(Bufer);

		return Lines;
	}

}

//Debug-функции.
namespace DUBLIB {

	//Выводит в консоль содержимое вектора (std::string).
	void PrintVector(std::vector<std::string> Value) {
		for (unsigned int i = 0; i < Value.size(); i++) Cout << "Element " << i << " : \"" << Value[i] << "\"\n";
	}

	//Выводит в консоль содержимое вектора (std::wstring).
	void PrintVector(std::vector<std::wstring> Value) {
		for (unsigned int i = 0; i < Value.size(); i++) Wout << L"Element " << i << L" : \"" << Value[i] << L"\"\n";
	}

	//Выводит в консоль содержимое вектора (unsigned int).
	void PrintVector(std::vector<unsigned int> Value) {
		for (unsigned int i = 0; i < Value.size(); i++) Cout << "Element " << i << " : \"" << Value[i] << "\"\n";
	}

}

//Методы работы с Windows.
namespace DUBLIB {

	//Задаёт цвет текста консоли.
	void SetWindowsConsoleColor(CMD_Colors TextColor) {
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | static_cast<unsigned>(TextColor)));
	}

}

