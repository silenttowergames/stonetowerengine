# build all the shaders

rm assets/shaders/*.fxb
rm bin/win64/assets/shaders/*.fx
rm bin/win64/assets/shaders/*.fxh

$files = Get-ChildItem assets/shaders/*.fx

foreach($file in $files)
{
    echo ("Compiling " + $file.Name)
    & "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Utilities\bin\x86\fxc.exe" $file /T fx_2_0 /Fo ("assets/shaders/" + $file.Name + "b")
}
