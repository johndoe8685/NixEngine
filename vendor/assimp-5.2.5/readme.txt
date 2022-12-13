For NixEngine to work Assimp has to be compiled.
Compile assimp and zlib and add them here.
Make sure compile modes are the same (ex. NixEngine compiling on Debug mode then Assimp has to compile on Debug mode too)

if assimp is going to be compiled on linux then change the assimp-vc143-mtd.lib to libassimp.a
also change zlibstaticd.lib to libzlibstatic.a