set -e
cd "`dirname "$0"`"

## CD 3 steps up to root/Bulk
cd ../../../

## Make Generated dir for generated project if not exist
if [ ! -d Generated_Xcode ]; then 
	mkdir Generated_Xcode
fi

## Step in Generated dir
cd Generated_Xcode

## Clean cmake garbage if there
if [ -d CMakeFiles ]; then 
	rm -r CMakeFiles 
fi
if [ -f cmake_install.cmake ]; then 
	rm cmake_install.cmake 
fi
if [ -f CMakeCache.txt ]; then 
	rm CMakeCache.txt 
fi

## Rebuild Project
cmake -G "Xcode" -DIRIS_USE_CONFIG:BOOL=ON -DIRIS_EXPLICIT_COMPILER_ID:STRING="CLANG" -DIRIS_EXPLICIT_HOST_ID:STRING="MAC" ../Source
