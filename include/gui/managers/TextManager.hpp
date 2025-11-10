#ifndef _TEXTMANAGER_HPP_
    #define _TEXTMANAGER_HPP_

    #include <string>
    #include <unordered_map>
    #include <exception>
    #include "raylib.h"

class TextManager
{
    public:
        /**
         * @brief Loads a font from the given file path.
         * 
         * @param fontPath Path to the font file.
         * @param baseSize Unused font size parameter.
         * @throws TextManagerException If the font cannot be loaded.
         */
        TextManager(const std::string &fontPath, int baseSize);
        /**
         * @brief Unloads the font and clears all translations.
         */
        ~TextManager();
        /**
         * @brief Loads translations from a language file.
         * 
         * @param langCode Language code.
         * @throws TextManagerException If the language file cannot be opened.
         */
        void loadLanguage(const std::string &langCode);
        /**
         * @brief Returns the translated text for a given key.
         * 
         * @param key Translation key.
         * @return Translated string if found, otherwise returns the key.
         */
        const std::string &getText(const std::string &key) const;
        /**
         * @brief Clears all loaded translations.
         */
        void clear();
        /**
         * @brief Draws the translated text for a key at a given position with shadow and tint.
         * 
         * @param key Translation key.
         * @param position Text position.
         * @param fontSize Size of the text.
         * @param tint Color tint.
         */
        void drawCode(const std::string &key, Vector2 position,
            float fontSize, const std::string &optionnalText = "", Color tint = WHITE) const;
        /**
         * @brief Draws the given text at a given position with shadow and tint.
         * 
         * @param text Text to draw.
         * @param position Text position.
         * @param fontSize Size of the text.
         * @param tint Color tint.
         */
        void drawText(const std::string &text, Vector2 position,
            float fontSize, Color tint = WHITE) const;
        class TextManagerException : public std::exception {
            public:
                explicit TextManagerException(const std::string &message)
                : _message("[TEXTMANAGER] " + message)
                {}
                ~TextManagerException() override = default;
                const char *what() const noexcept override
                {
                    return _message.c_str();
                }
            private:
                std::string _message;
        };
    private:
        Font font;
        std::unordered_map<std::string, std::string> translations;
        /**
         * @brief Removes leading and trailing whitespace from a string.
         * 
         * @param s String to trim.
         */
        static void trim(std::string &s);
        const int SPACING = 1;
};

#endif
