//
// Created by dp on 12/1/20.
//

#ifndef TEST_01_UTILS_H
#define TEST_01_UTILS_H

#include "Python.h"
#include "numpy/ndarrayobject.h"
#include "opencv2/opencv.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct DataFormat
{
    double x0;
    double y0;
    double x1;
    double y1;
    double score;
    string name;
};

//void ParsePythonReturnedList(PyObject * pRet);
double ConvertPythonObjectToDouble(PyObject *obj);
int ConvertPythonObjectToInt(PyObject *obj);
PyObject * TransImgToPython(cv::Mat img, string recPyName, string funName);
vector<DataFormat> ParsePythonReturnedList(PyObject * ret);
void DisplayVector(vector<DataFormat> results);
void show_results(cv::Mat& img, vector<DataFormat> results);

#endif //TEST_01_UTILS_H
