#include "Source.h"

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
	//Выбранный язык.
	std::wstring *Local = new std::wstring;
	*Local = DUBLIB::GetMarkeredStringFromFile(L"Settings.txt", L"game-local");
	Book = DUBLIB::GetMarkeredStringsArrayFromFile(L"Data\\Local\\" + *Local + L".txt", L"intro");
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

	PressAnyKey.SetCharacterSize(18);
	PressAnyKey.SetFont(&TextFont);
	PressAnyKey.SetStyle(sf::Text::Style::Italic);
	PressAnyKey.SetPosition(0, MainWindow->getSize().y * 0.95);
	PressAnyKey.Initialize(MainWindow, DUBLIB::GetMarkeredStringFromFile(L"Data\\Local\\" + *Local + L".txt", L"press-anykey"), sf::Vector2u(MainWindow->getSize().x, 20));
	delete Local;

	KP_Space.SetKey(sf::Keyboard::Space);
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
	SpaceWasPresed = 0;
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

		//Обработка прерывания ролика по требованию пользователя.
		if (KP_Space.Update()) SpaceWasPresed++;
		if (SpaceWasPresed == 1) PressAnyKey.Update();
		if (SpaceWasPresed == 2) End();

	}
}

//---> Credits
//=======================================================================================================================//

//Закрытие титров.
void Credits::Close() {
	Answer = "to_menu";
}

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
	HeaderSprite.setScale((float)MainWindow->getSize().x / (float)HeaderTexture.getSize().x, 1.0);
	EmblemTexture.loadFromFile("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\emblem.png");
	EmblemSprite.setTexture(EmblemTexture);
	EmblemSprite.setOrigin(EmblemTexture.getSize().x / 2, EmblemTexture.getSize().y / 2);
	EmblemSprite.setPosition(MainWindow->getSize().x / 2, MainWindow->getSize().y / 2 + 48);
	EmblemSprite.setScale(MainWindow->getSize().y / EmblemTexture.getSize().y / 1.25, MainWindow->getSize().y / EmblemTexture.getSize().y / 1.25);

	//---> Создание центрируемой надписи заголовка.
	//=======================================================================================================================//
	CenteredLabelObject.SetCharacterSize(48);
	CenteredLabelObject.SetFont(&TextFont);
	CenteredLabelObject.SetLineSpacing(0);
	CenteredLabelObject.SetStyle(sf::Text::Style::Bold);
	CenteredLabelObject.Initialize(MainWindow, DUBLIB::GetMarkeredStringFromFile(L"Data\\Local\\" + DUBLIB::GetMarkeredStringFromFile(L"Settings.txt", L"game-local") + L".txt", L"credits-header"), sf::Vector2u(MainWindow->getSize().x, HeaderSprite.getTextureRect().height));

	//---> Генерирование кнопки.
	//=======================================================================================================================//
	BT_Close.SetPosition(MainWindow->getSize().x - 80, 24);
	BT_Close.SetSize(48, 48);
	BT_Close.LoadTexture("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\button_close_grey.png", 3);
	BT_Close.Initialize(MainWindow);

	KP_Escape.SetKey(sf::Keyboard::Escape);

	delete TexturepackName;


}

//Выполнение цикла обновления класса.
std::string Credits::Update() {
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

	//Если титры были закрыты, но обновляются снова, то отменить передачу ответа.
	if (Answer != "") Answer.clear();

	//Отправка ответа для обработчика меню.
	if (BT_Close.Update() == Button::Clicked) Close();
	if (KP_Escape.Update()) Close();

	return Answer;
}

//---> MainMenu
//=======================================================================================================================//

//Закрытие главного меню.
void MainMenu::Close(std::string Message) {
	//Передача сообщения в обработчик меню.
	Answer = Message;
	//Отключение проигрывания музыки.
	BackgroundMusic.stop();
}

//Открытие главного меню.
void MainMenu::Open() {
	//Воспроизведение фоновой музыки.
	BackgroundMusic.play();
}

