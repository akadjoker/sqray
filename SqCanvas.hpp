#pragma once


class Canvas
{
public:
    static Canvas &Instance()
    {
        static Canvas instance;
        return instance;
    }

    void SetColor(unsigned int r, unsigned int g, unsigned int b)
    {
        mDefaultColor.r = r;
        mDefaultColor.g = g;
        mDefaultColor.b = b;
    }

    void SetAlpha(unsigned int a)
    {
        mDefaultColor.a = a;
    }

    void SetFont(unsigned int id)
    {
        mDefaultFont = AssetManager::Instance().GetFont(id);
    }

    void Circle(float x, float y, float radius, bool mIsLine)
    {
        if (mIsLine)
        {
            DrawCircleLines(x, y, radius, mDefaultColor);
        }
        else
        {
            DrawCircle(x, y, radius, mDefaultColor);
        }
    }

    void Line(float x1, float y1, float x2, float y2)
    {

        DrawLine(x1, y1, x2, y2, mDefaultColor);
    }

    void Rect(float x, float y, float width, float height, bool mIsLine)
    {
        if (mIsLine)
        {
            Rectangle r;
            r.x = x;
            r.y = y;
            r.width = width;
            r.height = height;
            DrawRectangleLinesEx(r, mlineThickness, mDefaultColor);
        }
        else
        {
            DrawRectangle(x, y, width, height, mDefaultColor);
        }
    }

    //  RLAPI void DrawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color); // Draw ring
    // RLAPI void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color);    // Draw ring outline

    void Ring(float x, float y, float innerRadius, float outerRadius, float startAngle, float endAngle, bool mIsLine)
    {
        Vector2 center;
        center.x = x;
        center.y = y;

        if (mIsLine)
        {
            DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, mSegments, mDefaultColor);
        }
        else
        {
            DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, mSegments, mDefaultColor);
        }
    }
    void RectangleRounded(float x, float y, float width, float height, float rounding, bool mIsLine)
    {
        Rectangle r;
        r.x = x;
        r.y = y;
        r.width = width;
        r.height = height;

        if (mIsLine)
        {
            DrawRectangleRoundedLines(r, rounding, mSegments, mlineThickness,mDefaultColor);
        }
        else
        {
            DrawRectangleRounded(r, rounding, mSegments,  mDefaultColor);
        }
    }

    // DrawEllipse

    void Ellipse(float x, float y, float radiusx, float radiusy, bool mIsLine)
    {
        if (mIsLine)
        {
            DrawEllipseLines(x, y, radiusx, radiusy,  mDefaultColor);
        }
        else
        {
            DrawEllipse(x, y, radiusx, radiusy, mDefaultColor);
        }
    }
    void Point(float x, float y)
    {
        DrawPixel(x, y, mDefaultColor);
    }

    void Text(float x, float y, const char *text)
    {
        DrawText(text, x, y, mTextSize, mDefaultColor);
    }

    void SetLineThickness(float thickness)
    {
        mlineThickness = thickness;
    }

    void SetTextSize(int size)
    {
        mTextSize = size;
    }

    void SetSegments(int segments)
    {
        mSegments = segments;
    }

    void Begin()
    {
        
        BeginMode2D(mCamera);
    }

    void End()
    {
        EndMode2D();
    }
    void SetViewPosition(float x, float y)
    {
        mCamera.target.x = x;
        mCamera.target.y = y;
    }

    void SetViewZoom(float value)
    {
        mCamera.zoom = value;
    }

    void SetViewRotation(float value)
    {
        mCamera.rotation = value;
    }

    void SetViewCenter(float x, float y)
    {
        mCamera.offset.x = x;
        mCamera.offset.y = y;
    }

private:
    Canvas()
    {
        mDefaultFont = GetFontDefault();
        mTextSize=mDefaultFont.baseSize;
        
        mCamera.target.x = 0.0f;
        mCamera.target.y = 0.0f;

        mCamera.offset.y = 0.0f;
        mCamera.offset.x = 0.0f;

        mCamera.rotation = 0.0f;
        mCamera.zoom = 1.0f;
    }
    ~Canvas() {}

    Canvas(const Canvas &) = delete;
    Canvas &operator=(const Canvas &) = delete;

    Color mDefaultColor = {255, 255, 255, 255};
    Font mDefaultFont;
    int mSegments = 32;
    float mlineThickness = 1.0f;
    int mTextSize;
    Camera2D mCamera;


};

