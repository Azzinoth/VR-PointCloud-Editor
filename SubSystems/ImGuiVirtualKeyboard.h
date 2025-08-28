#include "SceneResources/SceneResources.h"
using namespace FocalEngine;

class ImGuiVirtualKeyboard
{
    struct VirtualKeyboardState
    {
        bool bIsShiftActive = false;
        bool bIsCapsLockActive = false;
    };

    struct VirtualKeyboardKey
    {
        const char* BaseSymbol;
        const char* ShiftedSymbol;
        float WidthUnits;
        const char* ID;
    };

	std::string* OutputString;
    float KeyWidth = 64.0f;
    float KeyHeight = 64.0f;
    float KeyGap = 8.0f;

	bool bShouldRender = true;

	std::vector<std::function<void()>> OnTextChangedCallbacks;

    VirtualKeyboardState CurrentVirtualKeyboardState;
    char ApplyLetterCase(char Charater, const VirtualKeyboardState& State);
    void DrawCharacterKey(char Character);
    void DrawSymbolKey(const char* BaseSymbol, const char* ShiftedSymbol);
    void DrawSpecialKey(const char* Label, float KeyWidthScale, std::function<void()> OnKeyPress);
	void OnTextChanged();
public:
    void Initialize(std::string& Output, float KeyWidth = 64.0f, float KeyHeight = 64.0f, float KeyGap = 8.0f);
	void DrawVirtualKeyboard();

    void AddOnTextChangedCallback(std::function<void()> Callback);
};