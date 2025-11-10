/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Item
*/

#ifndef _ITEM_HPP_
    #define _ITEM_HPP_

    #include <unordered_map>
    #include <memory>
    #include <string>
    #include <list>

    #include "managers/TextureManager.hpp"

template<>
struct std::hash<Vector2>
{
    std::size_t operator()(const Vector2& v) const noexcept
    {
        std::size_t h1 = std::hash<float>{}(v.x);
        std::size_t h2 = std::hash<float>{}(v.y);
        return h1 ^ (h2 << 1);
    }
};

enum class ItemsList
{
    Food,
    Linemate,
    Deraumere,
    Sibur,
    Mendiane,
    Phiras,
    Thystame
};

class Item
{
    public:
        Item(ItemsList type, std::shared_ptr<TextureManager> textureManager)
        : _type(type)
        , _textureManager(std::move(textureManager))
        {
            std::string name = itemTypeToString(_type);
            std::string path = "resources/items/" + name + ".png";
    
            _texture = &_textureManager->getTexture(path);
        }

        ~Item() = default;

        ItemsList getType() const
        {
            return _type;
        }

        Texture2D &getTexture() const
        {
            return *_texture;
        }

        void draw(float x, float y, float scale = 0.9f, Color tint = WHITE) const
        {
            DrawTextureEx(*_texture, {x - _texture->width / 1.7f, y - _texture->height / 1.5f}, 0.0f, scale, tint);
        }

        static std::string itemTypeToString(ItemsList type)
        {
            switch (type)
            {
                case ItemsList::Food:      return "food";
                case ItemsList::Linemate:  return "linemate";
                case ItemsList::Deraumere: return "deraumere";
                case ItemsList::Sibur:     return "sibur";
                case ItemsList::Mendiane:  return "mendiane";
                case ItemsList::Phiras:    return "phiras";
                case ItemsList::Thystame:  return "thystame";
            }
            return "Unknown";
        }

    private:
        ItemsList _type;
        std::shared_ptr<TextureManager> _textureManager;
        Texture2D *_texture;
};

class ItemsManager
{
    public:
        explicit ItemsManager(std::shared_ptr<TextureManager> textureManager)
        : _textureManager(std::move(textureManager))
        {
            for (ItemsList t : {
                ItemsList::Food,
                ItemsList::Linemate,
                ItemsList::Deraumere,
                ItemsList::Sibur,
                ItemsList::Mendiane,
                ItemsList::Phiras,
                ItemsList::Thystame
            }) {
                _itemsSkin.emplace(t,
                    std::make_unique<Item>(t, _textureManager));
            }
        }

        ~ItemsManager() = default;

        Item &getItem(ItemsList type)
        {
            return *(_itemsSkin.at(type));
        }

        void addItem(ItemsList type, Vector2 position)
        {
            _items[position].push_back(std::make_pair(type, (Vector2){position.x - 7 + rand() % 14, position.y - 7 + rand() % 14}));
        }

        void drawAll()
        {
            for (auto list = _items.begin(); list != _items.end(); list++) {
                for (std::pair<ItemsList, Vector2> item : list->second) {
                    _itemsSkin.at(item.first)->draw(item.second.x, item.second.y);
                }
            }
        }

        void removeItem(Vector2 position);

        void clear(Vector2 position)
        {
            auto list = _items.find(position);

            if (list != _items.end())
                list->second.clear();
        }
    private:
        std::shared_ptr<TextureManager> _textureManager;
        std::unordered_map<ItemsList, std::unique_ptr<Item>> _itemsSkin;
        std::unordered_map<Vector2, std::list<std::pair<ItemsList, Vector2>>> _items;
};

#endif
