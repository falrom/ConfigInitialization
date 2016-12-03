# Instruction

This is a tool coded by CPP for loading parameters from configuration files.

### Features

- 支持注释。以`#`作为注释符，每一行`#`后的内容将被忽略。转义方法：`\#`
- 支持int、double、string等具有`>>`运算符重载的类型。支持数组赋值。
- 可以添加格式空白符。



接口使用示例存储在`example.cpp`文件中。直接在自己的`main`函数中调用该文件中的`exampleMain`函数即可运行示例。