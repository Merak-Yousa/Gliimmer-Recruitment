# EASY-1 C语言入门

>## part1 了解C语言配置文件

### 1.GCC和MinGW

- ***GCC***:一种编译器,GNU工具,能将人写出的程序经过预处理,编译,汇编和链接翻译成机器码(二进制);
- ***MinGW***:也是一种GNU工具,与GCC不同的是,GCC只能在Linux上运行,MinGW是它在Windows平台的移植版本.

### 2.三种.json文件

(依本人理解,VScode本体只是可以输入文本,而这三个文件负责帮助配置编程环境.)

- ***c_cpp_properties.json***:C/C++配置.指定了编译器路径和包含路径;
- ***launch.json***:调试配置.用于配置调试器(常见的有GDB等).可以决定使用的终端是外置还是内置,所以成为最常更改的一个;
- ***task.json***:任务配置.用于定义编译任务.它将GCC集成到VScode中,实现了代码到程序的编译.

### 3.插件的作用

VScode原生只提供文本编辑功能,依据网上的资料,安装C语言插件可以引入LSP)            也就是使VScode可以理解C语言

如此多的插件,使VScode由本质记事本变成编程语言的强大集成开发环境(IDE).

### 4.launch.json文件的更改与hello world

![alt text](外.png)
![alt text](内.png)
