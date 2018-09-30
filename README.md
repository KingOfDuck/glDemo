# glDemo
使用OpenGL和Visual Studio创建的演示程序  
## 程序库
GL/GLES/EGL/GLX/WGL Loader-Generator: [glad](https://github.com/Dav1dde/glad)  
Graphics Library Framework :[glfw](http://www.glfw.org/)  
OpenGL Mathematics Library: [glm](https://glm.g-truc.net)  
Sean T. Barrett's single-file Image Library: [stb_image](https://github.com/nothings/stb)    

下载并安装，添加到系统包含目录或者自行创建包含目录
## 其它  
这个项目主要为了学习OpenGL，按照LearnOpenGL的教程实现了一些功能，学习过程中也在不断的整理和改进整个程序。
## 学习日志
>###2018/09/13   
>项目文件结构重组，添加[材质数据](http://devernay.free.fr/cours/opengl/materials.html)  
>###2018/09/14  
>平行光源
>###2018/09/20  
>新增光照管理，着色器管理  
>重写光照，着色器  
>多光源  
>###2018/09/30  
>模型加载  
>默认模型着色  
>资源管理器，目前管理贴图、着色器和模型数据  
>初步分离了绘图和数据模块，整合到Drawer中  
>下一阶段任务：补全log，注释，优化代码结构

