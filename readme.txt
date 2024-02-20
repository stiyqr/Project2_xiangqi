If you run into problems when running in Visual Studio Debugger:
1. Install DirectX SDK (DXSDK_Jun10)
(should run fine without installing this, but if cannot run please install)

If still cannot run program in Visual Studio:
2. Change configuration settings:
	- right click "WindowsProject1" project
	- open Properties
	- make sure Configuration is "Active(Debug)" and Platform is "Active(Win32)"
	- open Configuration Properties -> VC++ Directories
	- click Include Directories, click the arrow and <Edit...>
	- in the uppermost textbox type "$(IncludePath)" and "$(DXSDK_DIR)Include"
	- click OK
	- click Library Directories, click the arrow and <Edit...>
	- in the uppermost textbox type "$(DXSDK_DIR)Lib\x86" (or "$(DXSDK_DIR)Lib\x64")
	- click OK
	- Apply and close