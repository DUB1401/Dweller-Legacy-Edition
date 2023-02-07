#include "CenteredLabel.h"

//--->CenteredLabel
//========================================================================================================================//

// Позиционирование строки по середине блока.
void CenteredLabel::Centering() {
	// Выравнивание по ширине блока.
	for (unsigned int i = 0; i < Label.size(); i++) {
		Label[i].setOrigin(Label[i].getLocalBounds().width / 2, Label[i].getOrigin().y);
		Label[i].setPosition((float)BlockSize.x / 2.0, Label[i].getPosition().y);
	}
	// Расчёт модификатора для выравнивания по высоте блока.
	float HeightModificator = 0;
	for (unsigned int i = 0; i < Label.size(); i++) HeightModificator += Label[i].getLocalBounds().height;
	HeightModificator = BlockSize.y - HeightModificator;
	HeightModificator /= 2;
	HeightModificator -= LineSpacing * CharacterSize * Label.size();
	HeightModificator += LineSpacing * CharacterSize;

	// Простановка координат по оси Y.
	for (unsigned int i = 0; i < Label.size(); i++) {
		// Модификатор межстрочного интервала.
		float LSC = CharacterSize * LineSpacing;

		if (i == 0) Label[i].setPosition(Label[i].getPosition().x + Position.x, HeightModificator - Label[i].getLocalBounds().top + Position.y);
		else Label[i].setPosition(Label[i].getPosition().x + Position.x, Label[i - 1].getPosition().y + Label[i - 1].getLocalBounds().height + LSC + Position.y);
	}

}

// Применение стиля ко всем спрайтам надписи.
void CenteredLabel::AppendStyle() {
	for (unsigned int i = 0; i < Label.size(); i++) {
		Label[i].setFont(*TextFont);
		Label[i].setCharacterSize(CharacterSize);
		Label[i].setFillColor(TextColor);
		Label[i].setStyle(TextStyle);
		Label[i].setOutlineColor(OutlineColor);
		Label[i].setOutlineThickness(OutlineThickness);
	}
}

// Конструктор: пустой.
CenteredLabel::CenteredLabel() {

}

// Задаёт окно отрисовки, центрируемую строку и размеры блока отображения. Вызывать после установки всех стилей.
void CenteredLabel::Initialize(sf::RenderWindow* MainWindow, std::wstring Str, sf::Vector2u BlockSize) {

	//---> Передача аргументов.
	//========================================================================================================================//
	this->MainWindow = MainWindow;
	this->Str = Str;
	this->BlockSize = BlockSize;

	SetString(Str);
}

// Передача указателя на шрифт.
void CenteredLabel::SetFont(sf::Font* TextFont) {
	this->TextFont = TextFont;
}

// Задаёт долю ширины блока, в которую нужно вписать текст (отступ от левого и правого края). По умолчанию 1.
void CenteredLabel::SetUsedSpace(float UsedSpace) {
	this->UsedSpace = UsedSpace;
}

// Устанавливает координаты блока.
void CenteredLabel::SetPosition(sf::Vector2f Postion) {
	this->Position = Position;
}

// Устанавливает координаты блока.
void CenteredLabel::SetPosition(float PostionX, float PostionY) {
	this->Position = sf::Vector2f(PostionX, PostionY);
}

// Установка цвета надписи. По умолчанию белый.
void CenteredLabel::SetColor(sf::Color TextColor) {
	this->TextColor = TextColor;
}

// Установка дополнительного стиля для текста.
void CenteredLabel::SetStyle(sf::Text::Style TextStyle) {
	this->TextStyle = TextStyle;
}

// Устанавливает межстрочный интервал в долях размера символа. По умолчанию 0.05 для компенсации артефактов шрифта.
void CenteredLabel::SetLineSpacing(float LineSpacing) {
	this->LineSpacing = LineSpacing;
}

// Установка размера символов. По умолчанию равно 12.
void CenteredLabel::SetCharacterSize(unsigned int Size) {
	this->CharacterSize = Size;
}

// Задаёт обводку.
void CenteredLabel::SetOutline(sf::Color OutlineColor, float OutlineThickness) {
	this->OutlineColor = OutlineColor;
	this->OutlineThickness = OutlineThickness;
}

// Установка новой строки и перерасчёт выравнивания.
void CenteredLabel::SetString(std::wstring Str) {
	// Проверка на пустоту строки.
	if (Str != L"") {
		// Очистка контейнера для перезаписи.
		Label.clear();
		// Буферный текст SFML для расчёта величины надписи.
		sf::Text TextBufer;
		TextBufer.setCharacterSize(CharacterSize);
		TextBufer.setFillColor(TextColor);
		TextBufer.setStyle(TextStyle);
		TextBufer.setFont(*TextFont);
		// Вектор слов после разбития строки по символам пробела.
		std::vector<std::wstring> StrBufer = DUBLIB::Split(Str, L' ');
		// После каждого слова добавить пробел для удобства.
		for (unsigned int i = 0; i < StrBufer.size(); i++) StrBufer[i] += L" ";
		// Буфер для прошлой строчки.
		std::wstring BuferStrOne = StrBufer[0];
		// Буфер для текущей строчки.
		std::wstring BuferStrTwo = L"";
		// Буфер текста для помещения в вектор строчек.
		sf::Text TextResultString;
		// Пока размер строчки не будет выходить за пределы блока, добавлять по слову в буфер.
		for (unsigned int i = 0; i < StrBufer.size(); i++) {
			// Ко второму буферу строки добавить слово и пробел.
			BuferStrTwo += StrBufer[i];
			// Задать текущий буфер строки для расчёта размеров надписи.
			TextBufer.setString(sf::String::fromUtf8(BuferStrTwo.begin(), BuferStrTwo.end()));
			// Если надпись шире блока, то прежний буфер добавить в вектор для отрисовки, иначе добавить обновить старый буфер.
			if (TextBufer.getLocalBounds().width > (float)BlockSize.x * UsedSpace) {
				// Убрать пробел на конце.
				BuferStrOne = DUBLIB::DeleteLastCharacters(BuferStrOne, 1);
				// Буферному спрайту строчки поставить текст без пробела на конце.
				TextResultString.setString(sf::String::fromUtf8(BuferStrOne.begin(), BuferStrOne.end()));
				Label.push_back(TextResultString);
				BuferStrOne = StrBufer[i];
				BuferStrTwo = L"";
				// Компенсация сдвига при добавлении в вектор окончательной строчки.
				i--;
			}
			else BuferStrOne = BuferStrTwo;
		}
		// Записать последнюю строчку.
		TextResultString.setString(sf::String::fromUtf8(BuferStrOne.begin(), BuferStrOne.end()));
		Label.push_back(TextResultString);

		AppendStyle();
		Centering();
	}
}

// Отрисовка центрированной надписи.
void CenteredLabel::Update() {
	for (unsigned int i = 0; i < Label.size(); i++) MainWindow->draw(Label[i]);

}