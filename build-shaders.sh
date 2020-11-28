START=`date +%s%N`

PIDS=()

for filename in assets/shaders/*.fx; do
    wine ~/.wine/drive_c/Program\ Files\ \(x86\)/Microsoft\ DirectX\ SDK\ \(June\ 2010\)/Utilities/bin/x64/fxc.exe $filename /T fx_2_0 /Fo $filename'b' &> /dev/null &
    PIDS+=$!' '
done

for pid in ${PIDS[*]}; do
    wait $pid
done

let END=`date +%s%N`-$START

echo That took ${END} S
