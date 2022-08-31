#include "TextBox.h"

// --->TextBox
//=======================================================================================================================//

//Применение стилей и настроек к надписи.
void TextBox::AppendStyle() {
	Label.setFont(*TextFont);
	Label.setCharacterSize(CharacterSize);
	Label.setFillColor(TextColor);
	Label.setStyle(TextStyle);
	Label.setLineSpacing(LineSpacing);
	Label.setOutlineColor(OutlineColor);
	Label.setOutlineThickness(Thickness);
	Label.setPosition(Position);

}

//Разбитие строки на подстроки методом подстановки символов разрыва строки Windows.
std::wstring TextBox::LineBreak(sf::Text TextBufer, sf::Font* TextFont, std::wstring Str, unsigned int BlockSizeX) {
	//Коррекция потери указателя на шрифт при копировании.
	TextBufer.setFont(*TextFont);
	//Результат выполнения.
	std::wstring Result = L"";

	//Проверка необходимости переноса.
	TextBufer.setString(sf::String::fromUtf8(Str.begin(), Str.end()));
	if (TextBufer.getLocalBounds().width >= BlockSizeX) {
		//Строка разбивается по пробелам.
		std::vector<std::wstring> StringsBufer = DUBLIB::Split(Str, L' ');
		//Первый буфер: хранит значение из предыдущего цикла, после которого в случае превышения ширины блока переносится текст.
		std::wstring StrBuferOne = L"";
		//Второй буфер: к нему добавляются слова, а также на его основе строится размерная модель.
		std::wstring StrBuferTwo = L"";

		//Добавление пробела в конец всех строк.
		for (unsigned int i = 0; i < StringsBufer.size(); i++) StringsBufer[i] += L" ";

		//Проверка выхода за пределы области.
		for (unsigned int i = 0; i < StringsBufer.size(); i++) {
			//Добавление слова во второй буфер, участвующий в проверке на превышение ширины блока.
			StrBuferTwo += StringsBufer[i];
			TextBufer.setString(sf::String::fromUtf8(StrBuferTwo.begin(), StrBuferTwo.end()));
			///Если длина строки больше ширины блока.
			if (TextBufer.getLocalBounds().width > BlockSizeX) {
				//Сохранение результата и добавление символа разрыва строки Windows.
				Result += StrBuferOne;
				Result = DUBLIB::Trim(Result);
				Result += L"\n";
				//Очистка буферов.
				StrBuferOne.clear();
				StrBuferTwo = StringsBufer[i];
			}
			else StrBuferOne = StrBuferTwo;
		}
		//Если во втором буфере что-то осталось, то добавить в строку.
		Result += StrBuferTwo;
	}
	else Result = Str;
	return Result;
}

//Конструктор: пустой.
TextBox::TextBox() {

}

//Задаёт окно отрисовки и размеры блока отображения. Вызывать после установки всех стилей.
void TextBox::Initialize(sf::RenderWindow* MainWindow, sf::Vector2u BlockSize) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->BlockSize = BlockSize;

	//---> Генерация надписей.
	//=======================================================================================================================//
	AppendStyle();
	std::wstring ResultString = L"";
	for (unsigned int i = 0; i < StringsArray.size(); i++) ResultString += LineBreak(Label, TextFont, StringsArray[i], BlockSize.x) + L"\n\n";
	Label.setString(sf::String::fromUtf8(ResultString.begin(), ResultString.end()));
}

//Устанавливает позицию в окне.
void TextBox::SetPosition(sf::Vector2f Position) {
	this->Position = Position;
}

//Устанавливает позицию в окне.
void TextBox::SetPosition(float PositionX, float PositionY) {
	this->Position = sf::Vector2f(PositionX, PositionY);
}

//Передача указателя на шрифт.
void TextBox::SetFont(sf::Font* TextFont) {
	this->TextFont = TextFont;
}

//Задаёт межстрочный промежуток в долях от установленного шрифтом. По умолчанию 1.
void TextBox::SetLineSpacing(float LineSpacing) {
	this->LineSpacing = LineSpacing;
}

//Установка цвета надписи. По умолчанию белый.
void TextBox::SetColor(sf::Color TextColor) {
	this->TextColor = TextColor;
}

//Установка дополнительного стиля для текста.
void TextBox::SetStyle(sf::Text::Style TextStyle) {
	this->TextStyle = TextStyle;
}

//Установка текста и толщины обводки.
void TextBox::SetOutline(sf::Color OutlineColor, float Thickness) {
	this->OutlineColor = OutlineColor;
	this->Thickness = Thickness;
}

//Установка размера символов. По умолчанию равно 12.
void TextBox::SetCharacterSize(unsigned int Size) {
	this->CharacterSize = Size;
}

//Установка текста.
void TextBox::SetStringsArray(std::vector<std::wstring> StringsArray) {
	this->StringsArray = StringsArray;
}

//Отрисовка текстового поля.
void TextBox::Update() {
	MainWindow->draw(Label);
}