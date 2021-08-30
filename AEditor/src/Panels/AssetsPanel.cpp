#include "AssetsPanel.hpp"
#include "../Utils.hpp"
#include <imgui.h>

void AssetsPanel::Start()
{
    // Load icons
    mFolderIcon = new Texture2D("Icons/folder.png");
    mFileIcon = new Texture2D("Icons/file.png");
    mCppIcon = new Texture2D("Icons/cpp.png");

    currentDirectory = rootDirectory;
}

void AssetsPanel::Render()
{
    ImGui::Begin("Assets");

    if (currentDirectory != rootDirectory)
    {
        if (ImGui::Button("<-"))
        {
            currentDirectory = currentDirectory.parent_path();
        }
    }

    static float padding = 16.0f;
    static float thumbnailSize = 64.0f;
    float cellSize = thumbnailSize + padding;
    
    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int)(panelWidth / cellSize);
    if (columnCount < 1) columnCount = 1;

    ImGui::Columns(columnCount, 0, false);

    for (auto& entry : std::filesystem::directory_iterator(currentDirectory)) 
    {
        // TODO: Support UTF-16 (wchar_t)

        std::string path = entry.path().string();
        std::string fileName = entry.path().filename().string();

        ImGui::PushID(path.c_str());

        // Set icon
        Texture2D* icon = entry.is_directory() ? mFolderIcon : mFileIcon;
        if (CheckFileExtension(path, "cpp")) icon = mCppIcon;

        ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.0f, 0.0f });
        ImGui::ImageButton((void*)(size_t)icon->ID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

        if (ImGui::BeginDragDropSource())
        {
            const char* itemPath = path.c_str();
            ImGui::SetDragDropPayload("ASSET_PANEL_ITEM", itemPath, path.size() * sizeof(char));
            ImGui::EndDragDropSource();
        }

        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            if (entry.is_directory())
            {
                currentDirectory /= fileName;
            }
            else 
            {
                // TODO: Open Files
            }
        }

        ImGui::TextWrapped(fileName.c_str());
        
        ImGui::NextColumn();
        ImGui::PopID();
    }

    ImGui::End();
}

void AssetsPanel::Dispose()
{
    // Delete icons
    delete mFolderIcon;
    delete mFileIcon;
    delete mCppIcon;
}
