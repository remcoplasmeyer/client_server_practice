#ifndef CLIENT_resourceLoader_h
#define CLIENT_resourceLoader_h
#include <map>
#include "SFML\Graphics.hpp"

namespace CLIENT {

class resourceLoader {
public:
	std::string backgroundsBasePath;
	std::string mapTextureBasePath;
	std::string playerTexturesBasePath;

	std::map<std::string, sf::Texture> backgrounds;
	std::map<std::string, sf::Texture> mapTextures;
	std::map<std::string, sf::Texture> playerTextures;
	
	resourceLoader();
	void loadTextureIntoMap(std::string imagePath, std::map<std::string, sf::Texture> &texturesMap);

	sf::Texture* getTextureFromMap(std::string name, std::map<std::string, sf::Texture> *map);
	sf::Texture* getBackground(std::string name);
	sf::Texture* getMapTexture(std::string name);
	sf::Texture* getPlayerTexture(std::string name);
	//TODO: someday, item textures, other textures, etc
};

} /* End of namespace CLIENT */

#endif // CLIENT_resourceLoader_h
