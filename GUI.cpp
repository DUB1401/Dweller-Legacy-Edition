#include "GUI.h"

// --->KeystrokesProcessing
//=======================================================================================================================//

//Конструктор: пустой.
KeystrokesProcessing::KeystrokesProcessing() {

}

//Конструктор: задаёт обрабатываемую клавишу.
KeystrokesProcessing::KeystrokesProcessing(sf::Keyboard::Key TargetKey) {
	this->TargetKey = TargetKey;
}

//Задаёт клавишу для обработки.
void KeystrokesProcessing::SetKey(sf::Keyboard::Key TargetKey) {
	this->TargetKey = TargetKey;
}

//Проверка состояния клавиши.
bool KeystrokesProcessing::Update() {
	//Результат проверки.
	bool Result = false;

	//Проверка нажатия клавиши.
	if (sf::Keyboard::isKeyPressed(TargetKey) && !IsKeyWasPressed) {
		IsKeyWasPressed = true;
		Result = true;
	}

	//Снятие залипания, если клавишу отпустили.
	if (!sf::Keyboard::isKeyPressed(TargetKey)) IsKeyWasPressed = false;

	return Result;
}

// --->Button
//=======================================================================================================================//

//Проверка попадания курсора в область кнопки.
bool Button::CheckMouseHover() {
	//Сохранение координат мыши.
	sf::Vector2i MouseCoords = sf::Mouse::getPosition(*MainWindow);
	//Попадание по осям X и Y.
	bool AxisX = false, AxisY = false;
	//Проверка попадания по оси X.
	if (MouseCoords.x > Position.x && MouseCoords.x < Position.x + Size.x * Scale.x) AxisX = true;
	//Проверка попадания по оси Y.
	if (MouseCoords.y > Position.y && MouseCoords.y < Position.y + Size.y * Scale.y) AxisY = true;
	//Проверка полного попадания.
	if (AxisX && AxisY) return true; else return false;
}

//Удаляет неиспользуемые индексы для доступа к спрайтам из перечисления стилей.
unsigned int Button::Normalize(unsigned int Index) {
	if (Index > 2) return 2; else return Index;
}

//Конструктор: пустой.
Button::Button() {

}

//Задаёт окно отрисовки.
void Button::Initialize(sf::RenderWindow* MainWindow) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
}

//Задаёт окно отрисовки.
void Button::Initialize(sf::RenderWindow* MainWindow, sf::Vector2u Size) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->Size = Size;
}

//Устанавливает позицию в окне.
void Button::SetPosition(sf::Vector2f Position) {
	this->Position = Position;
}

//Устанавливает позицию в окне.
void Button::SetPosition(float PositionX, float PositionY) {
	this->Position = sf::Vector2f(PositionX, PositionY);
}

//Задаёт базовый размер спрайта.
void Button::SetSize(sf::Vector2u Size) {
	this->Size = Size;
}

//Задаёт базовый размер спрайта.
void Button::SetSize(unsigned int SizeX, unsigned int SizeY) {
	this->Size = sf::Vector2u(SizeX, SizeY);
}

//Задаёт масштаб спрайта.
void Button::SetScale(float Scale) {
	this->Scale = sf::Vector2f(Scale, Scale);
}

//Загружает текстуру кнопки и задаёт количество спрайтов для неё. Вызывать после установки всех параметров.
bool Button::LoadTexture(std::string Path, unsigned int SpriteLinesCount) {
	if (ButtonTexture.loadFromFile(Path)) {
		//Буфер подгрузки спрайтов.
		sf::Sprite ButtonSpriteBufer;

		//Настройка спрайтов.
		for (unsigned int i = 0; i < SpriteLinesCount; i++) {
			ButtonSprites.push_back(ButtonSpriteBufer);
			ButtonSprites[i].setPosition(Position);
			ButtonSprites[i].setTexture(ButtonTexture);
			ButtonSprites[i].setTextureRect(sf::IntRect(0, Size.y * i, Size.x, Size.y));
			ButtonSprites[i].setScale(Scale);
		}
		return true;
	}
	else return false;
}

//Отрисовка центрированной надписи. Возвращает статус кнопки.
unsigned int Button::Update() {

	//Если курсор попадает на кнопку.
	if (CheckMouseHover()) { 
		//Если ЛКМ не нажата.
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !ButtonWasPressed) ButtonStatus = Hover;

		//Если ЛКМ нажата сейчас, а в прошлом цикле – нет.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !ButtonWasPressed) {
			ButtonWasPressed = true;
			ButtonStatus = Active;
		}

		//Если ЛКМ была нажата в прошлом цикле, а сейчас – нет.
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && ButtonWasPressed) {
			ButtonWasPressed = false;
			ButtonStatus = Clicked;
		}
	}
	else { 
		ButtonStatus = Normal;
		//Фикс срабатывания кнопки в случае, когда зажатая ЛКМ уходит с области фокуса.
		ButtonWasPressed = false;
	}

	MainWindow->draw(ButtonSprites[Normalize(ButtonStatus)]);

	return ButtonStatus;
}

// --->CenteredLabel
//=======================================================================================================================//

