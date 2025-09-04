#include "ImGuiVirtualKeyboard.h"
using namespace FocalEngine;

char ImGuiVirtualKeyboard::ApplyLetterCase(char Charater, const VirtualKeyboardState& State)
{
    if (!std::isalpha(static_cast<unsigned char>(Charater)))
        return Charater;

    bool bIsUpperCase = State.bIsCapsLockActive ^ State.bIsShiftActive; // XOR: Shift flips Caps
    return bIsUpperCase ? static_cast<char>(std::toupper((unsigned char)Charater)) : static_cast<char>(std::tolower((unsigned char)Charater));
}

void ImGuiVirtualKeyboard::DrawCharacterKey(char Character)
{
    char ButtonLabel[8] = { 0 };
    ButtonLabel[0] = ApplyLetterCase(Character, CurrentVirtualKeyboardState);
    ButtonLabel[1] = '\0';
    if (ImGui::Button(ButtonLabel, ImVec2(KeyWidth, KeyHeight)))
    {
        OnCharacterInput(ButtonLabel[0]);
        if (CurrentVirtualKeyboardState.bIsShiftActive && !CurrentVirtualKeyboardState.bIsCapsLockActive)
            CurrentVirtualKeyboardState.bIsShiftActive = false;
    }
}

void ImGuiVirtualKeyboard::DrawSymbolKey(const char* BaseSymbol, const char* ShiftedSymbol)
{
    const bool bIsShifted = CurrentVirtualKeyboardState.bIsShiftActive ^ false; // shift only (caps doesn’t affect symbols)
    const char* DisplayedSymbol = (bIsShifted && ShiftedSymbol) ? ShiftedSymbol : BaseSymbol;
    char ButtonLabel[8] = { 0 };

    if (DisplayedSymbol && DisplayedSymbol[0] && !DisplayedSymbol[1])
    {
        ButtonLabel[0] = DisplayedSymbol[0];
        ButtonLabel[1] = '\0';
    }
    else
    {
        snprintf(ButtonLabel, sizeof(ButtonLabel), "%s", DisplayedSymbol ? DisplayedSymbol : "?");
    }

    if (ImGui::Button(ButtonLabel, ImVec2(KeyWidth, KeyHeight)))
    {
        const char CharacterToAdd = (bIsShifted && ShiftedSymbol) ? ShiftedSymbol[0] : BaseSymbol[0];
		OnCharacterInput(CharacterToAdd);
        if (CurrentVirtualKeyboardState.bIsShiftActive && !CurrentVirtualKeyboardState.bIsCapsLockActive)
            CurrentVirtualKeyboardState.bIsShiftActive = false;
    }
}

void ImGuiVirtualKeyboard::DrawSpecialKey(const char* Label, float KeyWidthScale, std::function<void()> OnKeyPress)
{
    if (ImGui::Button(Label, ImVec2(KeyWidth * KeyWidthScale, KeyHeight)))
        OnKeyPress();
}

void ImGuiVirtualKeyboard::Initialize(float KeyWidth, float KeyHeight, float KeyGap)
{
	this->KeyWidth = KeyWidth;
	this->KeyHeight = KeyHeight;
	this->KeyGap = KeyGap;
}

