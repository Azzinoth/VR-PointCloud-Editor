#include "SceneResources/SceneResources.h"
using namespace FocalEngine;

class ImGuiVirtualKeyboard
{
public:
    enum class VirtualKeyboardSpecialKey
    {
        BACKAPACE = 0,
		DELETE_KEY = 1,
		ENTER = 2,
		TAB = 3
    };
private:
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

    float KeyWidth = 64.0f;
    float KeyHeight = 64.0f;
    float KeyGap = 8.0f;

	bool bShouldRender = true;

	std::vector<std::function<void()>> OnTextChangedCallbacks;
	std::vector<std::function<void(char)>> OnCharacterInputCallbacks;
	std::vector<std::function<void(VirtualKeyboardSpecialKey)>> OnSpecialKeyCallbacks;

    VirtualKeyboardState CurrentVirtualKeyboardState;
    char ApplyLetterCase(char Charater, const VirtualKeyboardState& State);
    void DrawCharacterKey(char Character);
    void DrawSymbolKey(const char* BaseSymbol, const char* ShiftedSymbol);
    void DrawSpecialKey(const char* Label, float KeyWidthScale, std::function<void()> OnKeyPress);

	void OnCharacterInput(char Character);
    void OnSpecialKey(VirtualKeyboardSpecialKey Key);
public:
    void Initialize(float KeyWidth = 64.0f, float KeyHeight = 64.0f, float KeyGap = 8.0f);
	void DrawVirtualKeyboard();

    void AddOnCharacterInputCallback(std::function<void(char)> Callback);
    void ClearOnCharacterInputCallbacks();
    void AddOnSpecialKeyCallback(std::function<void(VirtualKeyboardSpecialKey)> Callback);
    void ClearOnSpecialKeyCallbacks();

    bool ShouldBeRendered() const;
	void SetShouldBeRendered(bool bNewValue);
};