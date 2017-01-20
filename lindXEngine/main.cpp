#include <cstring> 
#include "headers\LoadParameters.h"
#include "headers\LoadParameters.h"

int main(){
	TextureParser *TextureFolder = new TextureParser;
						TextureFolder -> ScanDirectory("textures");
												
					delete TextureFolder;
				
						
						
	return EXIT_SUCCESS;
}
