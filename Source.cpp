#include "Source.h"
#include "EvolvGen.h"

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
		float LSC = CharacterSize * LineSpacing;
		if (i == 0) Label[i].setPosition(Label[i].getPosition().x, HeightModificator - Label[i].getLocalBounds().top);
		else Label[i].setPosition(Label[i].getPosition().x, Label[i - 1].getPosition().y + Label[i - 1].getLocalBounds().height + LSC);
	}

	/*
	//Простановка координат по оси Y.
	for (unsigned int i = 0; i < Label.size(); i++) {
		float LSC = CharacterSize * LineSpacing * i;
		if (i == 0) Label[i].setPosition(Label[i].getPosition().x, HeightModificator - Label[i].getLocalBounds().top);
		else Label[i].setPosition(Label[i].getPosition().x, LSC + HeightModificator - Label[i].getLocalBounds().top + CharacterSize * i);
	}
	*/

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

	//---> Генерация буферов и обработка разделения строчек.
	//=======================================================================================================================//
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

//Передача указателя на шрифт.
void CenteredLabel::SetFont(sf::Font* TextFont) {
	this->TextFont = TextFont;
}

//Задаёт долю ширины блока, в которую нужно вписать текст (отступ от левого и правого края). По умолчанию 1.
void CenteredLabel::SetUsedSpace(float UsedSpace) {
	this->UsedSpace = UsedSpace;
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

//Отрисовка центрированной надписи.
void CenteredLabel::Update() {
	for (unsigned int i = 0; i < Label.size(); i++) MainWindow->draw(Label[i]); 

}

// --->CenteredLabel
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

//---> Intro
//=======================================================================================================================//

//Установка анимации проявления.
void Intro::InitializeAppearancesAnimation() {
	TransparencyCoefficient = 255;
	StartAppearancesAnimation = true;
}

//Воспроизведение анимации проявления.
void Intro::PlayAppearancesAnimation() {
	TransparencyCoefficient -= 0.2 * *GlobalTimeAsMicroseconds / 800;
	if (TransparencyCoefficient < 0) {
		TransparencyCoefficient = 0;
		StartAppearancesAnimation = false;
	}
	BlackRect.setFillColor(sf::Color(0, 0, 0, TransparencyCoefficient));
	MainWindow->draw(BlackRect);
}

//Установка анимации затухания.
void Intro::InitializeAttenuationAnimation() {
	TransparencyCoefficient = 0;
	StartAttenuationAnimation = true;
}

//Воспроизведение анимации затухания.
void Intro::PlayAttenuationAnimation() {
	TransparencyCoefficient += 0.2 * *GlobalTimeAsMicroseconds / 800;
	if (TransparencyCoefficient > 255) {
		TransparencyCoefficient = 255;
		StartAttenuationAnimation = false;
	}
	BlackRect.setFillColor(sf::Color(0, 0, 0, TransparencyCoefficient));
	MainWindow->draw(BlackRect);
}

//Конструктор: запускает проигрывание вступительного ролика.
Intro::Intro(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds, unsigned long long int* GlobalTimeAsMicroseconds) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;
	this->GlobalTimeAsMicroseconds = GlobalTimeAsMicroseconds;

	//---> Загрузка историй из текстового файла и шрифта.
	//=======================================================================================================================//
	Book = DUBLIB::GetMarkeredStringsArrayFromFile(L"Data\\Local\\" + DUBLIB::GetMarkeredStringFromFile(L"Settings.txt", L"game-local") + L".txt", L"intro");
	TextFont.loadFromFile("Data\\Fonts\\" + DUBLIB::GetMarkeredStringFromFile("Settings.txt", "game-font"));

	//---> Загрузка иллюстраций и установка их положения по центру экрана. 
	//=======================================================================================================================//
	//Буферы.
	sf::Texture BufferTexture;
	sf::Sprite BufferSprite;
	std::string Path;
	//Обработка загрузки и позиционирования.
	for (unsigned int i = 0; i < 9; i++) {
		Path = "Data\\Texturepacks\\" + DUBLIB::GetMarkeredStringFromFile("Settings.txt", "game-texturepack") + "\\Story\\Story" + DUBLIB::ConvertNumberToString(i + 1) + ".png";

		StoryTextures.push_back(BufferTexture);
		StoryTextures[i].loadFromFile(Path.c_str());

		StorySprites.push_back(BufferSprite);
		StorySprites[i].setTexture(StoryTextures[i]);
		StorySprites[i].setScale(DUBLIB::CalculateScaleY(MainWindow->getSize(), StoryTextures[i].getSize(), 0.70));
		StorySprites[i].setOrigin(StorySprites[i].getLocalBounds().width / 2, StorySprites[i].getLocalBounds().height / 2);
		StorySprites[i].setPosition((float)MainWindow->getSize().x / 2, (float)MainWindow->getSize().y / 2);
	}
	//Формирование чёрного прямоугольника для анимации.
	BlackRect.setSize(sf::Vector2f(MainWindow->getSize().x, MainWindow->getSize().y));

	//---> Генерация лейблов.
	//=======================================================================================================================//
	//Заполнение вектора шаблонами.
	CenteredLabel* CL_Bufer = new CenteredLabel;
	for (unsigned int i = 0; i < 9; i++) {
		StoryText.push_back(*CL_Bufer);
		StoryText[i].SetCharacterSize(32);
		StoryText[i].SetFont(&TextFont);
		StoryText[i].SetStyle(sf::Text::Style::Italic);
		StoryText[i].SetUsedSpace(0.70);
		StoryText[i].SetLineSpacing(0.35);
		StoryText[i].Initialize(MainWindow, Book[i], MainWindow->getSize());
	}
	delete CL_Bufer;
}

