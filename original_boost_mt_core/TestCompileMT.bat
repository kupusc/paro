REM compiling MT for domain %1

pushd %~dp0..\..\%1\MT\

    REM FSMr2

bjam.exe sut_gen
bjam.exe --fastbuild --scan -j4

pushd %~dp0..\..\%1\MT\app\exe\
mt --detect_memory_leaks=0 --spawn=4 --nouserattention
popd

    REM FSMr3

bjam.exe FCT sut_gen
bjam.exe FCT --fastbuild --scan -j4

pushd %~dp0..\..\%1\MT\app\exe\
mt_fct --detect_memory_leaks=0 --spawn=4 --nouserattention
popd

popd