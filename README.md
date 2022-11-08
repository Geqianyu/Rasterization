[result1]: ./result/%E5%88%9D%E6%AD%A5%E5%8A%A0%E8%BD%BD.PNG

[result2]: ./result/%E5%B7%A6%E9%94%AE%E8%B0%83%E6%95%B4%E8%A7%92%E5%BA%A6.PNG


# Rasterization
## 配置
- 操作系统: win 10
- IDE: vs2022
- 第三方库: stb_image.h, 用于加载纹理
- 界面显示: 利用 WINAPI
- 多线程: 利用 omp
- 模型: 位于文件夹 obj 中

## 说明
- 本项目完成一个软光栅化器，用C++完成
- 按住鼠标左键可以旋转模型，按住鼠标右键可以拖拽模型
- 项目采用 blinphong 光照模型
- 可直接双击 x64 文件夹下的 Rasterization.exe 运行程序

<center>1.光栅化结果</center>

![光栅化结果][result1]

<center>2.调整角度后的结果</center>

![调整角度后的结果][result2]