//Запускает вступительный ролик. Возвращает false, если не удалось или возникли ошибки.
bool Intro::Start() {
	//Результат выполнения функции.
	bool IsSuccessfully = true;
	//Загрузка и воспроизведение трека.
	if (!IntroMusic.openFromFile("Data\\Sounds\\Intro.ogg")) IsSuccessfully = false;
	IntroMusic.play();

	IsEnabled = true;

	return IsSuccessfully;
}

//Останавливает вступительный ролик.
void Intro::End() {
	IntroMusic.stop();
	ElapsedTime = 0;
	IllustrationIndex = 0;
	BookIndex = 0;
	IsEnabled = false;
	TransparencyCoefficient = 255;
	StartAppearancesAnimation = true;
	StartAttenuationAnimation = false;
	IsAttenuationAnimationWasPlayed = false;
}

//Выполнение цикла обновления класса.
void Intro::Update() {
	//Пока включен ролик.
	if (IsEnabled) {
		//Если первый цикл, то проставить спрайтам указатели на текстуры.
		if (ElapsedTime == 0) StorySprites[IllustrationIndex].setTexture(StoryTextures[IllustrationIndex]);
		//Добавление времени кадра.
		ElapsedTime += *GlobalTimeAsSeconds;
		//Общий индекс кадров пролога.
		unsigned int FrameIndex = IllustrationIndex + BookIndex;

		//Если пролог не закончился и прошло нужное время в секундах, то сменить кадр.
		if (FrameIndex < 17 && ElapsedTime > EveryFrameTime[TimeIndex]) {
			ElapsedTime -= EveryFrameTime[TimeIndex];
			TimeIndex++;
			IsAttenuationAnimationWasPlayed = false; StartAttenuationAnimation = false;
			InitializeAppearancesAnimation();
			//Если чётное, перелистнуть иллюстрацию, иначе перелистнуть часть пролога.
			if (FrameIndex % 2 == 0) BookIndex++; else {
				//Перелистнуть кадр.
				IllustrationIndex++;
				//Нужно для обновления ссылки на текстуру.
				StorySprites[IllustrationIndex].setTexture(StoryTextures[IllustrationIndex]);
			}
		}

		//Если последний кадр был отрисован, то завершить вступительный ролик, иначе отрисовывать.
		if (FrameIndex % 2 == 0 && BookIndex < 9) StoryText[BookIndex].Update();
		if (FrameIndex % 2 != 0 && IllustrationIndex < 9) MainWindow->draw(StorySprites[IllustrationIndex]);

		//Если до конца кадра осталось меньше 0.5 секунды, то начать анимацию затухания.
		if (EveryFrameTime[TimeIndex] - ElapsedTime < 1.00 && !StartAttenuationAnimation && !IsAttenuationAnimationWasPlayed && FrameIndex < 17) {
			IsAttenuationAnimationWasPlayed = true;
			InitializeAttenuationAnimation();
		}

		//Проигрывание анимаций.
		if (StartAppearancesAnimation) PlayAppearancesAnimation();
		if (StartAttenuationAnimation) PlayAttenuationAnimation();
	}
}

//---> Credits
//=======================================================================================================================//

