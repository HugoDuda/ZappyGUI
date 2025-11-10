/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** TextureManager
*/

#ifndef _TEXTURE_MANAGER_HPP_
    #define _TEXTURE_MANAGER_HPP_

    #include <string>
    #include <unordered_map>
    #include <memory>
    #include <exception>
    #include <sys/stat.h>

    #include "Camera.hpp"
    #include "managers/TextManager.hpp"

class TextureManager
{
    public:
        TextureManager() = default;
        ~TextureManager()
        {
            unloadAll();
            if (_hasPlaceholder && _placeholder.id != 0) {
                UnloadTexture(_placeholder);
            }
        }
        class TextureManagerException : public std::exception
        {
            public:
                explicit TextureManagerException(const std::string &message)
                :   _message("[TEXTUREMANAGER] " + message)
                {}
                ~TextureManagerException() override = default;
                const char *what() const noexcept override
                {
                    return _message.c_str();
                }
            private:
                std::string _message;
        };
        Texture2D &getTexture(const std::string &texturePath)
        {
            struct stat st {};
            Texture2D texture;

            if (stat(texturePath.c_str(), &st) != 0 || S_ISDIR(st.st_mode)) {
                return getPlaceholder();
            }
            auto it = textures.find(texturePath);
            if (it == textures.end()) {
                texture = LoadTexture(texturePath.c_str());
                if (texture.id == 0) {
                    return getPlaceholder();
                }
                it = textures.emplace(texturePath, texture).first;
            }
            return it->second;
        }
        void unloadAll()
        {
            for (auto &[texturePath, texture] : textures) {
                if (texture.id != 0) {
                    UnloadTexture(texture);
                }
            }
            textures.clear();
        }
        void resetPlaceholder()
        {
            if (_hasPlaceholder && _placeholder.id != 0) {
                UnloadTexture(_placeholder);
            }
            _hasPlaceholder = false;
        }
        TextureManager(const TextureManager &) = delete;
        TextureManager &operator=(const TextureManager &) = delete;
    private:
        Texture2D _placeholder;
        bool _hasPlaceholder = false;
        std::unordered_map<std::string, Texture2D> textures;
        Texture2D &getPlaceholder()
        {
            if (!_hasPlaceholder) {
                loadPlaceholder();
            }
            return _placeholder;
        }
        void loadPlaceholder()
        {
            Image img = GenImageColor(24, 24, (Color){200, 200, 200, 255});

            ImageDrawText(&img, "?",  6,  2, 20, BLACK);
            _placeholder = LoadTextureFromImage(img);
            UnloadImage(img);
            _hasPlaceholder = true;
        }
};

#endif
