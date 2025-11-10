/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** displayMap
*/

#include "scenes/GameScene.hpp"

void GameScene::displayGrid()
{
    const float left = offsetX - tileSize / 2.0f;
    const float top = offsetY - tileSize / 2.0f;
    float x = 0;
    float y = 0;

    for (int i = 0; i <= totalWidth; ++i) {
        x = left + i * tileSize;
        DrawLineEx({x, top}, {x, top  + totalHeight * tileSize}, 1.0f, BLACK);
    }
    for (int j = 0; j <= totalHeight; ++j) {
        y = top + j * tileSize;
        DrawLineEx({left, y}, {left + totalWidth  * tileSize, y}, 1.0f, BLACK);
    }
}

void GameScene::displayMap()
{  
    int randomValue = 0;

    auto drawTile = [&](int x, int y, TileCategory category, TileType type) {
        DrawTexturePro(_tiles.getTexture(category),
        _tiles.getRect(type), {x * tileSize + offsetX - tileSize / 2.0f,
        y * tileSize + offsetY - tileSize / 2.0f, tileSize, tileSize},
        { 0.0f, 0.0f }, 0.0f, WHITE);
    };

    if (!isMapGenerated || lastMapWidth != mapWidth || lastMapHeight != mapHeight) {
        lastMapWidth = mapWidth;
        lastMapHeight = mapHeight;
        afterWallsMap.clear();
        afterWallsMap.resize(totalWidth, std::vector<TileType>(totalHeight));
        for (int x = 0; x < totalWidth; ++x) {
            for (int y = 0; y < totalHeight; ++y) {
                if (x < afterWallsThickness || x >= totalWidth - afterWallsThickness ||
                    y < afterWallsThickness || y >= totalHeight - afterWallsThickness) {
                    randomValue = rand() % 10;
                    afterWallsMap[x][y] = (randomValue < 6) ?
                    TileType::Walls_After : (randomValue < 8) ?
                    TileType::Walls_After_Alt1 : TileType::Walls_After_Alt2;
                }
            }
        }
        groundsMap.clear();
        groundsMap.resize(mapWidth, std::vector<TileType>(mapHeight));
        for (int x = 0; x < mapWidth; ++x) {
            for (int y = 0; y < mapHeight; ++y) {
                randomValue = rand() % 10;
                groundsMap[x][y] = (randomValue < 8) ? TileType::Grounds_Simple :
                (randomValue < 9) ? TileType::Grounds_Alt1 : TileType::Grounds_Alt2;
            }
        }
        isMapGenerated = true;
    }
    for (int x = 0; x < totalWidth; ++x) {
        for (int y = 0; y < totalHeight; ++y) {
            if (x < afterWallsThickness || x >= totalWidth - afterWallsThickness ||
                y < afterWallsThickness || y >= totalHeight - afterWallsThickness) {
                drawTile(x, y, TileCategory::Walls, afterWallsMap[x][y]);
            }
        }
    }
    for (int x = wallStartX; x <= wallEndX; ++x) {
        for (int y = wallStartY; y <= wallEndY; ++y) {
            if (x == wallStartX || x == wallEndX || y == wallStartY || y == wallEndY) {
                TileType wallType = TileType::Walls_Top;
                if (x == wallStartX && y == wallStartY) {
                    wallType = TileType::Walls_TopLeftInter;
                } else if (x == wallEndX && y == wallStartY) {
                    wallType = TileType::Walls_TopRightInter;
                } else if (x == wallStartX && y == wallEndY) {
                    wallType = TileType::Walls_BottomLeftInter;
                } else if (x == wallEndX && y == wallEndY) {
                    wallType = TileType::Walls_BottomRightInter;
                } else if (y == wallStartY) {
                    wallType = TileType::Walls_Top;
                } else if (y == wallEndY) {
                    wallType = TileType::Walls_Bottom;
                } else if (x == wallStartX) {
                    wallType = TileType::Walls_Left;
                } else if (x == wallEndX) {
                    wallType = TileType::Walls_Right;
                }
                drawTile(x, y, TileCategory::Walls, wallType);
            }
        }
    }
    for (int x = 0; x < mapWidth; ++x) {
        for (int y = 0; y < mapHeight; ++y) {
            if (x == 0 && y == 0) {
                drawTile(wallStartX + 1 + x, wallStartY + 1 + y, TileCategory::Grounds, TileType::Grounds_TopLeft);
            } else if (x == 0 && y == mapHeight - 1) {
                drawTile(wallStartX + 1 + x, wallStartY + 1 + y, TileCategory::Grounds, TileType::Grounds_BottomLeft);
            } else if (x == mapWidth - 1 && y == 0) {
                drawTile(wallStartX + 1 + x, wallStartY + 1 + y, TileCategory::Grounds, TileType::Grounds_TopRight);
            } else if (x == mapWidth - 1 && y == mapHeight - 1) {
                drawTile(wallStartX + 1 + x, wallStartY + 1 + y, TileCategory::Grounds, TileType::Grounds_BottomRight);
            } else if (x == 0) {
                drawTile(wallStartX + 1 + x, wallStartY + 1 + y, TileCategory::Grounds, TileType::Grounds_Left);
            } else if (y == 0) {
                drawTile(wallStartX + 1 + x, wallStartY + 1 + y, TileCategory::Grounds, TileType::Grounds_Top);
            } else if (y == mapHeight - 1) {
                drawTile(wallStartX + 1 + x, wallStartY + 1 + y, TileCategory::Grounds, TileType::Grounds_Bottom);
            } else if (x == mapWidth - 1) {
                drawTile(wallStartX + 1 + x, wallStartY + 1 + y, TileCategory::Grounds, TileType::Grounds_Right);
            } else {
                drawTile(wallStartX + 1 + x, wallStartY + 1 + y, TileCategory::Grounds, groundsMap[x][y]);
            }
        }
    }
    if (_toggleGrid) {
        displayGrid();
    }
}
