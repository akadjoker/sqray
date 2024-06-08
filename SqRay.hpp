#pragma once
static std::map<std::string, SQFUNCTION> raylibFunctions = 
{
    {"InitWindow", [](HSQUIRRELVM v) -> SQInteger 
    {
        SQInteger width, height;
        const SQChar* title;
        sq_getinteger(v, 2, &width);
        sq_getinteger(v, 3, &height);
        sq_getstring(v, 4, &title);
        InitWindow(width, height, title);
        return 0;
    }},
     {"SetTargetFPS", [](HSQUIRRELVM v) -> SQInteger 
     {
        SQInteger fps;
        sq_getinteger(v, 2, &fps);
        SetTargetFPS(fps);
        return 0;
    }},
    {"WindowShouldClose", [](HSQUIRRELVM v) -> SQInteger
    {
        sq_pushbool(v, WindowShouldClose());
        return 1;
    }},
    {"BeginDrawing", [](HSQUIRRELVM ) -> SQInteger 
    {
        BeginDrawing();
        return 0;
    }},
    {"EndDrawing", [](HSQUIRRELVM ) -> SQInteger 
    {
        EndDrawing();
        return 0;
    }},
    {"GetFrameTime", [](HSQUIRRELVM v) -> SQInteger 
    {
        sq_pushfloat(v, GetFrameTime());
        return 1;
    }},
    {"CloseWindow", [](HSQUIRRELVM ) -> SQInteger 
    {
        AssetManager::Instance().Free();
        CloseWindow();
        return 0;
    }},
    {"ClearBackground", [](HSQUIRRELVM v) -> SQInteger
    {
        SQInteger r, g, b;
        sq_getinteger(v, 2, &r);
        sq_getinteger(v, 3, &g);
        sq_getinteger(v, 4, &b);
        Color color;
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = 255;
        ClearBackground(color);
        return 0;
    }},


};


inline void RegisterRaylibFunctions(HSQUIRRELVM v) 
{
    sq_pushroottable(v);
    for (const auto& func : raylibFunctions) 
    {
        REGISTER_SQ_FUNC(v, func.first.c_str(), func.second);
    }
    sq_pop(v, 1);
}