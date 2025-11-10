/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Pokemon
*/

#ifndef _POKEMON_HPP_
    #define _POKEMON_HPP_

#include "parser/XMLParser.hpp"
#include "managers/TextureManager.hpp"
#include <map>
#include <array>

class Pokemon
{
    public:
        /**
         * @brief Construct a Pokémon and load its animations.
         * 
         * @param pokemonId Identifier of the Pokémon.
         * @param textureManager Shared pointer to the texture manager.
         */
        explicit Pokemon(int pokemonId, std::shared_ptr<TextureManager> textureManager);
        /**
         * @brief Destructor, unloads all cached shadow textures.
         */
        ~Pokemon()
        {
            for (auto &[key, tex] : shadowCache)
                UnloadTexture(tex);
        }
        class PokemonException : public std::exception
        {
            public:
                explicit PokemonException(const std::string &message)
                    : _message("[POKEMON] " + message)
                {}
                ~PokemonException() override = default;
                const char *what() const noexcept override
                {
                    return _message.c_str();
                }
            private:
                std::string _message;
        };
        /**
         * @brief Advance the animation timer.
         * 
         * @param dt Time delta since last update (seconds).
         */
        void update(float dt)
        {
            _timeAccumulator += dt;
        }
        /**
         * @brief Change the current animation type.
         * 
         * @param anim Animation type to set.
         */
        void setAnimation(animationType anim)
        {
            _currentAnim = anim;
        }
        /**
         * @brief Change the current animation direction.
         * 
         * @param dir Direction to set.
         */
        void setDirection(animationDirection dir)
        {
            _currentDir  = dir;
        }
        /**
         * @brief Draw the Pokémon with its current animation and optional shadow.
         * 
         * @param x X-coordinate on screen.
         * @param y Y-coordinate on screen.
         * @param shadowColor Color of the shadow.
         */
        void draw(float x, float y, Color shadowColor);
        /**
         * @brief Clone this Pokémon instance.
         * 
         * @return Unique pointer to the cloned Pokémon.
         */
        std::unique_ptr<Pokemon> clone() const;
        /**
         * @brief Convert animation type to its filename.
         * 
         * @param anim Animation type.
         * @return Filename string for the animation.
         */
        const std::string animationTypeToFilename(animationType anim) const;
        /**
         * @brief Convert animation type to its shadow filename.
         * 
         * @param anim Animation type.
         * @return Filename string for the shadow.
         */
        const std::string shadowToFilename(animationType anim) const;
        /**
         * @brief Get the Pokémon's identifier.
         * 
         * @return Pokémon ID.
         */
        int getId() const
        {
            return _id;
        }
        /**
         * @brief Format a Pokémon ID to find the folder in resources/pokemon_sprite/.
         * 
         * @param pokemonId ID to format.
         * @return Formatted ID string.
         */
        std::string formatPokemonId(int pokemonId) const
        {
            return (pokemonId < 10) ? "000" + std::to_string(pokemonId) :
            (pokemonId < 100) ? "00" + std::to_string(pokemonId) :
            "0" + std::to_string(pokemonId);
        }
        /**
         * @brief Generate a shadow texture from a source texture.
         * 
         * @param src Source texture.
         * @param color Color to apply to the shadow.
         * @param rect Rectangle region to process.
         * @return New shadow Texture2D.
         */
        Texture2D makeShadowTexture(const Texture2D &src, Color color, Rectangle rect);
        float getTextureHeight()
        {
            return textureHeight;
        }
    private:
        int _id;
        float _timeAccumulator = 0.f;
        std::shared_ptr<TextureManager> _textureManager;
        float textureHeight;
        animationType _currentAnim = animationType::Idle;
        animationDirection _currentDir  = animationDirection::South;
        std::unordered_map<animationDirection, std::unordered_map<animationType, std::vector<animationFrame_t>>> _animations;
        /**
         * @brief Convert a Color to an array of RGBA components.
         * 
         * @param c Reference to the Color.
         * @return std::array with { r, g, b, a }.
         */
        std::array<unsigned char, 4> colorToArray(const Color &c)
        {
            return { c.r, c.g, c.b, c.a };
        }
        /**
         * @brief Calculate the total duration of a sequence of animation frames.
         * 
         * @param frames Vector of animationFrame_t to sum.
         * @return Sum of all frame durations.
         */
        static float totalAnimationTime(const std::vector<animationFrame_t> &frames)
        {
            float sum = 0.f;

            for (auto &f : frames) {
                sum += f.duration;
            }
            return sum;
        }
        /**
         * @brief Key struct for caching rectangles.
         */
        typedef struct rectKey_s {
            int x = 0;
            int y = 0;
            int w = 0;
            int h = 0;
            /**
             * @brief Construct a rectKey from a Rectangle.
             * 
             * @param rectangle Source Rectangle.
             */
            rectKey_s(Rectangle rectangle)
            : x((int)rectangle.x), y((int)rectangle.y), w((int)rectangle.width), h((int)rectangle.height)
            {}
            /**
             * @brief Compare two rectKey_t for ordering.
             * 
             * @param other Other rectKey to compare.
             * @return True if this key is less than other.
             */
            bool operator<(const rectKey_s &other) const
            {
                return std::tie(x, y, w, h) < std::tie(other.x, other.y, other.w, other.h);
            }
        } rectKey_t;
        std::map<std::tuple<animationType, animationDirection, std::array<unsigned char, 4>, rectKey_t>, Texture2D> shadowCache;
};

class PokemonManager
{
    public:
        PokemonManager(std::shared_ptr<TextureManager> texMgr)
            : _textureManager(std::move(texMgr))
        {}
        class PokemonManagerException : public std::exception
        {
            public:
                explicit PokemonManagerException(const std::string &message)
                    : _message("[PokemonManager] " + message)
                {}
                ~PokemonManagerException() override = default;
                const char *what() const noexcept override
                {
                    return _message.c_str();
                }
            private:
                std::string _message;
        };
        /**
         * @brief Retrieve a Pokémon by its ID, loading it if necessary.
         * 
         * @param id ID of the Pokémon to get.
         * @return Reference to the requested Pokémon.
         * @throws PokemonManagerException If the Pokémon cannot be loaded.
         */
        Pokemon &getPokemon(int id);
        /**
         * @brief Check if a Pokémon exist by its ID.
         * 
         * @param id ID of the Pokémon to check.
         * @return True if exist, false if not.
        */
        bool hasPokemon(int id) const
        {
            return _pokemons.find(id) != _pokemons.end();
        }
        /**
         * @brief Get a list of all stored Pokémon IDs.
         * 
         * @return Vector containing every Pokémon ID in the manager.
         */
        std::vector<int> listIds() const;
        /**
         * @brief Create a new Pokémon instance by cloning an existing one.
         * 
         * @param id ID of the Pokémon to clone.
         * @return Unique pointer to the cloned Pokémon.
         */
        std::unique_ptr<Pokemon> createPokemon(int id);
    private:
        std::shared_ptr<TextureManager> _textureManager;
        std::unordered_map<int, std::unique_ptr<Pokemon>> _pokemons;
};

#endif
