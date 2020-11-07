#!/bin/bash

function doDir {
    local DIR=$1'/*'
    
    for filename in $DIR; do
        if [ -d $filename ]; then
            doDir $filename OBJS
            continue
        fi
        
        if [[ $filename == *.c ]]; then
            objf=$filename'.'$COMPILER'.o'
            
            if [ "$filename" -nt "$objf" ]; then
                gcc -c $filename ${INCS[*]} -o $objf
                echo "Compiling $objf..."
            fi
            
            OBJS+=($objf)
            continue
        fi
    done
}

OBJS=()
INCS=(
    'flecs-master/include'
    'FNA3D-master/include'
    'json-c-master/include'
    'lua-5.4.0/include'
    'soloud-custom/include'
)
LIBS=(
    'flecs-master'
    'FNA3D-master'
    'json-c-master'
    'lua-5.4.0'
)
LFLAGS=(
    'flecs'
    'FNA3D'
    'json-c'
    'lua54'
    'm' # math.h
)
DIR=`pwd`

COMPILER='gcc'
if [ $1 ]; then
    COMPILER=$1
fi

PLATFORM='64'
if [ $2 ]; then
    PLATFORM=$2
fi

for i in $(seq 1 ${#INCS[*]})
do
    INCS[$i - 1]='-I/C/'$COMPILER'/'$PLATFORM'/'${INCS[$i - 1]}
done

for i in $(seq 1 ${#LIBS[*]})
do
    LIBS[$i - 1]='-L/C/'$COMPILER'/'$PLATFORM'/'${LIBS[$i - 1]}
done

for i in $(seq 1 ${#LFLAGS[*]})
do
    LFLAGS[$i - 1]='-l'${LFLAGS[$i - 1]}
done

doDir ./src

$COMPILER -m${PLATFORM} -g -pedantic libs/linux${PLATFORM}/${COMPILER}/libsoloud-out.o ${OBJS[*]} -o ./bin/linux${PLATFORM}/${COMPILER}/main ${INCS[*]} ${LIBS[*]} ${LFLAGS[*]} -Wl,-rpath=${DIR}/bin/linux${PLATFORM}/${COMPILER}/libs/
