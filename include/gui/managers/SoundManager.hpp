/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** SoundManager
*/

#ifndef _SOUND_MANAGER_HPP_
    #define _SOUND_MANAGER_HPP_

    #include <string>
    #include <unordered_map>
    #include <exception>
    #include "raylib.h"


class SoundManager
{
    public:
        SoundManager() = default;
        ~SoundManager()
        {
            unloadAll();
        }
        class SoundManagerException : public std::exception
        {
            public:
                explicit SoundManagerException(const std::string &message)
                : _message("[SOUNDMANAGER] " + message)
                {}
                const char *what() const noexcept override
                {
                    return _message.c_str();
                }
            private:
                std::string _message;
        };
        Sound &getSound(const std::string &path)
        {
            auto it = _sounds.find(path);

            if (it == _sounds.end()) {
                Sound sound = LoadSound(path.c_str());
                if (sound.frameCount == 0) {
                    throw SoundManagerException("Cannot load sound: " + path);
                }
                it = _sounds.emplace(path, sound).first;
            }
            return it->second;
        }
        Music &getMusic(const std::string &path)
        {
            auto it = _music.find(path);

            if (it == _music.end()) {
                Music m = LoadMusicStream(path.c_str());
                if (m.ctxData == nullptr) {
                    throw SoundManagerException("Cannot load music: " + path);
                }
                it = _music.emplace(path, m).first;
            }
            return it->second;
        }
        void unloadAll()
        {
            for (auto &kv : _sounds) {
                UnloadSound(kv.second);
            }
            for (auto &kv : _music) {
                UnloadMusicStream(kv.second);
            }
            _sounds.clear();
            _music.clear();
        }
        void unloadSound(const std::string &path)
        {
            auto it = _sounds.find(path);

            if (it != _sounds.end()) {
                UnloadSound(it->second);
                _sounds.erase(it);
            }
        }
        SoundManager(const SoundManager &) = delete;
        SoundManager &operator=(const SoundManager &) = delete;

    private:
        std::unordered_map<std::string, Sound> _sounds;
        std::unordered_map<std::string, Music> _music;
};

#endif
