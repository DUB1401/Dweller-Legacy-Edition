#include "Button.h"

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