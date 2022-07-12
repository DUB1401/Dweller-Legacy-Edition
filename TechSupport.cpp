#include "TechSupport.h"
#include "EvolvGen.h"

//�����������: ����� ���� ��������� ����������� ������ � ������� �������.
TechSupport::TechSupport(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds) {

	//---> �������� ����������.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;

	//---> �������� �������� ��� ����������� ����������� ������.
	//=======================================================================================================================//
	//��������� ������� ��������� ��������.
	sf::Text* TemplateLabel = new sf::Text;
	TemplateLabel->setFillColor(sf::Color::Green);
	TemplateLabel->setCharacterSize(12);
	//�������� ������.
	sf::Font* TemplateFont = new sf::Font;
	TemplateFont->loadFromFile("Data\\Fonts\\Arialuni.ttf");
	//��������� �������� � �����.
	for (unsigned int i = 0; i < 2; i++) {
		TechLabels.push_back(*TemplateLabel);
		TechLabels[i].setFont(*TemplateFont);
	}
	//������� ����������.
	delete TemplateLabel, TemplateFont;
}

//����������� ����������� FPS.
void TechSupport::SwitchShowingFPS(bool IsShowFPS) {
	this->IsShowFPS = IsShowFPS;
}

//���������� ������ ����������� FPS.
bool TechSupport::IsShowingFPS() {
	return this->IsShowFPS;
}

//���������� ����� ���������� ������.
void TechSupport::Update() {
	//���������� �������� FPS.
	if (IsShowFPS) {
		LastFrameTime += *GlobalTimeAsSeconds;
		CurrentFPS++;

		//���� ������ �������.
		if (LastFrameTime >= 1.0) {
			//���������� ���������� ������� �� �������.
			LastFrameTime--;
			//���������� �������� FPS.
			LastSecondFPS = CurrentFPS;
			//��������� �������� ��� ���������� �����.
			CurrentFPS = 0;

			TechLabels[tsFPS].setString("FPS: " + DUBLIB::ConvertNumberToString(LastSecondFPS));
		}
	}

	//��������� ����������� ��������.
	for (unsigned int i = 0; i < TechLabels.size(); i++) MainWindow->draw(TechLabels[0]);
}