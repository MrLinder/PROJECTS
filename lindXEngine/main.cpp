#include "headers/LoadParameters.h"

#ifndef MAIN_CPP	
#define MAIN_CPP

int main() 
{
	  TypesForParsers *ScanTexture = new TypesForParsers();
		ScanTexture -> ScanDirectory((char*)"textures");
		ScanTexture -> Texture_file((char*)"config_textures.txt");

		delete ScanTexture;
		
	  return 0;
}

#endif









