cpp Tool

//compiler the lib

g++ -std=c++11 -shared -fPIC cpp_tool.cpp -o libcpptool.so

//Using lib in your project

g++ -std=c++11 yourcppfile.cpp -L../cppTool -lcpptool
