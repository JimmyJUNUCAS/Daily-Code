1 找到调用接口
调用接口在
Meshlab—tools—SLDecodecWorker—setup()
可以选择不同的编码方式

2 编码方式目录
Meshlab—SourceFiles—codec
可以选择多种编码方式

3 选择编码方式设定
Meshlab—SourceFiles—tools—SLDecodecWorker.cpp
Meshlab—SourceFiles—tools—SLScanWorker.cpp

QString patternMode = settings.value("pattern/mode", CODECPHASESHIFT3X4).toString();
CODECPHASESHIFT3X4 可以选择


配置qt
http://blog.csdn.net/liang19890820/article/details/53931813
http://blog.csdn.net/chinabinlang/article/details/31490915

配置opencv
C++ -->常规-->附加包含目录

 
=======================================================================================
.
..
..\..
..\..\..\vcglib
..\external\glew-1.7.0\include
..\external\jhead-2.95
F:\opencv\2.4.11\include
F:\opencv\2.4.11\include\opencv
F:\opencv\2.4.11\include\opencv2
F:\opencv\uEye\include
$(QTDIR)\include
$(QTDIR)\include\QtOpenGL
$(QTDIR)\include\QtWidgets
$(QTDIR)\include\QtGui
$(QTDIR)\include\QtANGLE
$(QTDIR)\include\QtXml
$(QTDIR)\include\QtXmlPatterns
$(QTDIR)\include\QtNetwork
$(QTDIR)\include\QtScript
$(QTDIR)\include\QtTest
$(QTDIR)\include\QtCore
release
$(QTDIR)\mkspecs\win32-msvc2015
.\GeneratedFiles
=======================================================================================
.
..
..\..
..\..\..\vcglib
..\external\glew-1.7.0\include
..\external\jhead-2.95
F:\opencv\2.4.11\include
F:\opencv\2.4.11\include\opencv
F:\opencv\2.4.11\include\opencv2
F:\opencv\uEye\include
 
E:\QT\Qt5.7.0\5.7\msvc2015_64\include
E:\QT\Qt5.7.0\5.7\msvc2015_64\include\QtOpenGL
E:\QT\Qt5.7.0\5.7\msvc2015_64\include\QtWidgets
E:\QT\Qt5.7.0\5.7\msvc2015_64\include\QtGui
E:\QT\Qt5.7.0\5.7\msvc2015_64\include\QtANGLE
E:\QT\Qt5.7.0\5.7\msvc2015_64\include\QtXml
E:\QT\Qt5.7.0\5.7\msvc2015_64\include\QtXmlPatterns
E:\QT\Qt5.7.0\5.7\msvc2015_64\include\QtNetwork
E:\QT\Qt5.7.0\5.7\msvc2015_64\include\QtScript
E:\QT\Qt5.7.0\5.7\msvc2015_64\include\QtTest
E:\QT\Qt5.7.0\5.7\msvc2015_64\include\QtCore
release
E:\QT\Qt5.7.0\5.7\msvc2015_64\mkspecs\win32-msvc2015
.\GeneratedFiles
%(AdditionalIncludeDirectories)
--------------------------------------------------------------------------------------------------------------------------------
链接器 -->输入-->附加依赖项
 
【附加依赖项】
..\external\lib\win32-msvc2015\jhead.lib
..\distrib\common.lib
opengl32.lib
GLU32.lib
F:\opencv\2.4.11\lib\opencv_core2411.lib
F:\opencv\2.4.11\lib\opencv_highgui2411.lib
F:\opencv\2.4.11\lib\opencv_imgproc2411.lib
F:\opencv\2.4.11\lib\opencv_calib3d2411.lib
F:\opencv\uEye\Lib\uEye_api_64.lib
F:\opencv\uEye\Lib\uEye_tools_64.lib
$(QTDIR)\lib\Qt5OpenGL.lib
$(QTDIR)\lib\Qt5Widgets.lib
$(QTDIR)\lib\Qt5Gui.lib
$(QTDIR)\lib\Qt5Xml.lib
$(QTDIR)\lib\Qt5XmlPatterns.lib
$(QTDIR)\lib\Qt5Network.lib
$(QTDIR)\lib\Qt5Script.lib
$(QTDIR)\lib\Qt5Test.lib
$(QTDIR)\lib\Qt5Core.lib
 
【计算的值】
..\external\lib\win32-msvc2015\jhead.lib
..\distrib\common.lib
opengl32.lib
GLU32.lib
F:\opencv\2.4.11\lib\opencv_core2411.lib
F:\opencv\2.4.11\lib\opencv_highgui2411.lib
F:\opencv\2.4.11\lib\opencv_imgproc2411.lib
F:\opencv\2.4.11\lib\opencv_calib3d2411.lib
F:\opencv\uEye\Lib\uEye_api_64.lib
F:\opencv\uEye\Lib\uEye_tools_64.lib
E:\QT\Qt5.7.0\5.7\msvc2015_64\lib\Qt5OpenGL.lib
E:\QT\Qt5.7.0\5.7\msvc2015_64\lib\Qt5Widgets.lib
E:\QT\Qt5.7.0\5.7\msvc2015_64\lib\Qt5Gui.lib
E:\QT\Qt5.7.0\5.7\msvc2015_64\lib\Qt5Xml.lib
E:\QT\Qt5.7.0\5.7\msvc2015_64\lib\Qt5XmlPatterns.lib
E:\QT\Qt5.7.0\5.7\msvc2015_64\lib\Qt5Network.lib
E:\QT\Qt5.7.0\5.7\msvc2015_64\lib\Qt5Script.lib
E:\QT\Qt5.7.0\5.7\msvc2015_64\lib\Qt5Test.lib
E:\QT\Qt5.7.0\5.7\msvc2015_64\lib\Qt5Core.lib
%(AdditionalDependencies)

