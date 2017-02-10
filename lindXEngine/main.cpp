#include <cstring> 
#include "headers\LoadParameters.h"
#include "headers\LoadParameters.h"

const char path_texture[]="textures";				//Директория в корневой папке игры в которой искать текстуры
const char texture_file[]="config_textures.txt";	//Имя файла для базы текстур (если его нет, то будет создан)
const char config_world[]="config_world.txt";		//Имя файла с конфигурацией мира

int main(){
	TextureParser *TextureFolder = new TextureParser();
						TextureFolder -> ScanDirectory(path_texture);
						TextureFolder -> CreateTextureConfig(texture_file);
		
	Load *Config = new Load(config_world, texture_file, TextureFolder -> NumLines);					
			Config -> ScanConfigFiles();
			Config -> Show();
			
	delete TextureFolder;	
	delete Config;					
	return EXIT_SUCCESS;
}



