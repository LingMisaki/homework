# This is the homework No.3
## 运行方式
## problem1
cmakelists.txt中有三个excutable  
直接运行即可  
代码文件  
main.cpp -> problem 1  
main2.cpp -> problem 2   
main3.cpp -> problem 4  
## 思路
### problem 1
直接调用solvepnp即可   
注意：solvePnP求解的r和t是将世界坐标系下的点变换到相机坐标系所需要的旋转和平移，实际上也是相机在世界坐标系下的位姿，即R*Pw + T = Pc。  
    r和t不是图像2D坐标和物体3D坐标之间的一个关系，而是相机坐标系（3D）和世界坐标系（3D）之间的关系。  
再用陀螺仪的四元数将相机坐标系中的物体坐标转换到陀螺仪坐标系中  

### problem 2
直接套用卡尔曼滤波的模板了，看了下曲线我感觉比较符合线性  
### problem 4
直接用opencv的标定函数,参考了第三次教程的程序  
踩了个坑，string的.append会更改原字符串，我当成加号来用了  



    