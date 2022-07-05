// Win32 implementation of file dialogs
#include "AEngine/Application/FileDialogs.hpp"

#include <commdlg.h>
#include <direct.h>
#include <ShlObj.h>
#include <tchar.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace aengine
{
    std::string FileDialog::OpenFile(const char* filter)
    {
        OPENFILENAMEA ofn;      // common dialog box structure
        CHAR szFile[260] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
        ofn.lStructSize = sizeof(OPENFILENAMEA);
        ofn.hwndOwner = glfwGetWin32Window(window);
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&ofn) == TRUE)
        {
            return ofn.lpstrFile;
        }
        return std::string();
    }
    
    std::string FileDialog::SaveFile(const char* filter)
    {
        OPENFILENAMEA ofn;      // common dialog box structure
        CHAR szFile[260] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
        ofn.lStructSize = sizeof(OPENFILENAMEA);
        ofn.hwndOwner = glfwGetWin32Window(window);
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetSaveFileNameA(&ofn) == TRUE)
        {
            return ofn.lpstrFile;
        }
        return std::string();
    }

    std::string FileDialog::BrowseFolder()
    {
        TCHAR szBuffer[260] = { 0 };
        BROWSEINFO bi;
        ZeroMemory(&bi, sizeof(BROWSEINFO));
        bi.hwndOwner = glfwGetWin32Window(window);
        bi.pszDisplayName = szBuffer;
        bi.pidlRoot = NULL;
        bi.lpszTitle = _T("Select asset folder");
        bi.ulFlags = BIF_NEWDIALOGSTYLE;
        LPITEMIDLIST idl = SHBrowseForFolder(&bi);

        if (idl == NULL)
        {
            return "";
        }

        SHGetPathFromIDList(idl, szBuffer);
        return std::string(szBuffer);
    }
}
