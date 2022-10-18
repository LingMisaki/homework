# This is the homework No.2
## 运行方式
## problem1
cmakelists.txt中有三个excutable  
直接运行即可  
代码文件  
main.cpp -> problem 1  
main2.cpp -> problem 2  
main3.cpp -> problem 3  
## 思路
### problem 1
用windows的画图找车牌的四个点就行了（左下角会显示坐标），然后直接套函数    
ps：车牌大小440*140（来自百度）  
### problem 2
原理应该就是pdf中的那个红色的大式子  
converter.block(0, 0, 3, 3) = rot_c_to_w.transpose().cast<double>();  
converter.block(0, 3, 3, 1) =-rot_c_to_w.transpose().cast<double>() * cam_w;  
这两行由于我对原理理解不深，自己写时候没有转置，平移量也没有这样处理，还有就是归一化不是特别懂，，导致输出很奇异  
踩了不少坑发现pdf里有程序可以参考   
### problem 3
我的思路是先老生长谈的轮廓提取，然后把点的z坐标随机一下，再用摄像机去拍照  
摄像机怎么平滑调整我想的办法是更改欧拉角，然后转旋转矩阵，这样比较平滑  
相机位置就很好改了  
这两个我都只写了线性改变的
为了好看circle时候的半径也随机一点  
世界坐标换算成相机坐标我写成了一个函数这样调用起来比较方便  


    