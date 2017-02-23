@echo Win32 ObEngine builder (Require mingw64)

@set /p mingwpath="Path to MinGW64 folder : "
@set /p sfmlpath="Path to SFML folder : "
@set /p luapath="Path to Lua53 folder : "

@echo "Building ObEngine... (This can take a long time)"
@"%mingwpath%/bin/g++" -O3 -c src/*.cpp^
 -I"include/" -I"extlibs/include/" -I"%sfmlpath%/include" -I"%luapath%\include"

@echo "Linking !"
@"%mingwpath%/bin/g++" *.o -o ObEngine^
 -L"%sfmlpath%/lib" -L"%luapath%" -L"extlibs/lib/mingw" -L"%mingwpath%/x86_64-w64-mingw32/lib"^
 -lopengl32 -lclip -lclipper -llua53 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

@del *.o

@echo "Moving ObEngine executable into engine/ folder"
@move /y "ObEngine.exe" "engine/"

@echo "Don't forget to copy all dlls (SFML, Lua53 and MinGW) in engine/ folder :)"
@echo "Build over"
@pause
