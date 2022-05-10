#pragma once
#include "imgui/imgui.h"
#include <iostream>

class Button {
private:
	bool isClicked;
public:
	enum class Type{MAINMENU, CIRCLE};
	Type buttonType;

	// Constructor
	Button() {}

	Button(const char* name, Type type) {
		if (type == Type::MAINMENU) {
			buttonType = Type::MAINMENU;
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ ImColor{139, 129, 119, 255} });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ ImColor{100, 93, 85, 255} });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ ImColor{69, 63, 57, 255} });
			isClicked = ImGui::Button(name, ImVec2(200, 50));
		}
		else if (type == Type::CIRCLE) {
			buttonType = Type::CIRCLE;
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50);
			isClicked = ImGui::Button(name, ImVec2(100, 100));
		}
	}

	~Button() {
		if (buttonType == Type::MAINMENU) {
			ImGui::PopStyleVar();
			ImGui::PopStyleColor(3);
		}
		else ImGui::PopStyleVar();
	}

	operator bool()const {
		return isClicked;
	}
};