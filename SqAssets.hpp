#pragma once



class AssetManager
{
public:
    static AssetManager &Instance()
    {
        static AssetManager instance;
        return instance;
    }

    bool ImageLoad(int id, const char *filename)
    {
        if (id == 0)
        {
            id = mLastImageId + 1;
        }
        if (images.find(id) != images.end())
        {
            Log(1,"Image ID already exists");
            return false;
        }

        Image image = LoadImage(filename);
        if (image.data == nullptr)
        {
           // Log(1,"Failed to load image");
            return false;
        }
        images[id] = image;

        mLastImageId++;

        return true;
    }

    bool ImageExists(int id) const
    {
        return images.find(id) != images.end();
    }

    Image &GetImage(int id)
    {
        if (images.find(id) == images.end())
        {
           Log(2,"Image ID not found");

           return mImageDefault;
        }
        return images[id];
    }

    void UnloadAllImages()
    {
        for (auto &pair : images)
        {
            UnloadImage(pair.second);
        }
        images.clear();
    }
    void FreeImage(int id)
    {
        if (images.find(id) == images.end())
        {
            Log(2,"Image ID not found");
            return;
        }
        UnloadImage(images[id]);
        images.erase(id);
    }

    bool TextureLoad(int id, const char *filename)
    {
        if (id == 0)
        {
            id = mLastTextureId + 1;
        }
        if (textures.find(id) != textures.end())
        {
            Log(1,"Texture ID already exists");
            return false;
        }

        Texture2D texture = LoadTexture(filename);
        if (texture.id == 0)
        {
        //    Log(2,"Failed to load texture");
            return false;
        }
        textures[id] = texture;
        mLastTextureId++;
        

        return true;
    }

    bool TextureExists(int id) const
    {
        return textures.find(id) != textures.end();
    }

    Texture2D &GetTexture(int id)
    {
        if (textures.find(id) == textures.end())
        {
            Log(1,"Texture ID not found");
            return mTextureDefault;
        }
        return textures[id];
    }

    void UnloadAllTextures()
    {
        for (auto &pair : textures)
        {
            UnloadTexture(pair.second);
        }
        textures.clear();
    }
    void FreeTexture(int id)
    {
        if (textures.find(id) == textures.end())
        {
            Log(2,"Texture ID not found");
            return;
        }
        UnloadTexture(textures[id]);
        textures.erase(id);
    }

    bool FontLoad(int id, const char *filename)
    {
        if (id == 0)
        {
            id = mLastFontId + 1;
        }
        if (fonts.find(id) != fonts.end())
        {
            Log(1,"Font ID already exists");
            return false;
        }

        Font font = LoadFont(filename);
        if (font.baseSize == 0)
        {
         //   Log(2,"Failed to load font");
            return false;
        }
        fonts[id] = font;
        mLastFontId++;  

        return true;
    }

    bool FontExists(int id) const
    {
        return fonts.find(id) != fonts.end();
    }

    Font &GetFont(int id)
    {
        if (fonts.find(id) == fonts.end())
        {
            Log(1,"Font ID not found");
            return mFontDefault;
        }
        return fonts[id];
    }

    void UnloadAllFonts()
    {
        for (auto &pair : fonts)
        {
            UnloadFont(pair.second);
        }
        fonts.clear();
    }
    void FreeFont(int id)
    {
        if (fonts.find(id) == fonts.end())
        {
            Log(2,"Font ID not found");
            return;
        }
        UnloadFont(fonts[id]);
        fonts.erase(id);
    }

    void Clear()
    {
       UnloadAllImages();
       UnloadAllTextures();
       UnloadAllFonts();

    }

    void Free()
    {
      UnloadImage(mImageDefault);
      UnloadTexture(mTextureDefault);
    }

private:
    AssetManager() 
    {
        mImageDefault = GenImageColor(32, 32, MAGENTA);
        //mFontDefault = GetFontDefault();
        //mTextureDefault = LoadTextureFromImage(mImageDefault);
    }
    ~AssetManager()    {           }

