include(muhkuh.version)
`; Muhkuh Inno Setup Cfg'
`'
`[Setup]'
`AppName=Muhkuh'
`AppVersion="'__VERSION_ALL__`"'
`AppVerName="Muhkuh '__VERSION_ALL__`"'
`OutputBaseFilename=muhkuh_'__VERSION_ALL__`_setup'
`VersionInfoTextVersion="'__VERSION_ALL__`"'
`VersionInfoVersion="'__VERSION_ALL__`"'
`'
`DefaultDirName={pf}\Muhkuh'
`DefaultGroupName=Muhkuh'
`Compression=lzma/max'
`SolidCompression=yes'
`'
`OutputDir=.'
`SourceDir=..\..'
`'
`AllowNoIcons=yes'
`;ChangesAssociations=yes'
`InfoBeforeFile=changelog.txt'
`LicenseFile=docs\gpl-2.0.txt'
`'
`; misc info'
`AppPublisher=Muhkuh team'
`AppPublisherURL=http://muhkuh.sourceforge.net/'
`AppSupportURL=http://www.sourceforge.net/projects/muhkuh'
`AppUpdatesURL=http://www.sourceforge.net/projects/muhkuh'
`VersionInfoCopyright=Copyright (C) 2008, Muhkuh team'
`AppCopyright=Copyright (C) 2008, Muhkuh team'
`'
`; icon stuff'
`UninstallDisplayIcon=icons\custom\muhkuh_uninstall.ico'
`SetupIconFile=icons\custom\muhkuh.ico'
`;WizardImageFile=icons\custom\muhkuh.ico'
`'
`'
`[Types]'
`Name: "full";    Description: "Full installation"'
`Name: "compact"; Description: "Only install the base system without plugins"'
`Name: "custom";  Description: "Custom installation";                          Flags: iscustom'
`'
`[Components]'
`Name: muhkuh;                   Description: "Muhkuh base application";  Types: full compact custom; Flags: fixed'
`Name: plugin_romloader_baka;    Description: "Romloader baka plugin";    Types: full'
`Name: plugin_romloader_uart;    Description: "Romloader uart plugin";    Types: full'
`Name: plugin_romloader_usb;     Description: "Romloader usb plugin";     Types: full'
`Name: plugin_romloader_openocd; Description: "Romloader openocd plugin"; Types: full'
`Name: lua_scripts;              Description: "Lua scripts";              Types: full compact'
`Name: demos;                    Description: "Demos";                    Types: full'
`'
`[Tasks]'
`Name: startmenu;       Description: "Create icons in Start menu";  GroupDescription: "Additional icons:"; Components: muhkuh'
`Name: desktopicon;     Description: "Create a &desktop icon";      GroupDescription: "Additional icons:"; Components: muhkuh'
`Name: quicklaunchicon; Description: "Create a &Quick Launch icon"; GroupDescription: "Additional icons:"; Components: muhkuh'
`'
`[Files]'
`Source: "bin\muhkuh.exe";      DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\muhkuh_tips.txt"; DestDir: "{app}\application"; Components: muhkuh'
`; the wxwidgets dlls'
`Source: "bin\wxbase28_net_vc.dll" ;      DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxbase28_odbc_vc.dll";      DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxbase28_vc.dll";           DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxbase28_xml_vc.dll";       DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_adv_vc.dll";        DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_aui_vc.dll";        DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_core_vc.dll";       DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_dbgrid_vc.dll";     DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_gl_vc.dll";         DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_html_vc.dll";       DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_media_vc.dll";      DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_qa_vc.dll";         DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_richtext_vc.dll";   DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_stc_vc_custom.dll"; DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_vc.dll";            DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxmsw28_xrc_vc.dll";        DestDir: "{app}\application"; Components: muhkuh'
`; the wxLua dlls'
`Source: "bin\lua5.1.dll";                  DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxbindadv.dll";   DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxbindaui.dll";   DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxbindbase.dll";  DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxbindcore.dll";  DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxbindgl.dll";    DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxbindhtml.dll";  DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxbindmedia.dll"; DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxbindnet.dll";   DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxbindstc.dll";   DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxbindxml.dll";   DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxbindxrc.dll";   DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxlua.dll";       DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxluadebug.dll";  DestDir: "{app}\application"; Components: muhkuh'
`Source: "bin\wxlua_msw28_wxluasocket.dll"; DestDir: "{app}\application"; Components: muhkuh'
`; the docs'
`Source: "docs\gpl-2.0.txt"; DestDir: "{app}\docs"; Components: muhkuh'
`Source: "changelog.txt";    DestDir: "{app}\docs"; Components: muhkuh'
`'
`Source: "bin\baka.dll"; DestDir: "{app}\application\plugins"; Components: plugin_romloader_baka'
`Source: "bin\baka.xml"; DestDir: "{app}\application\plugins"; Components: plugin_romloader_baka'
`'
`Source: "bin\bootloader_usb.dll";                                DestDir: "{app}\application\plugins";  Components: plugin_romloader_usb'
`Source: "bin\bootloader_usb.xml";                                DestDir: "{app}\application\plugins";  Components: plugin_romloader_usb'
`Source: "plugins\romloader\usb\win\driver\libusb0.dll";          DestDir: "{app}\driver\romloader_usb"; Components: plugin_romloader_usb'
`Source: "plugins\romloader\usb\win\driver\libusb0.sys";          DestDir: "{app}\driver\romloader_usb"; Components: plugin_romloader_usb'
`Source: "plugins\romloader\usb\win\driver\netx_bootmonitor.cat"; DestDir: "{app}\driver\romloader_usb"; Components: plugin_romloader_usb'
`Source: "plugins\romloader\usb\win\driver\netx_bootmonitor.inf"; DestDir: "{app}\driver\romloader_usb"; Components: plugin_romloader_usb'
`'
`Source: "bin\bootloader_uart.dll";                                DestDir: "{app}\application\plugins";   Components: plugin_romloader_uart'
`Source: "bin\bootloader_uart.xml";                                DestDir: "{app}\application\plugins";   Components: plugin_romloader_uart'
`Source: "plugins\romloader\uart\win\driver\netX_bootmonitor.inf"; DestDir: "{app}\driver\romloader_uart"; Components: plugin_romloader_uart'
`Source: "plugins\romloader\uart\win\driver\usbsernx.sys";         DestDir: "{app}\driver\romloader_uart"; Components: plugin_romloader_uart'
`'
`Source: "bin\openocd.dll";                     DestDir: "{app}\application\plugins"; Components: plugin_romloader_openocd'
`Source: "bin\openocd_netx50_jtagkey_win.xml";  DestDir: "{app}\application\plugins"; Components: plugin_romloader_openocd'
`Source: "bin\openocd_netx500_jtagkey_win.xml"; DestDir: "{app}\application\plugins"; Components: plugin_romloader_openocd'
`Source: "bin\openocd_nxhx50_win.xml";          DestDir: "{app}\application\plugins"; Components: plugin_romloader_openocd'
`'
`Source: "bin\lua\mmio.lua";                 DestDir: "{app}\application\lua"; Components: lua_scripts'
`Source: "bin\lua\muhkuh_system.lua";        DestDir: "{app}\application\lua"; Components: lua_scripts'
`Source: "bin\lua\select_plugin.lua";        DestDir: "{app}\application\lua"; Components: lua_scripts'
`Source: "bin\lua\serialnr.lua";             DestDir: "{app}\application\lua"; Components: lua_scripts'
`Source: "bin\lua\tester.lua";               DestDir: "{app}\application\lua"; Components: lua_scripts'
`'
`Source: "plugins\romloader\_demos\memory_read_gui\read_write_gui.lua";       DestDir: "{app}\demos\memory_read_gui";     Components: demos'
`Source: "plugins\romloader\_demos\memory_read_gui\test_description.xml";     DestDir: "{app}\demos\memory_read_gui";     Components: demos'
`Source: "plugins\romloader\_demos\memory_read_simple\test_description.xml";  DestDir: "{app}\demos\memory_read_simple";  Components: demos'
`Source: "plugins\romloader\_demos\memory_read_tester\test_description.xml";  DestDir: "{app}\demos\memory_read_tester";  Components: demos'
`Source: "plugins\romloader\_test\test_description.xml";                      DestDir: "{app}\demos\romloader_test";      Components: demos'
`Source: "plugins\romloader\_test\netxtest_nx50.bin";                         DestDir: "{app}\demos\romloader_test";      Components: demos'
`Source: "plugins\romloader\_test\netxtest_nx500.bin";                        DestDir: "{app}\demos\romloader_test";      Components: demos'
`Source: "plugins\romloader\_demos\Muhkuh.cfg";                               DestDir: "{app}\application";               Components: demos'
`'
`'
`[Icons]'
`Name: {group}\Muhkuh; Filename: {app}\application\muhkuh.exe; WorkingDir: {app}\application; Components: muhkuh; Tasks: startmenu'
`Name: {group}\Uninstall; Filename: {uninstallexe}; Components: muhkuh; Tasks: startmenu'
`'
`Name: {userdesktop}\Muhkuh; Filename: {app}\application\muhkuh.exe; WorkingDir: {app}\application; Components: muhkuh; Tasks: desktopicon'
`Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\Muhkuh; Filename: {app}\application\muhkuh.exe; WorkingDir: {app}\application; Tasks: quicklaunchicon'
`'
`'
`[Messages]'
`BeveledLabel=Muhkuh'
`'