void ImGuiVirtualKeyboard::DrawVirtualKeyboard()
{
    if (!bShouldRender)
		return;

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(1140.0f, 408.0f));
    ImGui::Begin("##Virtual Keyboard", nullptr, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    ImGuiStyle& Style = ImGui::GetStyle();
    ImVec2 PreviousTouchPadding = Style.TouchExtraPadding;
    Style.TouchExtraPadding = ImVec2(4, 4);

    ImGui::BeginChild("##VirtualKeyboard", ImVec2(0.0f, KeyHeight * 5.0f + KeyGap * 4.0f + 20.0f), true,
                      ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse |
                      ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowFontScale(2.1f);

    // Row 1: ` 1 2 3 4 5 6 7 8 9 0 - = [Backspace]
    //
    ImGui::SetCursorPosX(14.0f);
    DrawSymbolKey("`", "~");
    ImGui::SameLine();
    DrawSymbolKey("1", "!");
    ImGui::SameLine();
    DrawSymbolKey("2", "@");
    ImGui::SameLine();
    DrawSymbolKey("3", "#");
    ImGui::SameLine();
    DrawSymbolKey("4", "$");
    ImGui::SameLine();
    DrawSymbolKey("5", "%");
    ImGui::SameLine();
    DrawSymbolKey("6", "^");
    ImGui::SameLine();
    DrawSymbolKey("7", "&");
    ImGui::SameLine();
    DrawSymbolKey("8", "*");
    ImGui::SameLine();
    DrawSymbolKey("9", "(");
    ImGui::SameLine();
    DrawSymbolKey("0", ")");
    ImGui::SameLine();
    DrawSymbolKey("-", "_");
    ImGui::SameLine();
    DrawSymbolKey("=", "+");
    ImGui::SameLine();
    DrawSpecialKey("Backspace", 2.5f, [&]() {
        OnSpecialKey(VirtualKeyboardSpecialKey::BACKAPACE);
    });

    // Row 2: [Tab] q w e r t y u i o p [ ] \
    //
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);
    ImGui::SetCursorPosX(45.0f);
    DrawSpecialKey("Tab", 1.5f, [&]() {
		OnSpecialKey(VirtualKeyboardSpecialKey::TAB);
    });
    ImGui::SameLine();
    for (const char* CurrentCharacter = "qwertyuiop"; *CurrentCharacter; CurrentCharacter++)
    {
        DrawCharacterKey(*CurrentCharacter);
        if (CurrentCharacter[1])
            ImGui::SameLine();
    }
    ImGui::SameLine();
    DrawSymbolKey("[", "{");
    ImGui::SameLine();
    DrawSymbolKey("]", "}");
    ImGui::SameLine();
    DrawSymbolKey("\\", "|");

    // Row 3: [Caps] a s d f g h j k l ; ' [Enter]
    //
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);
    ImGui::SetCursorPosX(28.0f);
    DrawSpecialKey(CurrentVirtualKeyboardState.bIsCapsLockActive ? "Caps [ON]" : "Caps", 2.2f, [&]() { CurrentVirtualKeyboardState.bIsCapsLockActive = !CurrentVirtualKeyboardState.bIsCapsLockActive; });
    ImGui::SameLine();
    for (const char* CurrentCharacter = "asdfghjkl"; *CurrentCharacter; CurrentCharacter++)
    {
        DrawCharacterKey(*CurrentCharacter);
        if (CurrentCharacter[1])
            ImGui::SameLine();
    }
    ImGui::SameLine();
    DrawSymbolKey(";", ":");
    ImGui::SameLine();
    DrawSymbolKey("'", "\"");
    ImGui::SameLine();
    DrawSpecialKey("Enter", 2.0f, [&]() {
		OnSpecialKey(VirtualKeyboardSpecialKey::ENTER);
    });
    
    // Row 4: [Shift] z x c v b n m , . / [Shift]
    //
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);
    ImGui::SetCursorPosX(28.0f);
    DrawSpecialKey(CurrentVirtualKeyboardState.bIsShiftActive ? "Shift [ON]##Left" : "Shift##Left", 2.6f, [&]() { CurrentVirtualKeyboardState.bIsShiftActive = !CurrentVirtualKeyboardState.bIsShiftActive; });
    ImGui::SameLine();
    for (const char* CurrentCharacter = "zxcvbnm"; *CurrentCharacter; CurrentCharacter++)
    {
        DrawCharacterKey(*CurrentCharacter);
        if (CurrentCharacter[1])
            ImGui::SameLine();
    }
    ImGui::SameLine();
    DrawSymbolKey(",", "<");
    ImGui::SameLine();
    DrawSymbolKey(".", ">");
    ImGui::SameLine();
    DrawSymbolKey("/", "?");
    ImGui::SameLine();
    DrawSpecialKey(CurrentVirtualKeyboardState.bIsShiftActive ? "Shift [ON]" : "Shift", 2.6f, [&]() { CurrentVirtualKeyboardState.bIsShiftActive = !CurrentVirtualKeyboardState.bIsShiftActive; });
    
	// Getting available width for centering the space key row before drawing close button.
    float AvailableRowWidth = ImGui::GetContentRegionAvail().x;
    
    // Row 5.0: [Close]
    //
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);
	ImGui::SetCursorPosX(14.0f);
	DrawSpecialKey("Close", 2.0f, [&]() { bShouldRender = false; });

    // Row 5.1: [Space]
    //
    ImGui::SameLine();
    
    float SpaceKeyWidth = KeyWidth * 6.0f;
    float LeftPaddingForSpaceKey = (AvailableRowWidth - SpaceKeyWidth) * 0.5f;

    if (LeftPaddingForSpaceKey > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + LeftPaddingForSpaceKey);

    DrawSpecialKey("Space", 6.0f, [&]() {
		OnCharacterInput(' ');
    });
    
    ImGui::EndChild();
    Style.TouchExtraPadding = PreviousTouchPadding;

    ImGui::End();
}

void ImGuiVirtualKeyboard::AddOnCharacterInputCallback(std::function<void(char)> Callback)
{ 
    OnCharacterInputCallbacks.push_back(Callback);
}

void ImGuiVirtualKeyboard::ClearOnCharacterInputCallbacks()
{ 
    OnCharacterInputCallbacks.clear();
}

void ImGuiVirtualKeyboard::AddOnSpecialKeyCallback(std::function<void(VirtualKeyboardSpecialKey)> Callback)
{ 
    OnSpecialKeyCallbacks.push_back(Callback);
}

void ImGuiVirtualKeyboard::ClearOnSpecialKeyCallbacks()
{ 
    OnSpecialKeyCallbacks.clear();
}

void ImGuiVirtualKeyboard::OnCharacterInput(char Character)
{
    for (size_t i = 0; i < OnCharacterInputCallbacks.size(); i++)
    {
        if (OnCharacterInputCallbacks[i] != nullptr)
            OnCharacterInputCallbacks[i](Character);
    }
}

void ImGuiVirtualKeyboard::OnSpecialKey(VirtualKeyboardSpecialKey Key)
{
    for (size_t i = 0; i < OnSpecialKeyCallbacks.size(); i++)
    {
        if (OnSpecialKeyCallbacks[i] != nullptr)
            OnSpecialKeyCallbacks[i](Key);
	}
}

bool ImGuiVirtualKeyboard::ShouldBeRendered() const
{
    return bShouldRender;
}

void ImGuiVirtualKeyboard::SetShouldBeRendered(bool bNewValue)
{
    bShouldRender = bNewValue;
}