    AssetManager(const AssetManager &) = delete;
    AssetManager &operator=(const AssetManager &) = delete;

    std::map<int, Image> images;
    std::map<int, Texture2D> textures;
    std::map<int, Font> fonts;


    long mLastImageId = 0;
    long mLastTextureId = 0;
    long mLastFontId = 0;
    Image mImageDefault;
    Texture2D mTextureDefault;
    Font mFontDefault;
};




static std::map<std::string, SQFUNCTION> assetsFunctions = 
{
    {"loadImage", [](HSQUIRRELVM v) -> SQInteger 
    {
        SQInteger id=0;
        const SQChar* title;
        sq_getstring(v, 2, &title);

        SQInteger argc = sq_gettop(v);
        if (argc == 3) 
        { 
            sq_getinteger(v, 3, &id);
        }
        bool result =  AssetManager::Instance().ImageLoad(id, title);
        sq_pushbool(v, result);
        return 1;
    }},
    {"imageExists", [](HSQUIRRELVM v) -> SQInteger 
    {
        SQInteger id=0;
        sq_getinteger(v, 2, &id);
        bool result =  AssetManager::Instance().ImageExists(id);
        sq_pushbool(v, result);
        return 1;
    }},
    {"unloadImage", [](HSQUIRRELVM v) -> SQInteger 
    {
        SQInteger id=0;
        sq_getinteger(v, 2, &id);
        AssetManager::Instance().FreeImage(id);
        return 0;
    }},
    {"loadTexture", [](HSQUIRRELVM v) -> SQInteger 
    {
        SQInteger id=0;
        const SQChar* title;
        sq_getstring(v, 2, &title);

        SQInteger argc = sq_gettop(v);
        if (argc == 3) 
        { 
            sq_getinteger(v, 3, &id);
        }
        bool result =  AssetManager::Instance().TextureLoad(id, title);
        sq_pushbool(v, result);
        return 1;
    }},
    {"textureExists", [](HSQUIRRELVM v) -> SQInteger 
    {
        SQInteger id=0;
        sq_getinteger(v, 2, &id);
        bool result =  AssetManager::Instance().TextureExists(id);
        sq_pushbool(v, result);
        return 1;
    }},
    {"unloadTexture", [](HSQUIRRELVM v) -> SQInteger 
    {
        SQInteger id=0;
        sq_getinteger(v, 2, &id);
        AssetManager::Instance().FreeTexture(id);
        return 0;
    }},
    {"loadFont", [](HSQUIRRELVM v) -> SQInteger 
    {
        SQInteger id=0;
        const SQChar* title;
        sq_getstring(v, 2, &title);

        SQInteger argc = sq_gettop(v);
        if (argc == 3) 
        { 
            sq_getinteger(v, 3, &id);
        }
        bool result =  AssetManager::Instance().FontLoad(id, title);
        sq_pushbool(v, result);
        return 1;
    }},
    {"fontExists", [](HSQUIRRELVM v) -> SQInteger 
    {
        SQInteger id=0;
        sq_getinteger(v, 2, &id);
        bool result =  AssetManager::Instance().FontExists(id);
        sq_pushbool(v, result);
        return 1;
    }},
    {"unloadFont", [](HSQUIRRELVM v) -> SQInteger 
    {
        SQInteger id=0;
        sq_getinteger(v, 2, &id);
        AssetManager::Instance().FreeFont(id);
        return 0;
    }},
    {"lear", [](HSQUIRRELVM ) -> SQInteger 
    {
        AssetManager::Instance().Clear();
        return 0;
    }}   

};


inline void RegisterAssetsFunctions(HSQUIRRELVM v) 
{
    sq_pushroottable(v);
    sq_pushstring(v, "assets", -1);
    sq_newtable(v); // Criar uma nova tabela para armazenar as funções
    for (const auto& func : assetsFunctions) 
    {
        REGISTER_SQ_FUNC(v, func.first.c_str(), func.second);
    }
    sq_newslot(v, -3, SQTrue); // Adicionar a tabela de funções ao root table
    sq_pop(v, 1);
}