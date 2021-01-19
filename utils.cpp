//
// Created by dp on 12/1/20.
//

#include "utils.h"
using namespace std;
using namespace cv;

double ConvertPythonObjectToDouble(PyObject *obj)
{
    double result = 0;
    PyArg_Parse(obj, "d", &result);
    return result;
}

int ConvertPythonObjectToInt(PyObject *obj)
{
    int result = 0;
    PyArg_Parse(obj, "i", &result);
    return result;
}


PyObject * TransImgToPython(Mat img, string recPyName, string funName)
{
    Py_SetPythonHome(L"/home/dp/miniconda3/envs/torch1.6");
    Py_Initialize();
    import_array();
    if(!Py_IsInitialized())
    {
        cout << "Initialized Failed ." << endl;
        Py_Finalize();
    }

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/media/dp/LinuxData/Algorithms/mmdetection-2.5.0_cxx/demo')");

    PyObject * pModule = PyImport_ImportModule("mytest");

    int m, n;
    n = img.cols * 3;
    m = img.rows;
    unsigned char * data = (unsigned char *)malloc(sizeof(unsigned char ) * m * n);
    int p = 0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            data[p] = img.at<unsigned char>(i, j);
            p++;
        }
    }
    npy_intp Dims[2] = {m, n};
    PyObject * pyArray = PyArray_SimpleNewFromData(2, Dims, NPY_UBYTE, data);
    PyObject * pDict = PyModule_GetDict(pModule);

    PyObject * args = PyTuple_New(3);
    PyObject * args1 = Py_BuildValue("i", img.cols);
    PyObject * args2 = Py_BuildValue("i", img.rows);
    PyTuple_SetItem(args, 0, pyArray);
    PyTuple_SetItem(args, 1, args1);
    PyTuple_SetItem(args, 2, args2);

    PyObject * pFunFive = PyDict_GetItemString(pDict, "detect");
    PyObject * pRet = PyObject_CallObject(pFunFive, args);

    return pRet;
}
vector<DataFormat> ParsePythonReturnedList(PyObject * ret)
{
    map<int, string> labels = {
            {1, "Defection"},
            {2, "MaL"},
            {3, "AoK"},
            {4, "ShW"},
            {5, "SeC"},
    };
    vector<DataFormat> results;
    if(PyList_Check(ret))
    {
        int listSize = PyList_Size(ret);
        for(int i=0;i<listSize;i++)
        {
            PyArrayObject * currentBoxItemList = (PyArrayObject*)PyList_GetItem(ret,i);
            if(PyList_Check(currentBoxItemList))
            {
                auto currentSize = PyList_Size((PyObject *)currentBoxItemList);
                if(currentSize < 6) {continue;}
                PyObject * p0 = PyList_GetItem((PyObject*)currentBoxItemList, 0);
                PyObject * p1 = PyList_GetItem((PyObject*)currentBoxItemList, 1);
                PyObject * p2 = PyList_GetItem((PyObject*)currentBoxItemList, 2);
                PyObject * p3 = PyList_GetItem((PyObject*)currentBoxItemList, 3);
                PyObject * p4 = PyList_GetItem((PyObject*)currentBoxItemList, 4);
                PyObject * p5 = PyList_GetItem((PyObject*)currentBoxItemList, 5);

                auto d0 = ConvertPythonObjectToDouble(p0);
                auto d1 = ConvertPythonObjectToDouble(p1);
                auto d2 = ConvertPythonObjectToDouble(p2);
                auto d3 = ConvertPythonObjectToDouble(p3);
                auto d4 = ConvertPythonObjectToDouble(p4);
                auto d5 = ConvertPythonObjectToInt(p5);
                if(d0==d1==d2==d3==d4) continue;
                DataFormat dataFormat;
                dataFormat.x0 = d0;
                dataFormat.y0 = d1;
                dataFormat.x1 = d2;
                dataFormat.y1 = d3;
                dataFormat.score = d4;
                dataFormat.name = labels.at(d5);
                results.push_back(dataFormat);
            }
        }
    }
    return results;
}

void display_result(vector<DataFormat> results)
{
    for(int i=0;i<results.size();++i)
    {
        cout <<"results:" << results[i].name << endl;
    }
}

void show_results(Mat& img, vector<DataFormat> results)
{
    for(int i=0;i<results.size();i++)
    {
        rectangle(img,
                  Rect(results[i].x0, results[i].y0, results[i].x1-results[i].x0, results[i].y1-results[i].y0),
                  Scalar(0,255,0),
                  3);
    }
}