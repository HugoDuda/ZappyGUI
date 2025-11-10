/*
** EPITECH PROJECT, 2025
** *
** File description:
** GameScene
*/

#ifndef _GAME_SCENE_HPP_
    #define _GAME_SCENE_HPP_

    #include <functional>

    #include "network/Socket.hpp"
    #include "scenes/AScene.hpp"
    #include "HUD.hpp"
    #include "Tiles.hpp"
    #include "entities/Pokemon.hpp"
    #include "entities/Item.hpp"
    #include "managers/SoundManager.hpp"
    #include "scenes/SceneManager.hpp"
    #include "network/GameModel.hpp"

class GameScene;

class Commands
{
    public:
        static void msz(GameScene& gm, std::string params);

        static void sgt(GameScene& gm, std::string params);
        static void sst(GameScene& gm, std::string params);
        static void seg(GameScene& gm, std::string params);

        static void bct(GameScene& gm, std::string params);
        static void tna(GameScene& gm, std::string params);

        static void enw(GameScene& gm, std::string params);
        static void ebo(GameScene& gm, std::string params);
        static void edi(GameScene& gm, std::string params);

        static void pnw(GameScene& gm, std::string params);
        static void ppo(GameScene& gm, std::string params);
        static void plv(GameScene& gm, std::string params);
        static void pin(GameScene& gm, std::string params);
        static void pex(GameScene& gm, std::string params);
        static void pbc(GameScene& gm, std::string params);
        static void pic(GameScene& gm, std::string params);
        static void pie(GameScene& gm, std::string params);
        static void pfk(GameScene& gm, std::string params);
        static void pdr(GameScene& gm, std::string params);
        static void pgt(GameScene& gm, std::string params);
        static void pdi(GameScene& gm, std::string params);

        class ParamsException : public std::exception {
        public:
            explicit ParamsException(const std::string& msg)
            : _msg("[COMMAND]: " + msg) {}
            const char *what() const noexcept override
            {
                return _msg.c_str();
            }
        private:
            std::string _msg;
        };
};

class GameScene : public AScene
{
    public:
        GameScene(std::shared_ptr<TextureManager> textureManager,
            std::shared_ptr<TextManager> _textManager, int screenWidth,
            int screenHeight, std::shared_ptr<SoundManager> soundManager,
            int port, const std::string &host, settings_t *settings);
        ~GameScene() = default;
        /**
         * @brief Updates game logic, handles server communication and renders the scene.
         *
         * @param dt Delta time since last frame.
         * @throws ASceneException If the server is disconnected.
         */
        void update(float dt) override;
        void displayMap();
        void displayGrid();
        SceneType handleInput(float dt) override;
        SceneType getType() const override
        {
            return SceneType::GAMEPLAY;
        }
        float convertPositionX(float playerPositionX)
        {
            return playerPositionX * tileSize + offsetX + (afterWallsThickness * tileSize) + tileSize;
        }
        float convertPositionY(float playerPositionY)
        {
            return playerPositionY * tileSize + offsetY + (afterWallsThickness * tileSize) + tileSize;
        }
        void setLoading(bool state) {isLoadedCompletely = state; };
        void setMapWidth(int newMWidth) { mapWidth = newMWidth; };
        void setMapHeight(int newMHeight) { mapHeight = newMHeight; };
        void init_values();
        int getFrequency() { return _timer; };
        std::shared_ptr<TextureManager> getTextureManager()
        {
            return AScene::_textureManager;
        }
        void setFrequency(int timer)
        {
            _timer = timer;
            _tempTimer = timer;
        }
        std::shared_ptr<GameModel> getGameModel() { return _gameModel; };
        void setTileContent
        (int x, int y, int food, int line, int derau, int sib, int mend, int phir, int thyst)
        {
            _itemManager.clear({convertPositionX(x), convertPositionY(y)});
            for (int i = 0; i < food; i++) {
                _itemManager.addItem(ItemsList::Food, {convertPositionX(x), convertPositionY(y)});
            }
            for (int i = 0; i < line; i++) {
                _itemManager.addItem(ItemsList::Linemate, {convertPositionX(x), convertPositionY(y)});
            }
            for (int i = 0; i < derau; i++) {
                _itemManager.addItem(ItemsList::Deraumere, {convertPositionX(x), convertPositionY(y)});
            }
            for (int i = 0; i < sib; i++) {
                _itemManager.addItem(ItemsList::Sibur, {convertPositionX(x), convertPositionY(y)});
            }
            for (int i = 0; i < mend; i++) {
                _itemManager.addItem(ItemsList::Mendiane, {convertPositionX(x), convertPositionY(y)});
            }
            for (int i = 0; i < phir; i++) {
                _itemManager.addItem(ItemsList::Phiras, {convertPositionX(x), convertPositionY(y)});
            }
            for (int i = 0; i < thyst; i++) {
                _itemManager.addItem(ItemsList::Thystame, {convertPositionX(x), convertPositionY(y)});
            }
        }
        void addBrodcast(int pid, std::string message)
        {
            _hud.addBrodcast(pid, message);
        }
        std::unique_ptr<SocketClass>& getSocket() { return _socket; };
        void end(std::string team_name)
        {
            this->GameEnded = team_name;
        }
    private:
        /**
         * @brief Draws the game map, items, and all game entities.
         */
        void draw() override;
        void parseInformations(std::string& buf);
        void setupInitialInformations();
        void parseCommand(std::string cmdline, std::string line);
        void HUDHandling();
        std::unique_ptr<SocketClass> _socket;
        CameraScene camera;
        HUD _hud;
        Tiles _tiles;
        int mapWidth = 0;
        int mapHeight = 0;
        const float tileSize = 24.0f;
        const int afterWallsThickness = 30;
        bool isMapGenerated = false;
        int lastMapWidth = -1;
        int lastMapHeight = -1;
        std::vector<std::vector<TileType>> afterWallsMap;
        std::vector<std::vector<TileType>> groundsMap;
        int totalWidth;
        int totalHeight;
        float offsetX;
        float offsetY;
        int wallStartX;
        int wallStartY;
        int wallEndX;
        int wallEndY;
        std::unique_ptr<Item> item;
        PokemonManager _pokemonManager;
        std::shared_ptr<GameModel> _gameModel;
        std::shared_ptr<SoundManager> _soundManager;
        Music _themeMusic;
        bool _isResources = true;
        settings_t *_settings;
        ItemsManager _itemManager;
        bool isLoadedCompletely = true;
        int _timer;
        std::string _broadcast = "";
        int playerSpectateIndex = 0;
        bool spectate = false;
        bool _toggleItem = true;
        bool _toggleGrid = false;
        int _tempTimer;
        float _elapsedTimeFreq = 0.f;
        std::string GameEnded = "";

