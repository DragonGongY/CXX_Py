#include <iostream>
#include "Python.h"
#include "numpy/ndarrayobject.h"
#include "utils.h"
#include <string>

using namespace std;
using namespace cv;

int main() {
    std::cout << "Hello, World!" << std::endl;
    Py_SetPythonHome(L"/home/dp/miniconda3/envs/torch1.6");
    Py_Initialize();
    PyRun_SimpleString("print('hello python c++')");

    Mat src = imread("/media/dp/LinuxData/DataSets/GuanGan/1.jpg");
    PyObject * pRet = TransImgToPython(src, "", "");



    return 0;
}
