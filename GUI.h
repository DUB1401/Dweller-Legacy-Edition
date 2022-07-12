#pragma once

#include <SFML/Graphics.hpp>

//��������� ������� �������.
//TO-DO: ��������� ������: ������ ������� ������ ������ �����, ����� ������� �����.
class KeystrokesProcessing {
private:

	//������� �������.
	sf::Keyboard::Key TargetKey;
	//���� �� ������ ������� � ������� �����.
	bool IsKeyWasPressed = false;


public:

	//�����������: ����� �������������� ������� � �����.
	KeystrokesProcessing(sf::Keyboard::Key TargetKey) {
		this->TargetKey = TargetKey;
	}

	//�������� ��������� �������.
	bool Update() {
		//�������� ������� �������.
		if (sf::Keyboard::isKeyPressed(TargetKey))

		return 1;
	}


};

