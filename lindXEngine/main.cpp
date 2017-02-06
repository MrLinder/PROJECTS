#include <cstring> 
#include "headers\LoadParameters.h"
#include "headers\LoadParameters.h"

int main(){
	TextureParser *TextureFolder = new TextureParser;
						TextureFolder -> ScanDirectory("textures");
						TextureFolder -> CreateTextureConfig("config_textures.txt");
												
						
						
						
					delete TextureFolder;
				
						
						
	return EXIT_SUCCESS;
}



