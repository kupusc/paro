REM ALMAG
call TestCompileMT DM_ALMAG
REM RPMAG
call TestCompileMT DM_RPMAG
REM FoundationModel
call TestCompileMT FoundationModel
REM SoftwareManagement
call TestCompileMT SWM_SoftwareManagement
REM TestManagement
call TestCompileMT TM_TestManagement
REM TechnicalReporting
call TestCompileMT TR_TechnicalReporting
REM Sync
call TestCompileMT Sync_Synchronization

REM HardwareManagement
pushd %~dp0..\..\HWM_HardwareManagement\MT\
bjam.exe FCT sut_gen
bjam.exe FCT --fastbuild --scan -j4
pushd %~dp0..\..\HWM_HardwareManagement\MT\app\exe\
mt_fct --detect_memory_leaks=0 --spawn=4 --nouserattention
popd
popd

REM CLIC
pushd %~dp0..\..\CLIC_ClimateControl\MT_FSMr3\
bjam.exe FCT sut_gen
bjam.exe FCT --fastbuild --scan -j4
pushd %~dp0..\..\CLIC_ClimateControl\MT_FSMr3\app\exe\
mt_fct --detect_memory_leaks=0 --spawn=4 --nouserattention
popd
popd