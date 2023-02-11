#include "MainMenu.h"

//---> MainMenu
//========================================================================================================================//

// Закрытие главного меню.
void MainMenu::Close(std::string To, std::string From) {
	// Передача сообщения в обработчик меню.
	Answer.from = From;
	Answer.to = To;
	// Отключение проигрывания музыки.
	BackgroundMusic.stop();
}

// Открытие главного меню.
void MainMenu::Open() {
	// Воспроизведение фоновой музыки.
	BackgroundMusic.play();
}

// Проигрывает звуковой эффект.
void MainMenu::PlaySoundEffect(unsigned int Index) {
	if (SoundEffect.getStatus() != sf::Music::Playing) {
		SoundEffect.openFromFile("Data\\Sounds\\" + SoundsNames[Index] + ".ogg");
		SoundEffect.play();
	}
}

// Проверяет и обрабатывает взаимодействие с кнопками.
void MainMenu::ButtonInteraction(unsigned int Index) {
	if (ButtonsStatus[Index] == DUBGUI::ObjectGUI::Status::Hover) {
		if (LastSoundEffectIndex == 0) {
			PlaySoundEffect(Index);
			LastSoundEffectIndex = Index + 1;
			CL_Description.setString(ButtonsLabels[Index]);
		}
		CL_Description.update();
	}
}

// Конструктор: задаёт окно отрисовки технических данных.
MainMenu::MainMenu(sf::RenderWindow* MainWindow, Settings* ObjectSettings) {

	//---> Передача аргументов.
	//========================================================================================================================//
	this->MainWindow = MainWindow;
	this->ObjectSettings = ObjectSettings;

	//---> Подгрузка необходимых текстур.
	//========================================================================================================================//
	// Название текстурпака.
	LogoTexture.loadFromFile("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\logo.png");
	LogoSprite.setTexture(LogoTexture);
	LogoSprite.setOrigin(LogoTexture.getSize().x / 2, LogoTexture.getSize().y / 2);
	// Масштабирование в 25% высоты окна.
	float* Scale = new float;
	*Scale = MainWindow->getSize().y / 4;
	*Scale = *Scale / LogoTexture.getSize().y;
	LogoSprite.setScale(*Scale, *Scale);

	LogoSprite.setPosition(MainWindow->getSize().x / 2, LogoSprite.getGlobalBounds().height / 2);
	BackgroundTexture.loadFromFile("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\menu_background.png");
	BackgroundSprite.setTexture(BackgroundTexture);
	BackgroundSprite.setScale((float)MainWindow->getSize().x / (float)BackgroundTexture.getSize().x, (float)MainWindow->getSize().y / (float)BackgroundTexture.getSize().y);

	//---> Создание кнопок.
	//========================================================================================================================//
	// Масштабирование в 20% высоты окна.
	*Scale = MainWindow->getSize().y / 5;
	*Scale = *Scale / 48;
	// Настройка кнопки.
	BT_Play.setPosition((float)MainWindow->getSize().x * 0.085, (float)MainWindow->getSize().y * 0.66);
	BT_Play.setScale(*Scale);
	BT_Play.loadTexture("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\menu_button_play.png", sf::Vector2u(57, 48), DUBGUI::Button::SlicingType::Triple);
	BT_Play.initialize(MainWindow);

	// Масштабирование в 20% высоты окна.
	*Scale = MainWindow->getSize().y / 5;
	*Scale = *Scale / 60;
	// Настройка кнопки.
	BT_Credits.setPosition((float)MainWindow->getSize().x * 0.58, (float)MainWindow->getSize().y * 0.66);
	BT_Credits.setScale(*Scale);
	BT_Credits.loadTexture("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\menu_button_credits.png", sf::Vector2u(71, 60), DUBGUI::Button::SlicingType::Triple);
	BT_Credits.initialize(MainWindow);

	// Масштабирование в 20% высоты окна.
	*Scale = MainWindow->getSize().y / 5;
	*Scale = *Scale / 39;
	// Настройка кнопки.
	BT_Exit.setPosition((float)MainWindow->getSize().x * 0.78, (float)MainWindow->getSize().y * 0.66);
	BT_Exit.setScale(*Scale);
	BT_Exit.loadTexture("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\menu_button_exit.png", sf::Vector2u(49, 39), DUBGUI::Button::SlicingType::Triple);
	BT_Exit.initialize(MainWindow);

	// Масштабирование в 20% высоты окна.
	*Scale = MainWindow->getSize().y / 5;
	*Scale = *Scale / 31;
	// Настройка кнопки.
	BT_Settings.setPosition((float)MainWindow->getSize().x * 0.36, (float)MainWindow->getSize().y * 0.66);
	BT_Settings.setScale(*Scale);
	BT_Settings.loadTexture("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\menu_button_settings.png", sf::Vector2u(30, 31), DUBGUI::Button::SlicingType::Triple);
	BT_Settings.initialize(MainWindow);

	delete Scale;

	//---> Загрузка шрифта и надписей.
	//========================================================================================================================//
	ButtonsLabels = DUBLIB::GetMarkeredStringsArrayFromFile(L"Data\\Local\\" + ObjectSettings->Local.AsWstring() + L".txt", L"main-menu");
	TextFont.loadFromFile("Data\\Fonts\\" + ObjectSettings->PixelFont.AsString());

	CL_Description.setFont(&TextFont);
	CL_Description.setPosition(0, MainWindow->getSize().y * 0.85);
	CL_Description.setCharacterSize(48);
	CL_Description.setStyle(sf::Text::Bold);
	CL_Description.initialize(MainWindow, L"", sf::Vector2u(MainWindow->getSize().x, MainWindow->getSize().y / 5));
	CL_Description.setOutline(sf::Color::Black, 2);

	GameVersion.setString(ObjectSettings->Version.AsString());
	GameVersion.setCharacterSize(18);
	GameVersion.setFont(TextFont);
	GameVersion.setStyle(sf::Text::Bold);
	GameVersion.setPosition(18, MainWindow->getSize().y - GameVersion.getLocalBounds().height - 18);

	//---> Загрузка звуков и музыки.
	//========================================================================================================================//
	BackgroundMusic.openFromFile("Data\\Sounds\\Forest.ogg");
	Open();

}

