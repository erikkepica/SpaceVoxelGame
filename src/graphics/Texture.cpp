#include"Texture.h"
#include<string>
#include<map>

Texture::Texture()
{
}
Texture::Texture(std::string path)
{
    Generate(path);
}
void Texture::Generate(std::string path)
{
    memcpy(PathBuff, path.c_str(), path.size());
    stbi_set_flip_vertically_on_load(true);

    GL_CALL_DEBUG(glGenTextures(1, &m_ID));
    GL_CALL_DEBUG_ERR(glBindTexture(GL_TEXTURE_2D, m_ID)); 

    GL_CALL_DEBUG_ERR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL_DEBUG_ERR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CALL_DEBUG_ERR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CALL_DEBUG_ERR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);
    if (data)
    {
        GL_CALL_DEBUG(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
        GL_CALL_DEBUG_ERR(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else
    {
        LOG_WARNING("TEXTURE: Failed to load texture: " << path);
    }
    stbi_image_free(data);
}

void Texture::Bind(unsigned int slot)
{
    GL_CALL_DEBUG(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CALL_DEBUG_ERR(glBindTexture(GL_TEXTURE_2D, m_ID));
}