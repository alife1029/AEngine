#ifndef AED_ASSETS_PANEL_HPP
#define AED_ASSETS_PANEL_HPP

#include "Panel.hpp"
#include <AEngine.hpp>
#include <vector>
#include <filesystem>

using namespace aengine;

class AssetsPanel : public Panel
{
public:
    std::filesystem::path rootDirectory;
private:
    Texture2D *mFolderIcon, *mFileIcon, *mCppIcon;
    std::filesystem::path currentDirectory;
    std::string selectionContext = "";
    std::string currentlyRenamingFile = "";
    std::string oldName = "";
    bool isFileRenaming = false;
private:
    void StartFileRenaming(const std::string& file);
    void EndFileRenaming();
public:
    void Start();
    void Render();
    void Dispose();
};

#endif
