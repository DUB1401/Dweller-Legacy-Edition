#include "Button.h"

//---> Button
//========================================================================================================================//

namespace DUBGUI {

	// Возвращает индекс спрайта в зависимости от настроек, статуса и значения.
	unsigned int Button::GetSpriteIndex() {
		// Индекс спрайта.
		unsigned int SpriteIndex = 0;
		// Модификатор статуса кнопки.
		unsigned int ButtonStatusModificator;

		// Если кнопка имеет статус без соответствующего спрайта, дать ей максимальный индекс, иначе преобразовать статус в индекс.
		if (ButtonStatus == Status::Clicked) ButtonStatusModificator = 3;
		else ButtonStatusModificator = static_cast<unsigned int>(ButtonStatus) + 1;
		// Если индекс спрайта больше заданного количества спрайтов на значение кнопки, то установить максимально возможный индекс.
		if (ButtonStatusModificator > SpriteLinesCount) ButtonStatusModificator = SpriteLinesCount;
		// Компенсировать сдвиг индекса.
		SpriteIndex = ButtonStatusModificator - 1;
		
		return SpriteIndex;
	}

	// Конструктор: стандартный.
	Button::Button() {

	}

	// Инициализатор: задаёт окно отрисовки. Вызывать после установки всех свойств и загрузки текстуры.
	void Button::initialize(sf::RenderWindow* MainWindow) {
		//---> Передача аргументов.
		//========================================================================================================================//
		this->MainWindow = MainWindow;

		// Настройка спрайтов.
		for (unsigned int i = 0; i < SpriteLinesCount; i++) {
			ButtonSprites[i].setPosition(Position);
			ButtonSprites[i].setScale(Scale);
		}

		// Настройка обработчика взаимодействия с мышью.
		MouseProcessingObject.setPosition(Position);
		MouseProcessingObject.setScale(Scale);
		MouseProcessingObject.setSize(Size);
		MouseProcessingObject.initialize(MainWindow);
	}

	// Загружает текстуру кнопки и разрезает её на спрайты согласно выбранному режиму.
	bool Button::loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType SlicingType) {

		//---> Передача аргументов.
		//========================================================================================================================//
		this->SpriteLinesCount = static_cast<unsigned int>(SlicingType);
		this->Size = SpriteSize;

		// Проверка загрузки текстуры.
		if (ButtonTexture.loadFromFile(Path)) {
			// Буфер подгрузки спрайтов.
			sf::Sprite ButtonSpriteBufer;

			// Настройка спрайтов.
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

	// Загружает текстуру кнопки и разрезает её на спрайты согласно выбранному режиму и направлению.
	bool Button::loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType SlicingType, SlicingOrientation Orientation) {

		//---> Передача аргументов.
		//========================================================================================================================//
		this->SpriteLinesCount = static_cast<unsigned int>(SlicingType);
		this->Size = SpriteSize;

		// Проверка загрузки текстуры.
		if (ButtonTexture.loadFromFile(Path)) {
			// Буфер подгрузки спрайтов.
			sf::Sprite ButtonSpriteBufer;

			// Настройка спрайтов.
			for (unsigned int i = 0; i < SpriteLinesCount; i++) {
				ButtonSprites.push_back(ButtonSpriteBufer);
				ButtonSprites[i].setPosition(Position);
				ButtonSprites[i].setTexture(ButtonTexture);
				if (Orientation == SlicingOrientation::Vertical) ButtonSprites[i].setTextureRect(sf::IntRect(0, Size.y * i, Size.x, Size.y));
				else ButtonSprites[i].setTextureRect(sf::IntRect(Size.x * i, 0, Size.x, Size.y));
				ButtonSprites[i].setScale(Scale);
			}
			return true;
		}
		else return false;
	}

	// Устанавливает позицию в окне.
	void Button::setPosition(float PositionX, float PositionY) {
		this->Position = sf::Vector2f(PositionX, PositionY);
	}

	// Устанавливает позицию в окне.
	void Button::setPosition(sf::Vector2f Position) {
		this->Position = Position;
	}

	// Устанавливает масштаб спрайта.
	void Button::setScale(float Scale) {
		this->Scale = sf::Vector2f(Scale, Scale);
	}

	// Отрисовывает и обновляет кнопку.
	Button::Status Button::update() {

		// Отрисовывание кнопки.
		MainWindow->draw(ButtonSprites[GetSpriteIndex()]);
		// Обновление статуса кнопки.
		ButtonStatus = MouseProcessingObject.updateMouseButton(sf::Mouse::Left);

		return ButtonStatus;
	}

}