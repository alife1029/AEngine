#include "AssetsPanel.hpp"
#include "../Utils.hpp"
#include "../Core/FileCreator.hpp"
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
    bool popupContextMenuOpened = false;

    ImGui::Begin("Assets");

    if (currentDirectory != rootDirectory)
    {
        if (ImGui::Button("<-"))
        {
            currentDirectory = currentDirectory.parent_path();
            EndFileRenaming();
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

        if (currentlyRenamingFile != fileName && isFileRenaming) ImGui::PushID(path.c_str());
        else ImGui::PushID("aeditor_currently_renaming_file_imgui_id");

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

        if (ImGui::IsItemHovered())
        {
            if (!isFileRenaming)
                selectionContext = path;

            if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                if (entry.is_directory())
                {
                    currentDirectory /= fileName;
                    EndFileRenaming();
                }
                else 
                {
                    // TODO: Open Files
                    EndFileRenaming();
                }
            }
        }

        if (selectionContext == path)
        if (ImGui::BeginPopupContextItem(path.c_str()))
        {
            popupContextMenuOpened = true;
            if (ImGui::MenuItem("Open"))
            {
                // TODO: Open file
            }
            if (ImGui::MenuItem("Delete"))
            {
                remove(currentDirectory / fileName);
            }
            if (ImGui::MenuItem("Rename"))
            {
                StartFileRenaming(fileName);
            }

            ImGui::EndPopup();
        }

        ImGui::TextWrapped(fileName.c_str());
        
        ImGui::NextColumn();
        ImGui::PopID();
    }

    if (!popupContextMenuOpened)
    if (ImGui::BeginPopupContextWindow()) 
    {
        if (ImGui::MenuItem("Create Folder"))
        {
            // TODO: Create Folder
        }
        if (ImGui::MenuItem("Create Scene"))
        {
            // TODO: Create Scene
        }
        if (ImGui::MenuItem("Create Native C++ Script"))
        {
            selectionContext = currentDirectory.string() + "\\" + "NativeScript.cpp";
            StartFileRenaming("NativeScript.cpp");
            FileCreator::CreateNativeCppFile(currentDirectory.generic_string(), "NativeScript");
        }

        ImGui::EndPopup();
    }
    popupContextMenuOpened = false;

    ImGui::End();

    if (isFileRenaming)
    {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_AlwaysAutoResize 
            | ImGuiWindowFlags_NoDocking 
            | ImGuiWindowFlags_NoTitleBar;

        ImGui::Begin("Rename File", nullptr, flags);

        ImGui::Text("File: %s", oldName.c_str());
        if (ImGui::InputText("New Name:", &currentlyRenamingFile, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            if (rename(selectionContext.c_str(), (currentDirectory.string() + "\\" + currentlyRenamingFile).c_str()) != 0)
            {
                oldName = currentlyRenamingFile;
                Logger::LogToFile("Failed to rename file!\t" + selectionContext, "Logs.log", LogType::Error);
            }
            else 
            {
                Logger::LogToFile("File successfully renamed!");
                isFileRenaming = false;
            }
        }

        if (Input::IsKeyJustPressed(Key::Escape))
            isFileRenaming = false;

        ImGui::End();
    }    
}

void AssetsPanel::StartFileRenaming(const std::string& file)
{
    isFileRenaming = true;
    oldName = file;
    currentlyRenamingFile = file;
}

void AssetsPanel::EndFileRenaming()
{
    isFileRenaming = false;
    oldName = "";
    currentlyRenamingFile = "";
}

void AssetsPanel::Dispose()
{
    // Delete icons
    delete mFolderIcon;
    delete mFileIcon;
    delete mCppIcon;
}
