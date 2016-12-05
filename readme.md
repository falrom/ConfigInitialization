# Instruction

This is a tool coded by CPP for loading parameters from configuration files.

（由于Visual Studio限制，源码文件使用GBK编码。）



### Features

- 单行为单位。键以及与其对应的所有值应在同一**定义行**内，使用`=`连接。不存在`=`的行将自动视为全**注释行**。
- 支持定义行注释。以`#`作为注释符，每一行`#`后的内容将被忽略。转义方法：`\#`
- 支持int、double、string等具有`>>`运算符重载的类型。支持数组赋值。
- 可以添加格式空白符。




### Rules



配置文件样例：


接口使用示例存储在`example.cpp`文件中。直接在自己的`main`函数中调用该文件中的`exampleMain`函数即可运行示例。