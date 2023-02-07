#include "TechSupport.h"

struct cpuid_regs {
	DWORD   Eax;
	DWORD   Ebx;
	DWORD   Ecx;
	DWORD   Edx;
};

std::string SplitIntoChars(DWORD Value) {
	std::string Str;
	char const* pCursor = (char const*)&Value;
	for (int i = 0; i < sizeof(Value); i++) Str += pCursor[i];
	return Str;
}

std::string GetCpuVendorSubstring(DWORD Eax) {
	cpuid_regs Regs;
	__cpuid((int*)&Regs, Eax);
	std::string Str;
	Str += SplitIntoChars(Regs.Eax);
	Str += SplitIntoChars(Regs.Ebx);
	Str += SplitIntoChars(Regs.Ecx);
	Str += SplitIntoChars(Regs.Edx);
	return Str;
}

std::string GetCpuVendorString() {
	std::string VendorString;
	cpuid_regs Regs;
	__cpuid((int*)&Regs, 0x80000000);
	if (Regs.Eax >= 0x80000004) VendorString = GetCpuVendorSubstring(0x80000002) + GetCpuVendorSubstring(0x80000003) + GetCpuVendorSubstring(0x80000004);
	return VendorString;
}

// Получает список установленных видеокарт.
std::vector<std::string> TechSupport::GetGPU() {
	IDXGIFactory1* pFactory;
	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&pFactory));
	unsigned int AdapterNumber = 0;
	IDXGIAdapter1* Adapter;
	std::vector<std::string> AllCards;
	while (pFactory->EnumAdapters1(AdapterNumber++, &Adapter) != DXGI_ERROR_NOT_FOUND) {
		DXGI_ADAPTER_DESC1 Desc;
		Adapter->GetDesc1(&Desc);
		_bstr_t b(Desc.Description);
		AllCards.push_back((std::string)(char*)b);
		Adapter->Release();
	}
	pFactory->Release();
	return AllCards;
}

// Конструктор: задаёт окно отрисовки технических данных и счётчик времени.
TechSupport::TechSupport(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds) {

	//---> Передача аргументов.
	//========================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;

	//---> Создание надписей для отображения технических данных.
	//========================================================================================================================//
	// Настройка шаблона генерации надписей.
	sf::Text* TemplateLabel = new sf::Text;
	TemplateLabel->setFillColor(sf::Color::Green);
	TemplateLabel->setCharacterSize(12);
	// Загрузка шрифта.
	sf::Font* TemplateFont = new sf::Font;
	TemplateFont->loadFromFile("Data\\Fonts\\Arialuni.ttf");
	// Генерация надписей в цикле.
	for (unsigned int i = 0; i < 2; i++) {
		TechLabels.push_back(*TemplateLabel);
		TechLabels[i].setFont(*TemplateFont);
	}
	// Очистка переменных.
	delete TemplateLabel, TemplateFont;
}

// Переключить отображение FPS.
void TechSupport::SwitchShowingFPS(bool IsShowFPS) {
	this->IsShowFPS = IsShowFPS;
}

// Возвращает статус отображения FPS.
bool TechSupport::IsShowingFPS() {
	return this->IsShowFPS;
}

// Выполнение цикла обновления класса.
void TechSupport::Update() {
	// Обновление счётчика FPS.
	if (IsShowFPS) {
		LastFrameTime += *GlobalTimeAsSeconds;
		CurrentFPS++;

		// Если прошла секунда.
		if (LastFrameTime >= 1.0) {
			// Уменьшение прошедшего времени на секунду.
			LastFrameTime--;
			// Сохранение текущего FPS.
			LastSecondFPS = CurrentFPS;
			// Обнуление счётчика для следующего цикла.
			CurrentFPS = 0;

			TechLabels[tsFPS].setString("FPS: " + DUBLIB::ConvertNumberToString(LastSecondFPS));
		}
	}

	// Отрисовка технических надписей.
	for (unsigned int i = 0; i < TechLabels.size(); i++) MainWindow->draw(TechLabels[0]);
}