REM compiling domain %1

REM production code

pushd %~dp0..\..\..\..\C_Application\SC_OAM\%1\

call setenv WRU EC

    REM x86 bosse

pushd %~dp0..\..\..\..\C_Application\SC_OAM\FoundationModel
gnumake WinX86_WN_FCMD_GEN
popd
pushd %~dp0\..\..\..\..\C_Application\SC_OAM\InternalInterfaces
gnumake WinX86_WN_FCMD_GEN
popd
gnumake WinX86_WN_FCMD_GEN
emake WinX86_WN_FCMD_COM

    REM PPC ose target

pushd %~dp0\..\..\..\..\C_Application\SC_OAM\FoundationModel
gnumake WinPPC_WN_FCMD_GEN
popd
pushd %~dp0\..\..\..\..\C_Application\SC_OAM\InternalInterfaces
gnumake WinPPC_WN_FCMD_GEN
popd
gnumake WinPPC_WN_FCMD_GEN
emake WinPPC_WN_FCMD_COM

popd
