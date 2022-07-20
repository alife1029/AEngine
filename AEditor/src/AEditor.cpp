#include "AEditor.hpp"

using namespace aengine;

AEditor::AEditor(const AppConfig& config) : Application(config) { }

void AEditor::Start()
{
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void AEditor::Update()
{
    ImGui::ShowDemoWindow();
}

void AEditor::Dispose()
{
    
}
