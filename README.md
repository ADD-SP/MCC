# MCC

一个玩具编译器前端，实现一个C的子集，并支持将源代码转为三地址码，学习编译原理时的练手程序；

# 如何构建

使用VS2019/VS2017打开项目根目录的MCC.sln文件后直接编译即可

# 如何使用

使用命令行传入参数，参数为源代码文件名（包含路径），如果执行成功，则会输出成功提示并在运行目录创建“out.txt”文件，内容为三地址码，如果失败则程序退出代码为出错代码所在行，如果返回值小于0则代表触发了程序的BUG或者使用了不受支持的语法；

# 例子

1.c：
```c
/*
    这是一个求[1,10]范围内所有素数的程序
*/
bool check(int num)
{
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
        else
        {
            /* 该句用来演示else和continue的翻译，不影响代码功能 */
            continue;
        }
    }
    return true;
}

int main()
{
    int a[10], index = 0;
    for (int i = 2; i <= 10; i = i + 1)
    {
        if (check(i))
        {
            a[index++] = i;
        }
    }
    return 0;
}

```

运行命令
```
./MCC.exe 1.c
```

命令行输出
```
success！
```
打开运行目录下的out.txt文件
```
check:
i = 2
@label_1:
@var_4 = i < num
CNJMP @var_4 @label_3
@var_7 = num % i
@var_8 = @var_7 == 0
CNJMP @var_8 @label_4
RET false
JMP @label_5
@label_4:
JMP @label_1
@label_5:
@var_5 = i
@var_6 = i + 1
i = @var_6
JMP @label_1
@label_3:
RET true
main:
i = 2
@label_6:
@var_13 = i <= 10
CNJMP @var_13 @label_8
@var_15 = check(i)
CNJMP @var_15 @label_9
@var_16 = index
@var_17 = index + 1
index = @var_17
a[@var_16] = i
JMP @label_10
@label_9:
@label_10:
@var_14 = i + 1
i = @var_14
JMP @label_6
@label_8:
RET 0

```

# 必要的说明

+ 文法见项目根目录的syntax.xlsx文件；

+ LL(1)分析表见项目根目录的select.xlsx文件；

## 已经支持的语法（一小部分C的语法）

+ 函数和变量声明；

+ 数组的声明和使用；

+ 复杂的表达式，例如1+2-3*4/(5 + a[0]) && !true；

+ 支持的关键字包括int, float, bool, for, if, else, while, return, break, continue;

+ 支持每个{}内都是一个变量作用域，即在一个{}内声明的变量会在外围失效；

+ 支持在使用变量和函数时检查是否声明过；

## 部分三地址码含义说明

+ RET \<arg>：函数返回语句，后面可以紧跟着一个右值（即可以放到赋值符号右边的值）作为返回值，也可以为空代表无返回值；

+ CNJMP bool label：如果bool为false则跳转到对应的label处执行，反之则继续执行下一行；

+ CJMP bool label：如果bool为true则跳转到对应的label处执行，反之则继续执行下一行；

+ JMP label：无条件跳转到label处执行；