start "" vc_redist.x86.exe
reg add "HKEY_CLASSES_ROOT\Directory\shell\View with HealthTrailsGUI" /v AppliesTo /t Reg_SZ /d "\"*sdulog\" OR \"*Health\\Event Store\\Trail\""
reg add "HKEY_CLASSES_ROOT\Directory\shell\View with HealthTrailsGUI\command" /ve /d "%~dp0HealthTrailsGUI.exe %1"