/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** parser
*/

#include "entities/Pokemon.hpp"
#include <fstream>
#include <iostream>

void XMLParser::findAnimationByIndex(std::string &line, const std::string &xmlPath, int animIndex,
    parsingContext_t &ctx)
{
    auto posTag = line.find("<Index>");
    size_t start = 0;
    size_t end = 0;

    if (posTag != std::string::npos) {
        start = line.find('>', posTag) + 1;
        end = line.find("</Index>", start);
        if (start == std::string::npos || end == std::string::npos)
            throw XMLParserException("Malformed <Index> tag in " + xmlPath);
        ctx.currentIndex = std::stoi(line.substr(start, end - start));
        ctx.foundTargetAnim = (ctx.currentIndex == animIndex);
        ctx.hasFrameWidth = false;
        ctx.hasFrameHeight = false;
    }
}

void XMLParser::parseFrameWidth(std::string &line, int animIndex, parsingContext_t &ctx)
{
    size_t start = 0;
    size_t end = 0;

    if (line.find("<FrameWidth>") != std::string::npos) {
        start = line.find(">") + 1;
        end = line.find("</FrameWidth>");
        if (start == std::string::npos || end == std::string::npos) {
            throw XMLParserException("Malformed FrameWidth tag for animation index "
            + std::to_string(animIndex));
        }
        ctx.frameWidth = std::stoi(line.substr(start, end - start));
        ctx.hasFrameWidth = true;
    }
}

void XMLParser::parseFrameHeight(std::string &line, int animIndex, parsingContext_t &ctx)
{
    if (line.find("<FrameHeight>") != std::string::npos) {
        size_t start = line.find(">") + 1;
        size_t end = line.find("</FrameHeight>");
        if (start == std::string::npos || end == std::string::npos) {
            throw XMLParserException("Malformed FrameHeight tag for animation index "
            + std::to_string(animIndex));
        }
        ctx.frameHeight = std::stoi(line.substr(start, end - start));
        ctx.hasFrameHeight = true;
    }
}

void XMLParser::parseDuration(std::string &line, int animIndex, parsingContext_t &ctx)
{
    size_t start = 0;
    size_t end = 0;

    if (line.find("<Duration>") != std::string::npos) {
        if (!ctx.hasFrameWidth || !ctx.hasFrameHeight) {
            throw XMLParserException("Missing FrameWidth or FrameHeight for animation index "
            + std::to_string(animIndex));
        }
        start = line.find(">") + 1;
        end = line.find("</Duration>");
        if (start == std::string::npos || end == std::string::npos) {
            throw XMLParserException("Malformed Duration tag for animation index "
            + std::to_string(animIndex));
        }
        ctx.frames.push_back({{
            static_cast<float>(ctx.frames.size() * ctx.frameWidth),
            static_cast<float>(ctx.direction) * ctx.frameHeight,
            static_cast<float>(ctx.frameWidth),
            static_cast<float>(ctx.frameHeight)
        }, std::stof(line.substr(start, end - start))});
    }
}

std::vector<animationFrame_t> XMLParser::parseFromXMLFile(const std::string &xmlPath,
    int animIndex, animationDirection direction)
{
    std::ifstream file(xmlPath);
    std::string line;
    parsingContext_t ctx;

    ctx.direction = direction;
    if (!file.is_open()) {
        ctx.frames.push_back({{
            static_cast<float>(0),
            static_cast<float>(0),
            static_cast<float>(24),
            static_cast<float>(24)
        }, 0.f});
        return ctx.frames;
    }
    while (std::getline(file, line)) {
        try {
            findAnimationByIndex(line, xmlPath, animIndex, ctx);            
            if (!ctx.foundTargetAnim) {
                continue;
            }
            parseFrameWidth(line, animIndex, ctx);
            parseFrameHeight(line, animIndex, ctx);
            parseDuration(line, animIndex, ctx);
            if (ctx.foundTargetAnim && line.find("</Anim>") != std::string::npos) {
                break;
            }
        } catch (const std::invalid_argument &e) {
            throw XMLParserException("Invalid number format in XML file: "
            + xmlPath + " - " + e.what());
        } catch (const std::out_of_range &e) {
            throw XMLParserException("Number out of range in XML file: "
            + xmlPath + " - " + e.what());
        } catch (const std::exception &e) {
            throw XMLParserException(e.what());
        }
    }
    if (ctx.frames.empty()) {
        throw XMLParserException("No frames found for animation index "
        + std::to_string(animIndex) + " in file: " + xmlPath);
    }
    return ctx.frames;
}
