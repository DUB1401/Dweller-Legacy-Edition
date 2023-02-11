#pragma once

#include "../EvolvGen.h"
#include "../GUI.h"

namespace DUBGUI {

	// Обработчик взаимодействий с мышью.
	class MouseProcessing : public ObjectGUI {
	private:

		//---> Данные.
		//========================================================================================================================//
		// Размер блока.
		sf::Vector2u Size;
		// Оконные координаты блока.
		sf::Vector2f Position;
		// Масштаб блока.
		sf::Vector2f Scale = { 1.f, 1.f };
		// Указатель на используемое окно.
		sf::RenderWindow* MainWindow;
		// Была ли нажата кнопка мыши в предыдущем цикле.
		std::map<sf::Mouse::Button, bool> ButtonWasPressed = { 
			{sf::Mouse::Button::Left, false},
			{sf::Mouse::Button::Middle, false},
			{sf::Mouse::Button::Right, false}
		};
		// Была ли нажата кнопка мыши до наведения.
		std::map<sf::Mouse::Button, bool> ButtonWasPressedOnAway = {
			{sf::Mouse::Button::Left, false},
			{sf::Mouse::Button::Middle, false},
			{sf::Mouse::Button::Right, false}
		};
		// Текущее состояние обрабатываемой области.
		std::map< sf::Mouse::Button, Status> BlockStatus = {
			{sf::Mouse::Button::Left, Status::Normal},
			{sf::Mouse::Button::Middle, Status::Normal},
			{sf::Mouse::Button::Right, Status::Normal}
		};
		// Переключатель: включено ли отображение обрабатываемой области.
		bool IsShowDebugRectangle = false;

		//---> Свойства графических компонентов.
		//========================================================================================================================//
		// Цвет отладочного треугольника.
		sf::Color DebugRectangleColor = sf::Color(255, 0, 0, 128);

		//---> Графические компоненты.
		//========================================================================================================================//
		// Отладочный прямоугольник обрабатываемой области.
		sf::RectangleShape DebugRectangle;

		//---> Функции обработки.
		//========================================================================================================================//
		// Проверяет попадание курсора в область.
		bool CheckMouseHover();
		// Обновляет отладочный прямоугольник.
		void UpdateDebugRectangle();

	public:

		// Конструктор: пустой.
		MouseProcessing();

		// Инициализатор: задаёт используемое окно. Вызывать после установки всех свойств.
		void initialize(sf::RenderWindow* MainWindow);

		// Устанавливает позицию обрабатываемой области в окне.
		void setPosition(float PositionX, float PositionY);

		// Устанавливает позицию обрабатываемой области в окне.
		void setPosition(sf::Vector2f Position);

		// Устанавливает масштаб обрабатываемой области.
		void setScale(sf::Vector2f Scale);

		// Устанавливает размер обрабатываемой области.
		void setSize(sf::Vector2u Size);

		// Устанавливает размер обрабатываемой области.
		void setSize(unsigned int SizeX, unsigned int SizeY);

		// Переключает отображение обрабатываемой области.
		void showDebugRectangle(bool IsShowDebugRectangle);

		// Переключает отображение обрабатываемой области и устанавливает цвет для неё.
		void showDebugRectangle(bool IsShowDebugRectangle, sf::Color DebugRectangleColor);

		// Обрабатывает взаимодействие с указанной кнопкой мыши.
		Status updateMouseButton(sf::Mouse::Button MouseButton);

	};

}