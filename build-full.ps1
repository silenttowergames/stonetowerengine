# ok
rm -r -fo bin/win64
mkdir bin/win64
./build-shaders.ps1
cp -r assets/ -Destination bin/win64/
cp -r libs/win64/* -Destination bin/win64/
rm -r bin/win64/assets/shaders/*.fx
./build.ps1
echo "Built & moved"
