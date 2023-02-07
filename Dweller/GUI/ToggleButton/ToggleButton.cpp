#include "ToggleButton.h"

//---> ToggleButton
//========================================================================================================================//

namespace DUBGUI {

	// Проверяет попадание курсора в область переключателя.
	bool ToggleButton::CheckMouseHover() {
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

	// Возвращает индекс спрайта в зависимости от настроек, статуса и значения.
	unsigned int ToggleButton::GetSpriteIndex() {
		// Индекс спрайта.
		unsigned int SpriteIndex = 0;
		// Модификатор статуса переключателя.
		unsigned int ToggleButtonStatusModificator;

		// Если переключатель имеет статус без соответствующего спрайта, дать ей максимальный индекс, иначе преобразовать статус в индекс.
		if (ToggleButtonStatus == Status::Clicked) ToggleButtonStatusModificator = 3;
		else ToggleButtonStatusModificator = static_cast<unsigned int>(ToggleButtonStatus) + 1;
		// Если индекс спрайта больше заданного количества спрайтов на значение переключателя, то установить максимально возможный индекс.
		if (ToggleButtonStatusModificator > SpriteLinesCount) ToggleButtonStatusModificator = SpriteLinesCount;
		// Если переключатель включен, то задать индекс со сдвигом, иначе к индексу со сдвигом прибавить количество спрайтов включённой формы переключателя.
		if (ToggleButtonValue) SpriteIndex = ToggleButtonStatusModificator - 1;
		else SpriteIndex = ToggleButtonStatusModificator - 1 + SpriteLinesCount;

		return SpriteIndex;
	}

	// Стандартный конструктор.
	ToggleButton::ToggleButton() {

	}

	// Инициализатор: задаёт окно отрисовки. Вызывать после установки всех свойств и загрузки текстуры.
	void ToggleButton::initialize(sf::RenderWindow* MainWindow) {

		//---> Передача аргументов.
		//========================================================================================================================//
		this->MainWindow = MainWindow;

		// Настройка спрайтов.
		for (unsigned int i = 0; i < SpriteLinesCount * 2; i++) {
			ToggleButtonSprites[i].setPosition(Position);
			ToggleButtonSprites[i].setScale(Scale);
		}
	}

	// Устанавливает позицию в окне.
	void ToggleButton::setPosition(sf::Vector2f Position) {
		this->Position = Position;
	}

	// Устанавливает позицию в окне.
	void ToggleButton::setPosition(float PositionX, float PositionY) {
		this->Position = sf::Vector2f(PositionX, PositionY);
	}

	// Устанавливает масштаб спрайта.
	void ToggleButton::setScale(float Scale) {
		this->Scale = sf::Vector2f(Scale, Scale);
	}

	// Загружает текстуру переключателя и разрезает её на спрайты согласно выбранному режиму.
	bool ToggleButton::loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType SlicingType) {

		//---> Передача аргументов.
		//========================================================================================================================//
		this->SpriteLinesCount = static_cast<unsigned int>(SlicingType);
		this->Size = SpriteSize;

		// Проверка загрузки текстуры.
		if (ToggleButtonTexture.loadFromFile(Path)) {
			// Буфер подгрузки спрайтов.
			sf::Sprite ToggleButtonSpriteBufer;

			// Настройка спрайтов.
			for (unsigned int i = 0; i < SpriteLinesCount * 2; i++) {
				ToggleButtonSprites.push_back(ToggleButtonSpriteBufer);
				ToggleButtonSprites[i].setPosition(Position);
				ToggleButtonSprites[i].setTexture(ToggleButtonTexture);
				ToggleButtonSprites[i].setTextureRect(sf::IntRect(0, Size.y * i, Size.x, Size.y));
				ToggleButtonSprites[i].setScale(Scale);
			}
			return true;
		}
		else return false;
	}

	// Загружает текстуру переключателя и разрезает её на спрайты согласно выбранному режиму и направлению.
	bool ToggleButton::loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType SlicingType, SlicingOrientation Orientation) {

		//---> Передача аргументов.
		//========================================================================================================================//
		this->SpriteLinesCount = static_cast<unsigned int>(SlicingType);
		this->Size = SpriteSize;

		// Проверка загрузки текстуры.
		if (ToggleButtonTexture.loadFromFile(Path)) {
			// Буфер подгрузки спрайтов.
			sf::Sprite ToggleButtonSpriteBufer;

			// Настройка спрайтов.
			for (unsigned int i = 0; i < SpriteLinesCount * 2; i++) {
				ToggleButtonSprites.push_back(ToggleButtonSpriteBufer);
				ToggleButtonSprites[i].setPosition(Position);
				ToggleButtonSprites[i].setTexture(ToggleButtonTexture);
				if (Orientation == SlicingOrientation::Vertical) ToggleButtonSprites[i].setTextureRect(sf::IntRect(0, Size.y * i, Size.x, Size.y));
				else ToggleButtonSprites[i].setTextureRect(sf::IntRect(Size.x * i, 0, Size.x, Size.y));
				ToggleButtonSprites[i].setScale(Scale);
			}
			return true;
		}
		else return false;
	}

	// Возвращает значение переключателя.
	bool ToggleButton::getValue() {
		return ToggleButtonValue;
	}

	// Устанавливает значение переключателя.
	void ToggleButton::setValue(bool Value) {
		ToggleButtonValue = Value;
	}

	// Отрисовывание и обновление переключателя.
	ToggleButton::Status ToggleButton::update() {

		// Если курсор попадает на переключатель.
		if (CheckMouseHover()) {
			// Если ЛКМ не нажата.
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !ToggleButtonWasPressed) {
				ToggleButtonStatus = Status::Hover;
				ToggleButtonWasPressedOnAway = false;
			}

			// Если ЛКМ нажата сейчас, а в прошлом цикле – нет.
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !ToggleButtonWasPressed && !ToggleButtonWasPressedOnAway) {
				ToggleButtonWasPressed = true;
				ToggleButtonStatus = Status::Active;
			}

			// Если ЛКМ была нажата в прошлом цикле, а сейчас – нет.
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && ToggleButtonWasPressed && !ToggleButtonWasPressedOnAway) {
				ToggleButtonWasPressed = false;
				ToggleButtonStatus = Status::Clicked;
				ToggleButtonValue = DUBLIB::InvertBool(ToggleButtonValue);
			}
		}
		else {
			ToggleButtonStatus = Status::Normal;
			// Фикс срабатывания переключателя в случае, когда зажатая ЛКМ уходит с области фокуса.
			ToggleButtonWasPressed = false;
			// Фикс срабатывания переключателя в случае, когда зажатая ЛКМ приходит в область фокуса.
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !ToggleButtonWasPressedOnAway) ToggleButtonWasPressedOnAway = true;
		}

		MainWindow->draw(ToggleButtonSprites[GetSpriteIndex()]);

		return ToggleButtonStatus;
	}

}