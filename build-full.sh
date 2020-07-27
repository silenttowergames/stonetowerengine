# ok
cp build.ps1 build.sh
cp build-full.ps1 build-full.sh
rm -r -fo bin/win64
mkdir bin/win64
cp -r assets/ -Destination bin/win64/
cp -r libs/win64/* -Destination bin/win64/
./build.ps1
echo "Built & moved"
