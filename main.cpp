#include "pch.hpp"

#include <squirrel.h>
#include <sqstdio.h>
#include <sqstdaux.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdblob.h>
#include <sqstdio.h>
#include <sqstdsystem.h>

#include "SqUtils.hpp"
#include "SqAssets.hpp"
#include "SqCanvas.hpp"
#include "SqRay.hpp"

 




//DEFINE_RAYLIB_FUNC_1(ClearBackground, Color, integer)





int main(int cv, char *argv[])
{
    HSQUIRRELVM vm = sq_open(1024);
    sqstd_seterrorhandlers(vm);
    sq_setprintfunc(vm, printfunc, errorfunc);

     sq_pushroottable(vm);

    sqstd_register_bloblib(vm);
    sqstd_register_iolib(vm);
    sqstd_register_systemlib(vm);
    sqstd_register_mathlib(vm);
    sqstd_register_stringlib(vm);
    sq_enabledebuginfo(vm,1);
    sqstd_seterrorhandlers(vm);

    RegisterRaylibFunctions(vm);
    RegisterAssetsFunctions(vm);
    RegisterCanvasFunctions(vm);


  
    if (cv > 1)
    {
        if (SQ_FAILED(sqstd_dofile(vm, argv[1], SQFalse, SQTrue))) 
        {
            return -1;
        }
    } else 
    {
    if (SQ_FAILED(sqstd_dofile(vm, "main.nut", SQFalse, SQTrue))) 
    {
        
        return -1;
    }
    }

    

    
    sq_close(vm);
    return 0;
}
