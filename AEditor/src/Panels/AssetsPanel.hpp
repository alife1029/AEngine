#ifndef AED_ASSETS_PANEL_HPP
#define AED_ASSETS_PANEL_HPP

#include "Panel.hpp"
#include <AEngine.hpp>
#include <filesystem>

using namespace aengine;

class AssetsPanel : public Panel
{
public:
    std::filesystem::path rootDirectory;
private:
    Texture2D *mFolderIcon, *mFileIcon, *mCppIcon;
    std::filesystem::path currentDirectory;
public:
    void Start();
    void Render();
    void Dispose();
};

#endif
