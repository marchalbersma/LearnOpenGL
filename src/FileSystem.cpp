#include <FileSystem.hpp>
#include <string>

using namespace std;

string FileSystem::getResourcePath(string path)
{
    const string resourceDirectory = "resources/";

    path.insert(0, resourceDirectory);

    return path;
}
