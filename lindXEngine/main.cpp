






int main() 
{
	  TypesForParsers *ScanTexture = new TypesForParsers();
		ScanTexture -> ScanDirectory((char*)"textures");
		ScanTexture -> Texture_file((char*)"config_textures.txt");

	  return 0;
}











