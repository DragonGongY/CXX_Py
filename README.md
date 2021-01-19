# 混编

## Introduction

此工程为了使用c++代码调用python代码而开发，由于目前深度学习开发均是用python语言，而模型部署或工程项目时，大多以c++为主。

## Function

采用OpenCV的c++　API读取Mat图像，然后将Mat传输给python端的numpy，并恢复图像为ndarray格式，然后送入AI模型进行推理。

推理完后将结果以列表的形式返回，传回到c++程序，然后解析推理结果，并在原始的Mat图上将结果显示出来
