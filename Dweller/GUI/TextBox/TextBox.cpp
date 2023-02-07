#include "TextBox.h"

//--->TextBox
//======================================================================================================================//

// Рассчитывает индекс нижней отображаемой строки.
void TextBox::CalculateLowerDisplayedStringIndex() {
	if (DisplayedStringsCount == 0) LowerDisplayedStringIndex = UpperDisplayedStringIndex + LabelStrings.size() - 1;
	else LowerDisplayedStringIndex = UpperDisplayedStringIndex + DisplayedStringsCount - 1;
}

// Рассчитывает координаты строк.
void TextBox::CalculateLabelStringsCoords() {
	// Координата высоты вышестоящей строки.
	float UpperStringCoordY;
	// Межстрочный интервал в пикселях.
	float LabelLineSpacing;

	// Обнуление координат строк.
	for (unsigned int i = 0; i < LabelStrings.size(); i++) LabelStrings[i].setPosition(0, 0);

	// Расчёт координат.
	for (unsigned int i = UpperDisplayedStringIndex; i <= LowerDisplayedStringIndex; i++) {
		// Расчёт межстрочного интервала в пикселях.
		LabelLineSpacing = abs(TextFont->getLineSpacing(CharacterSize) - (float)CharacterSize);
		// Расчёт координаты высоты вышестоящей строки.
		if (i == UpperDisplayedStringIndex) UpperStringCoordY = Position.y;
		else UpperStringCoordY = LabelStrings[i - 1].getGlobalBounds().height + LabelStrings[i - 1].getPosition().y + LabelLineSpacing + ParagraphSpacing * TextFont->getLineSpacing(CharacterSize) * IsFirstStringOfParagraph[i];
		// Установка координат строки.
		LabelStrings[i].setPosition(Position.x, UpperStringCoordY);
	}

}

// Применяет стили к строкам и проводит необходимые для инициализации расчёты.
void TextBox::AppendStyles() {
	// Применение стилей.
	for (unsigned int i = 0; i < LabelStrings.size(); i++) {
		LabelStrings[i].setFont(*TextFont);
		LabelStrings[i].setCharacterSize(CharacterSize);
		LabelStrings[i].setFillColor(TextColor);
		LabelStrings[i].setStyle(TextStyle);
		LabelStrings[i].setLineSpacing(LineSpacing);
		LabelStrings[i].setOutlineColor(OutlineColor);
		LabelStrings[i].setOutlineThickness(Thickness);
	}

	// Расчёт индекса нижней отображаемой строки и координат строк.
	CalculateLowerDisplayedStringIndex();
	CalculateLabelStringsCoords();
}

// Разбивает параграфы на строки при необходимости переноса.
std::vector<std::wstring> TextBox::ParagraphBreak(std::wstring Str, unsigned int BlockSizeX) {
	// Буфер для расчёта размеров текста.
	sf::Text TextBufer;
	// Установка стилей для буфера.
	TextBufer.setFont(*TextFont);
	TextBufer.setCharacterSize(CharacterSize);
	TextBufer.setFillColor(TextColor);
	TextBufer.setStyle(TextStyle);
	TextBufer.setLineSpacing(LineSpacing);
	TextBufer.setOutlineColor(OutlineColor);
	TextBufer.setOutlineThickness(Thickness);
	// Результат расщепления для переноса.
	std::wstring Result = L"";

	// Проверка необходимости переноса.
	TextBufer.setString(sf::String::fromUtf8(Str.begin(), Str.end()));
	if (TextBufer.getLocalBounds().width >= BlockSizeX) {
		// Строка разбивается по пробелам.
		std::vector<std::wstring> StringsBufer = DUBLIB::Split(Str, L' ');
		// Первый буфер: хранит значение из предыдущего цикла, после которого в случае превышения ширины блока переносится текст.
		std::wstring StrBuferOne = L"";
		// Второй буфер: к нему добавляются слова, а также на его основе строится размерная модель.
		std::wstring StrBuferTwo = L"";

		// Добавление пробела в конец всех строк.
		for (unsigned int i = 0; i < StringsBufer.size(); i++) StringsBufer[i] += L" ";

		// Проверка выхода за пределы области.
		for (unsigned int i = 0; i < StringsBufer.size(); i++) {
			// Добавление слова во второй буфер, участвующий в проверке на превышение ширины блока.
			StrBuferTwo += StringsBufer[i];
			TextBufer.setString(sf::String::fromUtf8(StrBuferTwo.begin(), StrBuferTwo.end()));
			// Если длина строки больше ширины блока.
			if (TextBufer.getLocalBounds().width > BlockSizeX) {
				// Сохранение результата и добавление символа разрыва строки Windows.
				Result += StrBuferOne;
				Result = DUBLIB::Trim(Result);
				Result += L"\n";
				// Очистка буферов.
				StrBuferOne.clear();
				StrBuferTwo = StringsBufer[i];
			}
			else StrBuferOne = StrBuferTwo;
		}
		// Если во втором буфере что-то осталось, то добавить в строку.
		Result += StrBuferTwo;
	}
	else Result = Str;

	return DUBLIB::Split(Result, L'\n');
}

// Конструктор: пустой.
TextBox::TextBox() {

}