//Конструктор: задаёт окно отрисовки технических данных.
Credits::Credits(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;

	//---> Загрузка титров и настройка текстовой области.
	//=======================================================================================================================//
	TextFont.loadFromFile("Data\\Fonts\\" + DUBLIB::GetMarkeredStringFromFile("Settings.txt", "game-font"));
	TextBoxObject.SetCharacterSize(18);
	TextBoxObject.SetFont(&TextFont);
	TextBoxObject.SetPosition(28, 28 + 96);
	TextBoxObject.SetOutline(sf::Color::Black, 0.5);
	TextBoxObject.SetStringsArray(DUBLIB::GetMarkeredStringsArrayFromFile(L"Data\\Local\\" + DUBLIB::GetMarkeredStringFromFile(L"Settings.txt", L"game-local") + L".txt", L"credits"));
	TextBoxObject.Initialize(MainWindow, sf::Vector2u(MainWindow->getSize().x - 56, MainWindow->getSize().y));

	//---> Загрузка текстур.
	//=======================================================================================================================//
	BorderAmountX = MainWindow->getSize().x / 48;
	BorderAmountY = MainWindow->getSize().y / 28;
	std::string *TexturepackName = new std::string;
	*TexturepackName = DUBLIB::GetMarkeredStringFromFile("Settings.txt", "game-texturepack");
	BorderTexture.loadFromFile("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\border.png");
	BorderSprite.setTexture(BorderTexture);
	HeaderTexture.loadFromFile("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\header.png");
	HeaderSprite.setTexture(HeaderTexture);
	EmblemTexture.loadFromFile("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\emblem.png");
	EmblemSprite.setTexture(EmblemTexture);
	EmblemSprite.setOrigin(EmblemTexture.getSize().x / 2, EmblemTexture.getSize().y / 2);
	EmblemSprite.setPosition(MainWindow->getSize().x / 2, MainWindow->getSize().y / 2 + 48);
	EmblemSprite.setScale(MainWindow->getSize().y / EmblemTexture.getSize().y / 1.25, MainWindow->getSize().y / EmblemTexture.getSize().y / 1.25);
	
	delete TexturepackName;

	//---> Создание центрируемой надписи заголовка.
	//=======================================================================================================================//
	CenteredLabelObject.SetCharacterSize(48);
	CenteredLabelObject.SetFont(&TextFont);
	CenteredLabelObject.SetLineSpacing(0);
	CenteredLabelObject.SetStyle(sf::Text::Style::Bold);
	CenteredLabelObject.Initialize(MainWindow, DUBLIB::GetMarkeredStringFromFile(L"Data\\Local\\" + DUBLIB::GetMarkeredStringFromFile(L"Settings.txt", L"game-local") + L".txt", L"credits-header"), sf::Vector2u(HeaderSprite.getTextureRect().width, HeaderSprite.getTextureRect().height));
}

//Выполнение цикла обновления класса.
void Credits::Update() {
	//Заливка цветом.
	MainWindow->clear(sf::Color(158, 120, 119));

	MainWindow->draw(EmblemSprite);
	TextBoxObject.Update();
	//Отрисовка заголовка.
	MainWindow->draw(HeaderSprite);
	CenteredLabelObject.Update();

	//Отрисовка верхней рамки. Сдвиг на 12px для симметрии.
	BorderSprite.setTextureRect(sf::IntRect(0, 0, 48, 28));
	for (unsigned int i = 0; i < BorderAmountX; i++) {
		BorderSprite.setPosition(48 * i + 28 - 12, 96);
		MainWindow->draw(BorderSprite);
	}
	//Отрисовка левой рамки.
	BorderSprite.setTextureRect(sf::IntRect(0, 28, 28, 48));
	for (unsigned int i = 0; i < BorderAmountY; i++) {
		BorderSprite.setPosition(0, 48 * i + 28 + 96);
		MainWindow->draw(BorderSprite);
	}
	//Отрисовка правой рамки.
	BorderSprite.setTextureRect(sf::IntRect(28, 28, 28, 48));
	for (unsigned int i = 0; i < BorderAmountY; i++) {
		BorderSprite.setPosition(MainWindow->getSize().x - 28, 48 * i + 28 + 96);
		MainWindow->draw(BorderSprite);
	}
	//Отрисовка нижней рамки. Сдвиг на 12px для симметрии.
	BorderSprite.setTextureRect(sf::IntRect(48, 0, 48, 28));
	for (unsigned int i = 0; i < BorderAmountX; i++) {
		BorderSprite.setPosition(48 * i + 28 - 12, MainWindow->getSize().y - 28);
		MainWindow->draw(BorderSprite);
	}
	//Отрисовка уголков.
	BorderSprite.setTextureRect(sf::IntRect(56, 28, 28, 28));
	BorderSprite.setPosition(0, 96);
	MainWindow->draw(BorderSprite);
	BorderSprite.setPosition(MainWindow->getSize().x - 28, 96);
	MainWindow->draw(BorderSprite);
	BorderSprite.setPosition(MainWindow->getSize().x - 28, MainWindow->getSize().y - 28);
	MainWindow->draw(BorderSprite);
	BorderSprite.setPosition(0, MainWindow->getSize().y - 28);
	MainWindow->draw(BorderSprite);
}








































//Конструктор: загружает игру и включает её обработку.
Game::Game(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;
}

//Конструктор: задаёт окно отрисовки технических данных и счётчик времени.
World::World(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;
}

//Выполнение цикла обновления класса.
void World::Update() {

}