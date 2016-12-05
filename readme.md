# Instruction

用于CPP工程读取配置文件的一个小工具。

（由于Visual Studio限制，源码文件使用GBK编码。如果查看中文字符出现乱码，请尝试改变浏览编码方式。）

[TOC]

### Features

- 行为单位。键以及与其对应的所有值应在同一**定义行**内，使用`=`连接。不存在`=`的行将自动视为**全注释行**。
- 支持定义行注释。以`#`作为注释符，每一行`#`后的内容将被忽略。转义方法：`\#`
- 支持int、double、string等具有`>>`运算符重载的类型。支持数组赋值。
- 可以添加格式空白符。

### Usage

大象装进冰箱只需三步：

1. 实例化一个`Config`类的对象。
2. 调用`loadConfigFile`函数加载配置文件。
3. 使用`read`读取需要的变量。


当然，比必须在你的文件里include头文件*Config.h*。

#### 具体步骤举例：

在此实例化一个名为`conf`的对象：

```cpp
Config conf();
```

或者直接在构造时就指定配置文件名：

```cpp
Config conf("example.cfg");
```

接着就可以使用这个工具了。调用加载函数（如果构造的时候指定了文件，那不需要重新指定）：

```cpp
conf.loadConfigFile("example.cfg");
//OR: conf.loadConfigFile();
```

如果打开文件失败，函数返回`false`。因此一个合理的用法是：

```cpp
if (!conf.loadConfigFile())
{
	cerr << "Error: Can not open configuration file." << endl;
	return 1;
}
```

加载成功后就可以读取你需要的变量了。例如定义了一个int类型的变量`var`用来存储某个参数，在配置文件中的键值为`varINT`，那么读取方式为：

```cpp
conf.read("varINT", &var);
```

应当注意传入的是定义好的变量的指针。

配置文件中如果不存在这个键值会抛出异常，即默认情况下使用`read`读取的变量都要求是必需的。但有时候我们在程序中已经设定了默认值，并希望如果配置文件中没有定义的话自动跳过即可。那么，可以在函数参数最后声明`NOT_NECESSARY`，这样的话如果找不到键值，函数只是返回`false`但不会抛出异常。

```cpp
conf.read("varINT", &var, NOT_NECESSARY);
```

绝大部分流类型中重载了`>>`运算符的类型都是可以使用的。  

也可以利用配置文件为一个数组赋值。这时候需要显式说明该参数是`NOT_NECESSARY`的还是`NECESSARY`的，并指定数组的长度。例如：

```cpp
int arr[3]; // key = arrINT
conf.read("arrINT", arrInt, NECESSARY, 3);
```

注意只传入数组名就可以了。数组名本身就是指针。  

总的来说，任何未声明或显式声明为`NECESSARY`的读取操作如果未能在文件中找到相应键值，都会抛出异常。如果是`NOT_NECESSARY`的，只是会根据情况返回`true`或`false`。之所以使用抛异常的方式，是为了使用简便，可以将多个读取操作并列写在一起，查看和修改都更方便。因此一个推荐的用法：

```cpp
try
{           //   key         var/arr     requirement   size
	conf.read("varInt1",    &varInt1,    NECESSARY         );
	conf.read("varInt2",    &varInt2                       );
	conf.read("varDouble1", &varDouble1                    );
	conf.read("varDouble2", &varDouble2, NOT_NECESSARY     );
	conf.read("varString",  &varString                     );
	conf.read("arrInt",     arrInt,      NECESSARY,     3  );
	conf.read("arrDouble",  arrDouble,   NECESSARY,     4  );
}
catch (const runtime_error error)
{
	cerr << error.what() << endl;
	return 1;
}
```

#### 文件样例：

接口使用示例存储在*example.cpp*文件中，配置文件示例为*example.cfg*文件。直接在自己的`main`函数中调用cpp文件中的`exampleMain`函数即可运行示例。