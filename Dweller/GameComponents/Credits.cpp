#include "Credits.h"

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
	std::string* TexturepackName = new std::string;
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