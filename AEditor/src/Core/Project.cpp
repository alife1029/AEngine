#include "Project.hpp"

#include <fstream>

AEProject::AEProject() { }

AEProject::AEProject(const std::string& projectFile)
{
    mPath = projectFile;

    // Read project properties
    std::ifstream ifs(mPath);
    if (ifs.is_open())
    {
        ifs >> mProjectName;
    }
    ifs.close();
}

void AEProject::Save()
{
    std::ofstream ofs(mPath);
    if (ofs.is_open())
    {
        ofs << mProjectName;
    }
    ofs.close();
}

std::string AEProject::ProjectName()
{
    return mProjectName;
}
std::string AEProject::ProjectPath()
{
    return mPath;
}
std::string AEProject::ProjectDirectory()
{
    size_t lastSlashLoc = 0;
    for (size_t i = mPath.size() - 1; i >= 0; i--)
    {
        if (mPath[i] == '/' || mPath[i] == '\\')
        {
            lastSlashLoc = i;
            break;   
        }
    }
    return mPath.substr(0, lastSlashLoc);
}

void AEProject::SetProjectName(const std::string& projName)
{
    mProjectName = projName;
}