// Выполнение цикла обновления класса.
LayoutAnswer MainMenu::Update() {

	MainWindow->draw(BackgroundSprite);
	MainWindow->draw(LogoSprite);
	MainWindow->draw(GameVersion);

	//---> Обработка кнопок и сохранение их статусов.
	//========================================================================================================================//
	ButtonsStatus[static_cast<unsigned int>(MenuButtons::Game)] = BT_Play.update();
	ButtonsStatus[static_cast<unsigned int>(MenuButtons::Settings)] = BT_Settings.update();
	ButtonsStatus[static_cast<unsigned int>(MenuButtons::Credits)] = BT_Credits.update();
	ButtonsStatus[static_cast<unsigned int>(MenuButtons::Exit)] = BT_Exit.update();

	//---> Звуковые эффекты наведения на кнопки.
	//========================================================================================================================//
	for (unsigned int i = 0; i <= static_cast<unsigned int>(MenuButtons::Exit); i++) ButtonInteraction(i);
	if (LastSoundEffectIndex > 0 && ButtonsStatus[LastSoundEffectIndex - 1] == DUBGUI::ObjectGUI::Status::Normal) LastSoundEffectIndex = 0;

	//---> Отправка ответа в обработчик меню.
	//========================================================================================================================//
	// Переход к игре.
	if (ButtonsStatus[static_cast<unsigned int>(MenuButtons::Game)] == DUBGUI::ObjectGUI::Status::Clicked) Close("start_game", "menu");
	// Переход к игре.
	if (ButtonsStatus[static_cast<unsigned int>(MenuButtons::Settings)] == DUBGUI::ObjectGUI::Status::Clicked) Close("settings", "menu");
	// Переход к титрам.
	if (ButtonsStatus[static_cast<unsigned int>(MenuButtons::Credits)] == DUBGUI::ObjectGUI::Status::Clicked) Close("credits", "menu");
	// Выход из игры.
	if (ButtonsStatus[static_cast<unsigned int>(MenuButtons::Exit)] == DUBGUI::ObjectGUI::Status::Clicked) Close("exit", "menu");

	return Answer;
}