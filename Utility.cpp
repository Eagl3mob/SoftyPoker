#include "Utility.h"

std::string getAssetPath(const std::string& relativePath) {
    // Adjust the base path as needed
    std::string basePath = "D:/Projects/softypoker/Assets/";
    return basePath + relativePath;
}
