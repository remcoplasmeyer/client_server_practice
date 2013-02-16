#include "resourceLoader.h"
#include <SFML/Graphics.hpp>
#include "../Log.h"
#include <map>
#include <array>

/*
	[resourceLoader] loads and holds all the resources
	we put them in a map by string to easily load them later on
	this could be more efficient, but this is the easiest way to handle this right now

	TODO: Error handling!
*/

namespace CLIENT {

	resourceLoader::resourceLoader() {
		//we load all the resources here
		//hardcoded images for now
		this->backgrounds = std::map<std::string, sf::Texture>();
		this->mapTextures = std::map<std::string, sf::Texture>();
		this->playerTextures = std::map<std::string, sf::Texture>();

		backgroundsBasePath = "images/backgrounds/";
		mapTextureBasePath = "images/tiles/";
		playerTexturesBasePath = "images/chars/";

		std::string backgroundHolder[] = {"testbg.png"};
		std::string mapTexturesHolder[] = {"dirt.png", "grass_main.png"};
		std::string playerTexturesHolder[] = {"mario_template.png"};

		for each (std::string image in backgroundHolder) {
			loadTextureIntoMap(this->backgroundsBasePath + image, backgrounds);
		}
		for each (std::string image in mapTexturesHolder) {
			loadTextureIntoMap(this->mapTextureBasePath + image, mapTextures);
		}
		for each (std::string image in playerTexturesHolder) {
			loadTextureIntoMap(this->playerTexturesBasePath + image, playerTextures);
		}
	}

	void resourceLoader::loadTextureIntoMap(std::string imagePath, std::map<std::string, sf::Texture> &texturesMap) {
		sf::Texture texture;
		if(texture.loadFromFile(imagePath)) {
			texture.setRepeated(true);
			texturesMap[imagePath] = texture;
		} else {
			FILE_LOG(logERROR) << "Problem loading image: " << imagePath;
		}
	}

	sf::Texture* resourceLoader::getTextureFromMap(std::string name, std::map<std::string, sf::Texture> *map) {
		sf::Texture *texture = &map->at(name);
		return texture;
	}

	sf::Texture* resourceLoader::getBackground(std::string name) {
		return getTextureFromMap(backgroundsBasePath + name, &backgrounds);
	}
	sf::Texture* resourceLoader::getMapTexture(std::string name) {
		return getTextureFromMap(mapTextureBasePath + name, &mapTextures);
	}
	sf::Texture* resourceLoader::getPlayerTexture(std::string name) {
		return getTextureFromMap(playerTexturesBasePath + name, &playerTextures);
	}

} /* End of namespace CLIENT */