//Проигрывает звуковой эффект.
void MainMenu::PlaySoundEffect(unsigned int Index) {
	if (SoundEffect.getStatus() != sf::Music::Playing) {
		SoundEffect.openFromFile("Data\\Sounds\\" + SoundsNames[Index] + ".ogg");
		SoundEffect.play();
	}
}

//Проверяет и обрабатывает взаимодействие с кнопками.
void MainMenu::ButtonInteraction(unsigned int Index) {
	if (ButtonsStatus[Index] == Button::Hover) {
		if (LastSoundEffectIndex == 0) {
			PlaySoundEffect(Index);
			LastSoundEffectIndex = Index + 1;
			CL_Description.SetString(ButtonsLabels[Index]);
		}
		CL_Description.Update();
	}
}

//Конструктор: задаёт окно отрисовки технических данных.
MainMenu::MainMenu(sf::RenderWindow* MainWindow) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;

	//---> Подгрузка необходимых текстур.
	//=======================================================================================================================//
	//Название текстурпака.
	std::string* TexturepackName = new std::string;
	*TexturepackName = DUBLIB::GetMarkeredStringFromFile("Settings.txt", "game-texturepack");
	LogoTexture.loadFromFile("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\logo.png");
	LogoSprite.setTexture(LogoTexture);
	LogoSprite.setOrigin(LogoTexture.getSize().x / 2, LogoTexture.getSize().y / 2);
	//Масштабирование в 25% высоты окна.
	float *Scale = new float;
	*Scale = MainWindow->getSize().y / 4;
	*Scale = *Scale / LogoTexture.getSize().y;
	LogoSprite.setScale(*Scale, *Scale);

	LogoSprite.setPosition(MainWindow->getSize().x / 2, LogoSprite.getGlobalBounds().height / 2);
	BackgroundTexture.loadFromFile("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\menu_background.png");
	BackgroundSprite.setTexture(BackgroundTexture);
	BackgroundSprite.setScale((float)MainWindow->getSize().x / (float)BackgroundTexture.getSize().x, (float)MainWindow->getSize().y / (float)BackgroundTexture.getSize().y);

	//---> Создание кнопок.
	//=======================================================================================================================//
	BT_Play.Initialize(MainWindow, sf::Vector2u(57, 48));
	BT_Play.SetPosition((float)MainWindow->getSize().x * 0.085, (float)MainWindow->getSize().y * 0.66);
	//Масштабирование в 20% высоты окна.
	*Scale = MainWindow->getSize().y / 5;
	*Scale = *Scale / 48;
	BT_Play.SetScale(*Scale);
	BT_Play.LoadTexture("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\menu_button_play.png", 3);

	BT_Credits.Initialize(MainWindow, sf::Vector2u(71, 60));
	BT_Credits.SetPosition((float)MainWindow->getSize().x * 0.58, (float)MainWindow->getSize().y * 0.66);
	//Масштабирование в 20% высоты окна.
	*Scale = MainWindow->getSize().y / 5;
	*Scale = *Scale / 60;
	BT_Credits.SetScale(*Scale);
	BT_Credits.LoadTexture("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\menu_button_credits.png", 3);

	BT_Exit.Initialize(MainWindow, sf::Vector2u(49, 39));
	BT_Exit.SetPosition((float)MainWindow->getSize().x * 0.78, (float)MainWindow->getSize().y * 0.66);
	//Масштабирование в 15% высоты окна.
	*Scale = MainWindow->getSize().y / 5;
	*Scale = *Scale / 39;
	BT_Exit.SetScale(*Scale);
	BT_Exit.LoadTexture("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\menu_button_exit.png", 3);

	BT_Settings.Initialize(MainWindow, sf::Vector2u(30, 31));
	BT_Settings.SetPosition((float)MainWindow->getSize().x * 0.36, (float)MainWindow->getSize().y * 0.66);
	//Масштабирование в 15% высоты окна.
	*Scale = MainWindow->getSize().y / 5;
	*Scale = *Scale / 31;
	BT_Settings.SetScale(*Scale);
	BT_Settings.LoadTexture("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\menu_button_settings.png", 3);

	//---> Загрузка шрифта и надписей.
	//=======================================================================================================================//
	//Выбранный язык.
	std::wstring* Local = new std::wstring;
	*Local = DUBLIB::GetMarkeredStringFromFile(L"Settings.txt", L"game-local");
	ButtonsLabels = DUBLIB::GetMarkeredStringsArrayFromFile(L"Data\\Local\\" + *Local + L".txt", L"main-menu");
	TextFont.loadFromFile("Data\\Fonts\\" + DUBLIB::GetMarkeredStringFromFile("Settings.txt", "game-font-pixel"));

	CL_Description.SetFont(&TextFont);
	CL_Description.SetPosition(0, MainWindow->getSize().y * 0.85);
	CL_Description.SetCharacterSize(48);
	CL_Description.SetStyle(sf::Text::Bold);
	CL_Description.Initialize(MainWindow, L" ", sf::Vector2u(MainWindow->getSize().x, MainWindow->getSize().y / 5));

	GameVersion.setString(DUBLIB::GetMarkeredStringFromFile("Settings.txt", "version"));
	GameVersion.setCharacterSize(18);
	GameVersion.setFont(TextFont);
	GameVersion.setStyle(sf::Text::Bold);
	GameVersion.setPosition(18, MainWindow->getSize().y - GameVersion.getLocalBounds().height - 18);


	delete TexturepackName;

	//---> Загрузка звуков и музыки.
	//=======================================================================================================================//
	BackgroundMusic.openFromFile("Data\\Sounds\\Forest.ogg");

	Open();

	//---> Загрузка шейдеров.
	//=======================================================================================================================//
	//BackgroundShader.loadFromFile("Data\\Shaders\\Pixelezation.frag", sf::Shader::Fragment);
	//BackgroundShader.setUniform("Resolution", sf::Vector2f(1280, 720));
	//BackgroundShader.setUniform("Texture", sf::Shader::CurrentTexture);
	//TestTexture.loadFromFile("123.jpg");
	//TestSprite.setTexture(TestTexture);
	//Frame.create(1280, 720);
	
}

