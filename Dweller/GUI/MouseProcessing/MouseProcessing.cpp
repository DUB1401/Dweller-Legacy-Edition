#include "MouseProcessing.h"

//---> MouseProcessing
//========================================================================================================================//

namespace DUBGUI {

	// Проверяет попадание курсора в область.
	bool MouseProcessing::CheckMouseHover() {
		// Сохранение координат мыши.
		sf::Vector2i MouseCoords = sf::Mouse::getPosition(*MainWindow);
		// Попадание по осям X и Y.
		bool AxisX = false, AxisY = false;
		// Проверка попадания по оси X.
		if (MouseCoords.x > Position.x && MouseCoords.x < Position.x + Size.x * Scale.x) AxisX = true;
		// Проверка попадания по оси Y.
		if (MouseCoords.y > Position.y && MouseCoords.y < Position.y + Size.y * Scale.y) AxisY = true;
		// Проверка полного попадания.
		if (AxisX && AxisY) return true; else return false;
	}

	// Обновляет отладочный прямоугольник.
	void MouseProcessing::UpdateDebugRectangle() {
		DebugRectangle.setSize(sf::Vector2f(Size.x, Size.y));
		DebugRectangle.setFillColor(DebugRectangleColor);
		DebugRectangle.setPosition(Position);
		DebugRectangle.setScale(Scale);
	}

	// Конструктор: пустой.
	MouseProcessing::MouseProcessing() {

	}

	// Инициализатор: задаёт используемое окно 
	void MouseProcessing::initialize(sf::RenderWindow* MainWindow) {
		//---> Передача аргументов.
		//========================================================================================================================//
		this->MainWindow = MainWindow;

		UpdateDebugRectangle();

	}

	// Устанавливает позицию в окне.
	void MouseProcessing::setPosition(float PositionX, float PositionY) {
		this->Position = sf::Vector2f(PositionX, PositionY);
		UpdateDebugRectangle();
	}

	// Устанавливает позицию в окне.
	void MouseProcessing::setPosition(sf::Vector2f Position) {
		this->Position = Position;
		UpdateDebugRectangle();
	}

	// Устанавливает масштаб обрабатываемой области.
	void MouseProcessing::setScale(sf::Vector2f Scale) {
		this->Scale = Scale;
		UpdateDebugRectangle();
	}

	// Устанавливает размер обрабатываемой области.
	void MouseProcessing::setSize(sf::Vector2u Size) {
		this->Size = Size;
		UpdateDebugRectangle();
	}

	// Устанавливает размер обрабатываемой области.
	void MouseProcessing::setSize(unsigned int SizeX, unsigned int SizeY) {
		this->Size = sf::Vector2u(SizeX, SizeY);
		UpdateDebugRectangle();
	}

	// Переключает отображение обрабатываемой области.
	void MouseProcessing::showDebugRectangle(bool IsShowDebugRectangle) {
		this->IsShowDebugRectangle = IsShowDebugRectangle;
	}

	// Переключает отображение обрабатываемой области и устанавливает цвет для неё.
	void MouseProcessing::showDebugRectangle(bool IsShowDebugRectangle, sf::Color DebugRectangleColor) {
		this->IsShowDebugRectangle = IsShowDebugRectangle;
		this->DebugRectangleColor = DebugRectangleColor;
	}

	// Обрабатывает взаимодействие с указанной кнопкой мыши.
	MouseProcessing::Status MouseProcessing::updateMouseButton(sf::Mouse::Button MouseButton) {

		// Если курсор попадает в обрабатываемую область, то проверить взаимодействия.
		if (CheckMouseHover()) {
			// Если кнопка мыши не нажата.
			if (!sf::Mouse::isButtonPressed(MouseButton) && !ButtonWasPressed[MouseButton]) {
				ButtonWasPressedOnAway[MouseButton] = false;
				BlockStatus[MouseButton] = Status::Hover;
			}
			// Если кнопка мыши нажата сейчас, а в прошлом цикле – нет.
			if (sf::Mouse::isButtonPressed(MouseButton) && !ButtonWasPressed[MouseButton] && !ButtonWasPressedOnAway[MouseButton]) {
				ButtonWasPressed[MouseButton] = true;
				BlockStatus[MouseButton] = Status::Active;
			}
			// Если кнопка мыши была нажата в прошлом цикле, а сейчас – нет.
			if (!sf::Mouse::isButtonPressed(MouseButton) && ButtonWasPressed[MouseButton] && !ButtonWasPressedOnAway[MouseButton]) {
				ButtonWasPressed[MouseButton] = false;
				BlockStatus[MouseButton] = Status::Clicked;
			}
		}
		else {
			BlockStatus[MouseButton] = Status::Normal;
			// Фикс срабатывания обработчика в случае, когда зажатая кнопка мыши уходит с области фокуса.
			ButtonWasPressed[MouseButton] = false;
			// Фикс срабатывания обработчика в случае, когда зажатая кнопка мыши приходит в область фокуса.
			if (sf::Mouse::isButtonPressed(MouseButton) && !ButtonWasPressedOnAway[MouseButton]) ButtonWasPressedOnAway[MouseButton] = true;
		}

		// Отрисовка отладочного прямоугольника.
		if (IsShowDebugRectangle) MainWindow->draw(DebugRectangle);

		return BlockStatus[MouseButton];

	}

}