//Позиционирование строки по середине блока.
void CenteredLabel::Centering() {
	//Выравнивание по ширине блока.
	for (unsigned int i = 0; i < Label.size(); i++) {
		Label[i].setOrigin(Label[i].getLocalBounds().width / 2, Label[i].getOrigin().y);
		Label[i].setPosition((float)BlockSize.x / 2.0, Label[i].getPosition().y);
	}
	//Расчёт модификатора для выравнивания по высоте блока.
	float HeightModificator = 0;
	for (unsigned int i = 0; i < Label.size(); i++) HeightModificator += Label[i].getLocalBounds().height;
	HeightModificator = BlockSize.y - HeightModificator;
	HeightModificator /= 2;
	HeightModificator -= LineSpacing * CharacterSize * Label.size();
	HeightModificator += LineSpacing * CharacterSize;

	//Простановка координат по оси Y.
	for (unsigned int i = 0; i < Label.size(); i++) {
		//Модификатор межстрочного интервала.
		float LSC = CharacterSize * LineSpacing;

		if (i == 0) Label[i].setPosition(Label[i].getPosition().x + Position.x, HeightModificator - Label[i].getLocalBounds().top + Position.y);
		else Label[i].setPosition(Label[i].getPosition().x + Position.x, Label[i - 1].getPosition().y + Label[i - 1].getLocalBounds().height + LSC + Position.y);
	}

}

//Применение стиля ко всем спрайтам надписи.
void CenteredLabel::AppendStyle() {
	for (unsigned int i = 0; i < Label.size(); i++) {
		Label[i].setFont(*TextFont);
		Label[i].setCharacterSize(CharacterSize);
		Label[i].setFillColor(TextColor);
		Label[i].setStyle(TextStyle);
	}
}

//Конструктор: пустой.
CenteredLabel::CenteredLabel() {

}

//Задаёт окно отрисовки, центрируемую строку и размеры блока отображения. Вызывать после установки всех стилей.
void CenteredLabel::Initialize(sf::RenderWindow* MainWindow, std::wstring Str, sf::Vector2u BlockSize) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->Str = Str;
	this->BlockSize = BlockSize;

	SetString(Str);
}

//Передача указателя на шрифт.
void CenteredLabel::SetFont(sf::Font* TextFont) {
	this->TextFont = TextFont;
}

//Задаёт долю ширины блока, в которую нужно вписать текст (отступ от левого и правого края). По умолчанию 1.
void CenteredLabel::SetUsedSpace(float UsedSpace) {
	this->UsedSpace = UsedSpace;
}

//Устанавливает координаты блока.
void CenteredLabel::SetPosition(sf::Vector2f Postion) {
	this->Position = Position;
}

//Устанавливает координаты блока.
void CenteredLabel::SetPosition(float PostionX, float PostionY) {
	this->Position = sf::Vector2f(PostionX, PostionY);
}

//Установка цвета надписи. По умолчанию белый.
void CenteredLabel::SetColor(sf::Color TextColor) {
	this->TextColor = TextColor;
}

//Установка дополнительного стиля для текста.
void CenteredLabel::SetStyle(sf::Text::Style TextStyle) {
	this->TextStyle = TextStyle;
}

//Устанавливает межстрочный интервал в долях размера символа. По умолчанию 0.05 для компенсации артефактов шрифта.
void CenteredLabel::SetLineSpacing(float LineSpacing) {
	this->LineSpacing = LineSpacing;
}

//Установка размера символов. По умолчанию равно 12.
void CenteredLabel::SetCharacterSize(unsigned int Size) {
	this->CharacterSize = Size;
}

//Установка новой строки и перерасчёт выравнивания.
void CenteredLabel::SetString(std::wstring Str) {

	//Очистка контейнера для перезаписи.
	Label.clear();
	//Буферный текст SFML для расчёта величины надписи.
	sf::Text TextBufer;
	TextBufer.setCharacterSize(CharacterSize);
	TextBufer.setFillColor(TextColor);
	TextBufer.setStyle(TextStyle);
	TextBufer.setFont(*TextFont);
	//Вектор слов после разбития строки по символам пробела.
	std::vector<std::wstring> StrBufer = DUBLIB::Split(Str, L' ');
	//После каждого слова добавить пробел для удобства.
	for (unsigned int i = 0; i < StrBufer.size(); i++) StrBufer[i] += L" ";
	//Буфер для прошлой строчки.
	std::wstring BuferStrOne = StrBufer[0];
	//Буфер для текущей строчки.
	std::wstring BuferStrTwo = L"";
	//Буфер текста для помещения в вектор строчек.
	sf::Text TextResultString;
	//Пока размер строчки не будет выходить за пределы блока, добавлять по слову в буфер.
	for (unsigned int i = 0; i < StrBufer.size(); i++) {
		//Ко второму буферу строки добавить слово и пробел.
		BuferStrTwo += StrBufer[i];
		//Задать текущий буфер строки для расчёта размеров надписи.
		TextBufer.setString(sf::String::fromUtf8(BuferStrTwo.begin(), BuferStrTwo.end()));
		//Если надпись шире блока, то прежний буфер добавить в вектор для отрисовки, иначе добавить обновить старый буфер.
		if (TextBufer.getLocalBounds().width > (float)BlockSize.x * UsedSpace) {
			//Убрать пробел на конце.
			BuferStrOne = DUBLIB::DeleteLastCharacters(BuferStrOne, 1);
			//Буферному спрайту строчки поставить текст без пробела на конце.
			TextResultString.setString(sf::String::fromUtf8(BuferStrOne.begin(), BuferStrOne.end()));
			Label.push_back(TextResultString);
			BuferStrOne = StrBufer[i];
			BuferStrTwo = L"";
			//Компенсация сдвига при добавлении в вектор окончательной строчки.
			i--;
		}
		else BuferStrOne = BuferStrTwo;
	}
	//Записать последнюю строчку.
	TextResultString.setString(sf::String::fromUtf8(BuferStrOne.begin(), BuferStrOne.end()));
	Label.push_back(TextResultString);

	AppendStyle();
	Centering();
}

//Отрисовка центрированной надписи.
void CenteredLabel::Update() {
	for (unsigned int i = 0; i < Label.size(); i++) MainWindow->draw(Label[i]);

}

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