#include "headers/LoadParameters.h"

#ifndef MAIN_CPP    
#define MAIN_CPP

int main() 
{
    
    TextureParser *TextureFolder = new TextureParser();
                     TextureFolder -> ScanDirectory((char*)"textures");
                     TextureFolder -> CreateTextureConfig((char*)"config_textures.txt");
        
    Load *Config = new Load((char*)"config_world.txt");         //Подключаем конфиг и окрываем поток
            Config->Include(TextureFolder->ConfigFile);
            Config->Read((char*)"Textures Path", 1);                //Прочитать и загрузить текстуры
            Config->Read((char*)"Textures Numpollies", 2);      //Проситать и загрузить параметры полей
            Config->Read((char*)"Textures Coordinates", 5);     //Прочитать и загрузить координаты текст
    
    delete TextureFolder;
    
    

    
    
    
        
    return 0;
}

#endif









