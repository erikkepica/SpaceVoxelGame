#pragma once
#include"glad/glad.h"
#include"stb_image/stb_image.h"
#include"Logging.h"



class Texture
{
public:
    Texture();
    Texture(std::string path);

    void Generate(std::string path);

    void Bind(unsigned int slot = 0);

    char PathBuff[128]{ " " };

private:
    unsigned int m_ID;
};

