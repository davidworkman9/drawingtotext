dwgdxftotext: AutoCADConverter.cpp OutputFormatText.cpp OutputFormatConsole.cpp OutputFormatTypes.cpp InputFormatDXF.cpp GetInsertions.cpp InputFormatDWG.cpp
	g++ -ggdb -o dwgdxftotext OutputFormatText.cpp OutputFormatConsole.cpp OutputFormatTypes.cpp InputFormatDXF.cpp GetInsertions.cpp InputFormatDWG.cpp AutoCADConverter.cpp -ldxflib -I/usr/include/gdal -lredwg
