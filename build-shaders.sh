for filename in assets/shaders/*.fx; do
    wine ~/.wine/drive_c/Program\ Files\ \(x86\)/Microsoft\ DirectX\ SDK\ \(June\ 2010\)/Utilities/bin/x64/fxc.exe $filename /T fx_2_0 /Fo $filename'b'
done
