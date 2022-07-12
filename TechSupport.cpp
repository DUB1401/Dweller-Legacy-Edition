#include "TechSupport.h"
#include "EvolvGen.h"

//Конструктор: задаёт окно отрисовки технических данных и счётчик времени.
TechSupport::TechSupport(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;

	//---> Создание надписей для отображения технических данных.
	//=======================================================================================================================//
	//Настройка шаблона генерации надписей.
	sf::Text* TemplateLabel = new sf::Text;
	TemplateLabel->setFillColor(sf::Color::Green);
	TemplateLabel->setCharacterSize(12);
	//Загрузка шрифта.
	sf::Font* TemplateFont = new sf::Font;
	TemplateFont->loadFromFile("Data\\Fonts\\Arialuni.ttf");
	//Генерация надписей в цикле.
	for (unsigned int i = 0; i < 2; i++) {
		TechLabels.push_back(*TemplateLabel);
		TechLabels[i].setFont(*TemplateFont);
	}
	//Очистка переменных.
	delete TemplateLabel, TemplateFont;
}

//Переключить отображение FPS.
void TechSupport::SwitchShowingFPS(bool IsShowFPS) {
	this->IsShowFPS = IsShowFPS;
}

//Возвращает статус отображения FPS.
bool TechSupport::IsShowingFPS() {
	return this->IsShowFPS;
}

//Выполнение цикла обновления класса.
void TechSupport::Update() {
	//Обновление счётчика FPS.
	if (IsShowFPS) {
		LastFrameTime += *GlobalTimeAsSeconds;
		CurrentFPS++;

		//Если прошла секунда.
		if (LastFrameTime >= 1.0) {
			//Уменьшение прошедшего времени на секунду.
			LastFrameTime--;
			//Сохранение текущего FPS.
			LastSecondFPS = CurrentFPS;
			//Обнуление счётчика для следующего цикла.
			CurrentFPS = 0;

			TechLabels[tsFPS].setString("FPS: " + DUBLIB::ConvertNumberToString(LastSecondFPS));
		}
	}

	//Отрисовка технических надписей.
	for (unsigned int i = 0; i < TechLabels.size(); i++) MainWindow->draw(TechLabels[0]);
}