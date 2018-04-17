========================================================================
    CONSOLE APPLICATION : readAMCASF Project Overview
========================================================================

AppWizard has created this readAMCASF application for you.

This file contains a summary of what you will find in each of the files that
make up your readAMCASF application.


readAMCASF.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

readAMCASF.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

readAMCASF.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named readAMCASF.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
command list
exit					退出
animation	on
			off
			n			播放第n个动作
			deleteall	删除所有动作
skeleton	on
			off
current		animation	显示当前播放的动作
			frame		显示当前是第几帧
loop		off			/* 不循环 */
playlist				显示播放列表
goto		n			直接到第n帧，同时播放暂停
read		path		读取.amc 或.asf 文件（读amc文件会读amc文件序列） 读asf文件有bug
					

//////////////////////////////////////////////////////////////////////////////