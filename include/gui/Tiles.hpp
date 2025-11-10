/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Tiles
*/

#ifndef _TILES_HPP_
    #define _TILES_HPP_

#include "managers/TextureManager.hpp"

enum class TileCategory
{
    Walls,
    Grounds,
    Water
};

enum class TileType
{
    Walls_After,
    Walls_After_Alt1,
    Walls_After_Alt2,
    Walls_Left,
    Walls_Right,
    Walls_Bottom,
    Walls_Top,
    Walls_TopLeftInter,
    Walls_TopRightInter,
    Walls_BottomLeftInter,
    Walls_BottomRightInter,
    Walls_TopLeftExter,
    Walls_TopRightExter,
    Walls_BottomLeftExter,
    Walls_BottomRightExter,
    Grounds_Simple,
    Grounds_Left,
    Grounds_Right,
    Grounds_Bottom,
    Grounds_Top,
    Grounds_TopLeft,
    Grounds_TopRight,
    Grounds_BottomLeft,
    Grounds_BottomRight,
    Grounds_Alt1,
    Grounds_Alt2,
    Grounds_Alt3,
    Water_TurnRightBottom,
    Water_TurnRightTop,
    Water_TurnLeftTop,
    Water_TurnLeftBottom,
    Water_Horizontal,
    Water_Vertical,
    Water_EndTop,
    Water_EndBottom,
    Water_EndRight,
    Water_EndLeft,
    Water_CrossRoads
};

class Tiles
{
    public:
        Tiles(const std::string &themeFile,
            std::shared_ptr<TextureManager> textureManager)
        {
            _textureByCategory[TileCategory::Walls]         = textureManager->getTexture(themeFile + "/Walls.png");
            _textureByCategory[TileCategory::Grounds]       = textureManager->getTexture(themeFile + "/Grounds.png");
            _textureByCategory[TileCategory::Water]         = textureManager->getTexture(themeFile + "/Water.png");
            _rectByTile[TileType::Walls_After]              = { 0.f,   0.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_After_Alt1]         = {24.f,   0.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_After_Alt2]         = {48.f,   0.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_Left]               = {48.f,  96.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_Right]              = { 0.f,  96.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_Bottom]             = {24.f,  72.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_Top]                = {24.f, 120.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_TopLeftInter]       = { 0.f,  24.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_TopRightInter]      = {24.f,  24.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_BottomLeftInter]    = { 0.f,  48.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_BottomRightInter]   = {24.f,  48.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_TopLeftExter]       = { 0.f,  72.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_TopRightExter]      = {48.f,  72.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_BottomLeftExter]    = { 0.f, 120.f,   24.f, 24.f};
            _rectByTile[TileType::Walls_BottomRightExter]   = {48.f, 120.f,   24.f, 24.f};
            _rectByTile[TileType::Grounds_Simple]           = {24.f,  24.f,   24.f, 24.f};
            _rectByTile[TileType::Grounds_Left]             = { 0.f,  24.f,   24.f, 24.f};
            _rectByTile[TileType::Grounds_Right]            = {48.f,  24.f,   24.f, 24.f};
            _rectByTile[TileType::Grounds_Bottom]           = {24.f,  48.f,   24.f, 24.f};
            _rectByTile[TileType::Grounds_Top]              = {24.f,   0.f,   24.f, 24.f};
            _rectByTile[TileType::Grounds_TopLeft]          = { 0.f,   0.f,   24.f, 24.f};
            _rectByTile[TileType::Grounds_TopRight]         = {48.f,   0.f,   24.f, 24.f};
            _rectByTile[TileType::Grounds_BottomLeft]       = { 0.f,  48.f,   24.f, 24.f};
            _rectByTile[TileType::Grounds_BottomRight]      = {48.f,  48.f,   24.f, 24.f};
            _rectByTile[TileType::Grounds_Alt1]             = {48.f,  96.f,   24.f, 24.f};
            _rectByTile[TileType::Grounds_Alt2]             = {24.f,  120.f,  24.f, 24.f};
            _rectByTile[TileType::Water_TurnRightBottom]    = { 0.f,   0.f,   24.f, 24.f};
            _rectByTile[TileType::Water_TurnLeftBottom]     = {48.f,   0.f,   24.f, 24.f};
            _rectByTile[TileType::Water_TurnRightTop]       = { 0.f,  48.f,   24.f, 24.f};
            _rectByTile[TileType::Water_TurnLeftTop]        = { 0.f,   0.f,   24.f, 24.f};
            _rectByTile[TileType::Water_Horizontal]         = { 0.f,  24.f,   24.f, 24.f};
            _rectByTile[TileType::Water_Vertical]           = {24.f,   0.f,   24.f, 24.f};
            _rectByTile[TileType::Water_EndBottom]          = {24.f,  72.f,   24.f, 24.f};
            _rectByTile[TileType::Water_EndTop]             = {24.f, 120.f,   24.f, 24.f};
            _rectByTile[TileType::Water_EndRight]           = { 0.f,  96.f,   24.f, 24.f};
            _rectByTile[TileType::Water_EndLeft]            = {48.f,  96.f,   24.f, 24.f};
            _rectByTile[TileType::Water_CrossRoads]         = {24.f,  96.f,   24.f, 24.f};
        }
        bool has(TileType t) const
        {
            return (_rectByTile.find(t) != _rectByTile.end());
        }
        Texture2D &getTexture(TileCategory category) const
        {
            return const_cast<Texture2D &>(_textureByCategory.at(category));
        }
        const Rectangle &getRect(TileType t) const
        {
            return _rectByTile.at(t);
        }

    private:
        std::unordered_map<TileCategory, Texture2D> _textureByCategory;
        std::unordered_map<TileType, Rectangle> _rectByTile;
};

#endif
