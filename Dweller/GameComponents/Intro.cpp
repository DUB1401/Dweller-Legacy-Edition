#include "Intro.h"

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
Intro::Intro(sf::RenderWindow* MainWindow, Settings* ObjectSettings, double* GlobalTimeAsSeconds, unsigned long long int* GlobalTimeAsMicroseconds) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;
	this->GlobalTimeAsMicroseconds = GlobalTimeAsMicroseconds;
	this->ObjectSettings = ObjectSettings;

	//---> Загрузка историй из текстового файла и шрифта.
	//=======================================================================================================================//
	Book = DUBLIB::GetMarkeredStringsArrayFromFile(L"Data\\Local\\" + ObjectSettings->Local.AsWstring() + L".txt", L"intro");
	TextFont.loadFromFile("Data\\Fonts\\" + ObjectSettings->Font.AsString());

	//---> Загрузка иллюстраций и установка их положения по центру экрана. 
	//=======================================================================================================================//
	//Буферы.
	sf::Texture BufferTexture;
	sf::Sprite BufferSprite;
	std::string Path;
	//Обработка загрузки и позиционирования.
	for (unsigned int i = 0; i < 9; i++) {
		Path = "Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\Story\\Story" + DUBLIB::ConvertNumberToString(i + 1) + ".png";

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
	PressAnyKey.Initialize(MainWindow, DUBLIB::GetMarkeredStringFromFile(L"Data\\Local\\" + ObjectSettings->Local.AsWstring() + L".txt", L"press-anykey"), sf::Vector2u(MainWindow->getSize().x, 20));

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