        static inline const std::unordered_map<
            std::string,
            std::function<void (GameScene& gm, std::string params)>
        > COMMAND_MAP = {
            {"msz", [] (GameScene& gm, std::string params) { Commands::msz(gm, params); } },

            {"sgt", [] (GameScene& gm, std::string params) { Commands::sgt(gm, params); } },

            {"bct", [] (GameScene& gm, std::string params) { Commands::bct(gm, params); } },
            {"tna", [] (GameScene& gm, std::string params) { Commands::tna(gm, params); } },

            {"enw", [] (GameScene& gm, std::string params) { Commands::enw(gm, params); } },
            {"ebo", [] (GameScene& gm, std::string params) { Commands::ebo(gm, params); } },
            {"edi", [] (GameScene& gm, std::string params) { Commands::edi(gm, params); } },

            {"pnw", [] (GameScene& gm, std::string params) { Commands::pnw(gm, params); } },
            {"ppo", [] (GameScene& gm, std::string params) { Commands::ppo(gm, params); } },
            {"plv", [] (GameScene& gm, std::string params) { Commands::plv(gm, params); } },
            {"pin", [] (GameScene& gm, std::string params) { Commands::pin(gm, params); } },
            {"pex", [] (GameScene& gm, std::string params) { Commands::pex(gm, params); } },
            {"pbc", [] (GameScene& gm, std::string params) { Commands::pbc(gm, params); } },
            {"pic", [] (GameScene& gm, std::string params) { Commands::pic(gm, params); } },
            {"pie", [] (GameScene& gm, std::string params) { Commands::pie(gm, params); } },
            {"pfk", [] (GameScene& gm, std::string params) { Commands::pfk(gm, params); } },
            {"pdr", [] (GameScene& gm, std::string params) { Commands::pdr(gm, params); } },
            {"pgt", [] (GameScene& gm, std::string params) { Commands::pgt(gm, params); } },
            {"pdi", [] (GameScene& gm, std::string params) { Commands::pdi(gm, params); } },

            {"seg", [] (GameScene& gm, std::string params) { Commands::seg(gm, params); } },

            // ignored Commands
            {"ok", [] (GameScene&, std::string) { return; } },
            {"smg", [] (GameScene&, std::string) { return; } },
            {"suc", [] (GameScene&, std::string) { return; } },
            {"sbp", [] (GameScene&, std::string) { return; } },
        };
};

#endif // !_GAME_SCENE_HPP_
