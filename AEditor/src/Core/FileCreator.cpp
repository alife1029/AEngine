#include "FileCreator.hpp"
#include <fstream>

std::string FileCreator::CreateNativeCppFile(const std::string& directory, const std::string& title)
{
    std::string fileName = directory + "/" + title + ".cpp";

    std::ofstream ofs(fileName);
    ofs << "#include <AEngine.hpp>" << std::endl
        << "\nclass " << title << "\n{\n\n};" << std::endl;
    ofs.close();

    return fileName;
}
