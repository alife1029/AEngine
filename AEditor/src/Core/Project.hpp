#ifndef AED_PROJECT_HPP
#define AED_PROJECT_HPP

#include <AEngine.hpp>

using namespace aengine;

// TODO: Create a project structure

class AEProject
{
    friend class CreateProjectMenu;
public:
    AEProject();
    AEProject(const std::string& projectFile);
    void Save();

    // Getters
    std::string ProjectName();
    std::string ProjectPath();
    std::string ProjectDirectory();

    // Setters
    void SetProjectName(const std::string& projName);
private:
    std::string mPath;

// Project properties
private:
    std::string mProjectName;
};

#endif