static std::map<std::string, SQFUNCTION> canvasFunctions =
{
        {"setColor", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger r, g, b;
             sq_getinteger(v, 2, &r);
             sq_getinteger(v, 3, &g);
             sq_getinteger(v, 4, &b);
             Canvas::Instance().SetColor(r, g, b);
             return 0;
         }},
        {"setAlpha", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger a;
             sq_getinteger(v, 2, &a);
             Canvas::Instance().SetAlpha(a);
             return 0;
         }},
        {"setFont", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger id;
             sq_getinteger(v, 2, &id);
             Canvas::Instance().SetFont(id);
             return 0;
         }},
        {"circle", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger x, y, radius, mIsLine;
             sq_getinteger(v, 2, &x);
             sq_getinteger(v, 3, &y);
             sq_getinteger(v, 4, &radius);
             sq_getinteger(v, 5, &mIsLine);
             Canvas::Instance().Circle(x, y, radius, mIsLine);
             return 0;
         }},
        {"line", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger x1, y1, x2, y2;
             sq_getinteger(v, 2, &x1);
             sq_getinteger(v, 3, &y1);
             sq_getinteger(v, 4, &x2);
             sq_getinteger(v, 5, &y2);
             Canvas::Instance().Line(x1, y1, x2, y2);
             return 0;
         }},
        {"rectangle", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger x, y, width, height, mIsLine;
             sq_getinteger(v, 2, &x);
             sq_getinteger(v, 3, &y);
             sq_getinteger(v, 4, &width);
             sq_getinteger(v, 5, &height);
             sq_getinteger(v, 6, &mIsLine);
             Canvas::Instance().Rect(x, y, width, height, mIsLine);
             return 0;
         }},
        {"roundRectangle", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger x, y, width, height, rounding, mIsLine;
             sq_getinteger(v, 2, &x);
             sq_getinteger(v, 3, &y);
             sq_getinteger(v, 4, &width);
             sq_getinteger(v, 5, &height);
             sq_getinteger(v, 6, &rounding);
             sq_getinteger(v, 7, &mIsLine);
             Canvas::Instance().RectangleRounded(x, y, width, height, rounding, mIsLine);
             return 0;
         }},
        {"ring", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger x, y, innerRadius, outerRadius, startAngle, endAngle, mIsLine;
             sq_getinteger(v, 2, &x);
             sq_getinteger(v, 3, &y);
             sq_getinteger(v, 4, &innerRadius);
             sq_getinteger(v, 5, &outerRadius);
             sq_getinteger(v, 6, &startAngle);
             sq_getinteger(v, 7, &endAngle);
             sq_getinteger(v, 8, &mIsLine);
             Canvas::Instance().Ring(x, y, innerRadius, outerRadius, startAngle, endAngle, mIsLine);
             return 0;
         }},
        {"ellipse", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger x, y, radiusx, radiusy, mIsLine;
             sq_getinteger(v, 2, &x);
             sq_getinteger(v, 3, &y);
             sq_getinteger(v, 4, &radiusx);
             sq_getinteger(v, 5, &radiusy);
             sq_getinteger(v, 6, &mIsLine);
             Canvas::Instance().Ellipse(x, y, radiusx, radiusy, mIsLine);
             return 0;
         }},
        {"text", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger x, y;
             const SQChar* text;
             sq_getinteger(v, 2, &x);
             sq_getinteger(v, 3, &y);
             sq_getstring(v, 4, &text);
             Canvas::Instance().Text(x, y, text);
             return 0;
         }},
        {"point", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger x, y;
             sq_getinteger(v, 2, &x);
             sq_getinteger(v, 3, &y);
             Canvas::Instance().Point(x, y);
             return 0;
         }},
         {"setLineThickness", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger thickness;
             sq_getinteger(v, 2, &thickness);
             Canvas::Instance().SetLineThickness(thickness);
             return 0;
         }},
    
         {"setTextSize", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger size;
             sq_getinteger(v, 2, &size);
             Canvas::Instance().SetTextSize(size);
             return 0;
         }},
         {"setSegments", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger segments;
             sq_getinteger(v, 2, &segments);
             Canvas::Instance().SetSegments(segments);
             return 0;    
        }},
         {"begin", [](HSQUIRRELVM ) -> SQInteger   
         {
             Canvas::Instance().Begin();
             return 0;
         }},
         {"end", [](HSQUIRRELVM ) -> SQInteger
         {
             Canvas::Instance().End();
             return 0;
         }},
         {"setViewPosition", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger x, y;
             sq_getinteger(v, 2, &x);
             sq_getinteger(v, 3, &y);
             Canvas::Instance().SetViewPosition(x, y);
             return 0;
             
         }},
         {"setViewZoom", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger zoom;
             sq_getinteger(v, 2, &zoom);
             Canvas::Instance().SetViewZoom(zoom);
             return 0;
             
         }},
         {"setViewRotation", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger rotation;
             sq_getinteger(v, 2, &rotation);
             Canvas::Instance().SetViewRotation(rotation);
             return 0;
         }},
         {"setViewCenter", [](HSQUIRRELVM v) -> SQInteger
         {
             SQInteger x, y;
             sq_getinteger(v, 2, &x);
             sq_getinteger(v, 3, &y);
             Canvas::Instance().SetViewCenter(x, y);
             return 0;
    }}   

};

inline void RegisterCanvasFunctions(HSQUIRRELVM v)
{
    sq_pushroottable(v);
    sq_pushstring(v, "graphics", -1);
    sq_newtable(v);
    for (const auto &func : canvasFunctions)
    {
        REGISTER_SQ_FUNC(v, func.first.c_str(), func.second);
    }
    sq_newslot(v, -3, SQTrue);
    sq_pop(v, 1);
}