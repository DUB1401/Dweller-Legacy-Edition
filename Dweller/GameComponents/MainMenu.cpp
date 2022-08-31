#include "MainMenu.h"

// --->MainMenu
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
MainMenu::MainMenu(sf::RenderWindow* MainWindow, Settings* ObjectSettings) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->ObjectSettings = ObjectSettings;

	//---> Подгрузка необходимых текстур.
	//=======================================================================================================================//
	//Название текстурпака.
	std::string* TexturepackName = new std::string;
	LogoTexture.loadFromFile("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\logo.png");
	LogoSprite.setTexture(LogoTexture);
	LogoSprite.setOrigin(LogoTexture.getSize().x / 2, LogoTexture.getSize().y / 2);
	//Масштабирование в 25% высоты окна.
	float* Scale = new float;
	*Scale = MainWindow->getSize().y / 4;
	*Scale = *Scale / LogoTexture.getSize().y;
	LogoSprite.setScale(*Scale, *Scale);

	LogoSprite.setPosition(MainWindow->getSize().x / 2, LogoSprite.getGlobalBounds().height / 2);
	BackgroundTexture.loadFromFile("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\menu_background.png");
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
	BT_Play.LoadTexture("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\menu_button_play.png", 3);

	BT_Credits.Initialize(MainWindow, sf::Vector2u(71, 60));
	BT_Credits.SetPosition((float)MainWindow->getSize().x * 0.58, (float)MainWindow->getSize().y * 0.66);
	//Масштабирование в 20% высоты окна.
	*Scale = MainWindow->getSize().y / 5;
	*Scale = *Scale / 60;
	BT_Credits.SetScale(*Scale);
	BT_Credits.LoadTexture("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\menu_button_credits.png", 3);

	BT_Exit.Initialize(MainWindow, sf::Vector2u(49, 39));
	BT_Exit.SetPosition((float)MainWindow->getSize().x * 0.78, (float)MainWindow->getSize().y * 0.66);
	//Масштабирование в 15% высоты окна.
	*Scale = MainWindow->getSize().y / 5;
	*Scale = *Scale / 39;
	BT_Exit.SetScale(*Scale);
	BT_Exit.LoadTexture("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\menu_button_exit.png", 3);

	BT_Settings.Initialize(MainWindow, sf::Vector2u(30, 31));
	BT_Settings.SetPosition((float)MainWindow->getSize().x * 0.36, (float)MainWindow->getSize().y * 0.66);
	//Масштабирование в 15% высоты окна.
	*Scale = MainWindow->getSize().y / 5;
	*Scale = *Scale / 31;
	BT_Settings.SetScale(*Scale);
	BT_Settings.LoadTexture("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\GUI\\menu_button_settings.png", 3);

	//---> Загрузка шрифта и надписей.
	//=======================================================================================================================//
	ButtonsLabels = DUBLIB::GetMarkeredStringsArrayFromFile(L"Data\\Local\\" + ObjectSettings->Local.AsWstring() + L".txt", L"main-menu");
	TextFont.loadFromFile("Data\\Fonts\\" + ObjectSettings->PixelFont.AsString());

	CL_Description.SetFont(&TextFont);
	CL_Description.SetPosition(0, MainWindow->getSize().y * 0.85);
	CL_Description.SetCharacterSize(48);
	CL_Description.SetStyle(sf::Text::Bold);
	CL_Description.Initialize(MainWindow, L"", sf::Vector2u(MainWindow->getSize().x, MainWindow->getSize().y / 5));
	CL_Description.SetOutline(sf::Color::Black, 2);

	GameVersion.setString(ObjectSettings->Version.AsString());
	GameVersion.setCharacterSize(18);
	GameVersion.setFont(TextFont);
	GameVersion.setStyle(sf::Text::Bold);
	GameVersion.setPosition(18, MainWindow->getSize().y - GameVersion.getLocalBounds().height - 18);


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
	ButtonsStatus[static_cast<unsigned int>(MenuButtons::Game)] = BT_Play.Update();
	ButtonsStatus[static_cast<unsigned int>(MenuButtons::Settings)] = BT_Settings.Update();
	ButtonsStatus[static_cast<unsigned int>(MenuButtons::Credits)] = BT_Credits.Update();
	ButtonsStatus[static_cast<unsigned int>(MenuButtons::Exit)] = BT_Exit.Update();

	//---> Звуковые эффекты наведения на кнопки.
	//=======================================================================================================================//
	for (unsigned int i = 0; i <= static_cast<unsigned int>(MenuButtons::Exit); i++) ButtonInteraction(i);
	if (LastSoundEffectIndex > 0 && ButtonsStatus[LastSoundEffectIndex - 1] == Button::Normal) LastSoundEffectIndex = 0;

	//---> Отправка ответа в обработчик меню.
	//=======================================================================================================================//
	//Если главное меню было закрыто, но обновляется снова, то отменить передачу ответа.
	if (Answer != "") { Answer.clear(); Open(); }
	//Переход к игре.
	if (ButtonsStatus[static_cast<unsigned int>(MenuButtons::Game)] == Button::Clicked) Close("start_game");
	//Переход к игре.
	if (ButtonsStatus[static_cast<unsigned int>(MenuButtons::Settings)] == Button::Clicked) Close("to_settings");
	//Переход к титрам.
	if (ButtonsStatus[static_cast<unsigned int>(MenuButtons::Credits)] == Button::Clicked) Close("to_credits");
	//Выход из игры.
	if (ButtonsStatus[static_cast<unsigned int>(MenuButtons::Exit)] == Button::Clicked) Close("exit");

	return Answer;
}