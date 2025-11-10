/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** PokemonManager
*/

#include "entities/Pokemon.hpp"

Pokemon &PokemonManager::getPokemon(int id)
{
    auto it = _pokemons.find(id);
    std::unique_ptr<Pokemon> pokemon;

    if (it != _pokemons.end()) {
        return *it->second;
    }
    try {
        pokemon = std::make_unique<Pokemon>(id, _textureManager);
    } catch (const Pokemon::PokemonException &e) {
        throw PokemonManager::PokemonManagerException("Can't load Pokemon");
    }
    Pokemon &ref = *pokemon;
    _pokemons[id] = std::move(pokemon);
    return ref;
}

std::vector<int> PokemonManager::listIds() const
{
    std::vector<int> ids;

    ids.reserve(_pokemons.size());
    for (auto &kv : _pokemons) {
        ids.push_back(kv.first);
    }
    return ids;
}

std::unique_ptr<Pokemon> PokemonManager::createPokemon(int id)
{
    return getPokemon(id).clone();
}