//Выполнение цикла обновления класса.
std::string MainMenu::Update() {

	MainWindow->draw(BackgroundSprite);
	MainWindow->draw(LogoSprite);
	MainWindow->draw(GameVersion);

	//---> Обработка кнопок и сохранение их статусов.
	//=======================================================================================================================//
	ButtonsStatus[MenuButtons::Game] = BT_Play.Update();
	ButtonsStatus[MenuButtons::Settings] = BT_Settings.Update();
	ButtonsStatus[MenuButtons::Credits] = BT_Credits.Update();
	ButtonsStatus[MenuButtons::Exit] = BT_Exit.Update();

	//---> Звуковые эффекты наведения на кнопки.
	//=======================================================================================================================//
	for (unsigned int i = 0; i <= MenuButtons::Exit; i++) ButtonInteraction(i);
	if (LastSoundEffectIndex > 0 && ButtonsStatus[LastSoundEffectIndex - 1] == Button::Normal) LastSoundEffectIndex = 0;

	//---> Отправка ответа в обработчик меню.
	//=======================================================================================================================//
	//Если главное меню было закрыто, но обновляется снова, то отменить передачу ответа.
	if (Answer != "") { Answer.clear(); Open(); }
	//Переход к игре.
	if (ButtonsStatus[MenuButtons::Game] == Button::Clicked) Close("start_game");
	//Переход к игре.
	if (ButtonsStatus[MenuButtons::Settings] == Button::Clicked) Close("to_settings");
	//Переход к титрам.
	if (ButtonsStatus[MenuButtons::Credits] == Button::Clicked) Close("to_credits");
	//Выход из игры.
	if (ButtonsStatus[MenuButtons::Exit] == Button::Clicked) Close("exit");

	return Answer;
}