// Инициализатор: задаёт окно отрисовки и размеры блока отображения. Вызывать после установки всех свойств.
void TextBox::initialize(sf::RenderWindow* MainWindow, sf::Vector2u BlockSize) {

	//---> Передача аргументов.
	//======================================================================================================================//
	this->MainWindow = MainWindow;
	this->BlockSize = BlockSize;

	//---> Генерация надписей.
	//======================================================================================================================//
	// Строки текста, разбитые для переноса.
	std::vector<std::wstring> SplittedStringsArray;
	// Для каждой строки проверить необходимость переноса и вставить символы новой строки при необходимости.
	for (unsigned int i = 0; i < StringsArray.size(); i++) { 
		// Буфер для вставки.
		std::vector<std::wstring> InsertBufer = ParagraphBreak(StringsArray[i], BlockSize.x);
		// Объединение уже имеющихся строк с разделёнными для переноса.
		SplittedStringsArray.insert(SplittedStringsArray.end(), InsertBufer.begin(), InsertBufer.end());

		// Если параграф разбивали для переноса, то определить последнюю строку, иначе представить весь параграф как строку.
		if (InsertBufer.size() > 1) { 
			for (unsigned int i = 0; i < InsertBufer.size(); i++) 
				if (i != 0) IsFirstStringOfParagraph.push_back(false);
				else IsFirstStringOfParagraph.push_back(true);
		}
		else IsFirstStringOfParagraph.push_back(true);
	}
	// Буфер для создания контейнеров.
	sf::Text ContainerBufer;
	// Создание контейнеров для отдельных строк.
	for (unsigned int i = 0; i < SplittedStringsArray.size(); i++) {
		LabelStrings.push_back(ContainerBufer);
		LabelStrings[i].setString(sf::String::fromUtf8(SplittedStringsArray[i].begin(), SplittedStringsArray[i].end()));
	}
	// Применение стилей к контейнерам и расчёт координат.
	AppendStyles();
}

// Устанавливает позицию в окне.
void TextBox::setPosition(sf::Vector2f Position) {
	this->Position = Position;
}

// Устанавливает позицию в окне.
void TextBox::setPosition(float PositionX, float PositionY) {
	this->Position = sf::Vector2f(PositionX, PositionY);
}

// Устанавливает указатель на шрифт.
void TextBox::setFont(sf::Font* TextFont) {
	this->TextFont = TextFont;
}

// Устанавливает межстрочный интервал в долях от заданного шрифтом.
void TextBox::setLineSpacing(float LineSpacing) {
	this->LineSpacing = LineSpacing;
}

// Устанавливает интервал между парграфами в долях от заданного шрифтом.
void TextBox::setParagraphSpacing(float ParagraphSpacing) {
	this->ParagraphSpacing = ParagraphSpacing;
}

// Устанавливает цвет текста.
void TextBox::setColor(sf::Color TextColor) {
	this->TextColor = TextColor;
}

// Устанавливает дополнительные стили.
void TextBox::setStyle(sf::Text::Style TextStyle) {
	this->TextStyle = TextStyle;
}

// Устанавливает цвет и толщину обводки.
void TextBox::setOutline(sf::Color OutlineColor, float Thickness) {
	this->OutlineColor = OutlineColor;
	this->Thickness = Thickness;
}

// Устанавливает размер символа в пикселях.
void TextBox::setCharacterSize(unsigned int Size) {
	this->CharacterSize = Size;
}

// Устанавливает список параграфов.
void TextBox::setParagraphsArray(std::vector<std::wstring> StringsArray) {
	this->StringsArray = StringsArray;
}

// Устанавливает количество одновременно отображаемых строк.
void TextBox::setDisplayedStringsCount(unsigned int DisplayedStringsCount) {
	this->DisplayedStringsCount = DisplayedStringsCount;
}

// Прокручивает текст по переданному дельта-значению.
void TextBox::scroll(int ScrollDelta) {

	// Сложение текущего индекса верхней строки со сначением прокрутки.
	UpperDisplayedStringIndex += -ScrollDelta;
	// Сложение текущего индекса нижней строки со сначением прокрутки.
	LowerDisplayedStringIndex += -ScrollDelta;

	// Проверка отрицательного индекса верхней строки.
	if (LowerDisplayedStringIndex < DisplayedStringsCount - 1) LowerDisplayedStringIndex = DisplayedStringsCount - 1;
	// Проверка выхода за количество строк индекса верхней строки.
	if (LowerDisplayedStringIndex > LabelStrings.size() - 1) LowerDisplayedStringIndex = LabelStrings.size() - 1;

	// Проверка отрицательного индекса верхней строки.
	if (UpperDisplayedStringIndex < 0) UpperDisplayedStringIndex = 0;
	// Проверка выхода за количество строк индекса верхней строки.
	if (UpperDisplayedStringIndex > LowerDisplayedStringIndex - DisplayedStringsCount + 1) UpperDisplayedStringIndex = LowerDisplayedStringIndex - DisplayedStringsCount + 1;

	// Рассчёт координат строк.
	CalculateLabelStringsCoords();
}

// Отрисовывает текст.
void TextBox::update() {

	for (unsigned int i = UpperDisplayedStringIndex; i <= LowerDisplayedStringIndex; i++) MainWindow->draw(LabelStrings[i]);

}