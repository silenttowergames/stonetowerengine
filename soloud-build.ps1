# PUT THIS IN THE SOLOUD SRC
# DELETE ./src/tools
# DELTEE ./src/backends/* anything not SDL2 static

$files = Get-ChildItem -Recurse ./src/*.c
$filesPP = Get-ChildItem -Recurse ./src/*.cpp

foreach($file in $files)
{
    $fileO = $file.ToString() + ".o"
    
    g++ -g -c $file -o $fileO -DWITH_SDL2_STATIC -IC:\C\libs\gcc\64\soloud-custom\include -IC:\C\libs\gcc\64\SDL2-2.0.14\x86_64-w64-mingw32\include\SDL2
}

foreach($file in $filesPP)
{
    $fileO = $file.ToString() + ".o"
    
    g++ -g -c $file -o $fileO -DWITH_SDL2_STATIC -IC:\C\libs\gcc\64\soloud-custom\include -IC:\C\libs\gcc\64\SDL2-2.0.14\x86_64-w64-mingw32\include\SDL2
}
