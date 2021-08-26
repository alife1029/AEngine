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
    std::string filePath = mPath + "/" + mProjectName + ".aeproject";
    std::ofstream ofs(filePath);
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

void AEProject::SetProjectName(const std::string& projName)
{
    mProjectName = projName;
}
