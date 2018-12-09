# 程序功能

- [x] 代码中**已实现**了C语言代码的简单词法分析及语法分析，能够识别基本的词法错误和语法错误，例如：a[..]属于对数组声明的错误等。
- [x] 代码中**已实现**的词法分析部分采用了GNU Flex方法，语法分析部分采用了GNU Bison方法并且自行设计了多叉树结构。
- [x] 代码中**已实现**的符号表采用了基于十字链表和Open hashing的散列表结构。
- [x] 代码中**已实现**的语义分析部分采用深度优先搜索的方法遍历语法树，并且查填表以找到错误类型。
- [x] 代码中**已实现**了对C语言代码的语义分析，能够输出符合C语言文法语法但是并不符合C语言语义要求的多种错误类型(**包括所有必做和选做要求**)。
- [x] 代码中**已实现**中间代码生成所需要的数据结构。
- [x] 代码中**已实现**对正确通过词法、语法及语义分析的C语言代码进行中间代码的生成。(**完成所有必做和选做要求**)
- [x] 代码中改进或实现了实验三的以下假设或者功能：**(亮点)**  
    1. 改进假设1，支持八进制和十六进制数(转为十进制数进行计算)。
    2. 改进假设4，支持变量作用域。
    3. 改进假设6，支持函数声明。
    4. 改进要求3.2，高维数组也允许作为参数。此外，结构体和数组可以互相嵌套。
    5. 优化控制流语句，尽可能少生成GOTO和LABEL而使用fall方法。
    6. 优化常数表达式，可计算的常数表达式会被直接计算好。

## 数据结构

1. 操作数的数据结构如下，``OP_TYPE``表示操作数类型，是一个枚举类型，``MODIFIER_TYPE``表示操作数前的修饰符，同样也是一个枚举类型。最后的匿名联合体用于存储变量或临时变量的标号或者立即数的值。

```cpp  
        typedef struct IROperand_ {
            /* The type of operands */
            OP_TYPE kind;
            /* Whether the operand is only a varibale or an 
             * address or the dereferenced 
             */
            MODIFIER_TYPE modifier;
            /* Identify different temporary variables */
            union {
                int var_label_num;
                int value_int;
                float value_float;
                char* var_func_name;
            };
        } IROperand;
```

2. 中间代码的数据结构如下，采用了线性IR的结构，并且使用了双向链表。其中``IR_TYPE``用于表示中间代码的类型，是一个枚举类型。紧接着的一个大的匿名联合体用于存储不同类型中间代码所需要的操作数。最后的匿名联合体专门用于``IR_RELOP``和``IR_DEC``两种类型的中间代码的表示。

```cpp
        typedef struct IRCode_ {
            /* The type of a piece of intermediate 
             * representation 
             */
            IR_TYPE kind;
            /* For result or temporary variables */
            union {
                struct {
                    IROperand* dst;
                    union {
                        struct {
                            IROperand* src1;
                            IROperand* src2;
                        };
                    IROperand* merged_src;
                    };
                };
                struct { 
                    // 1-operand
                    IROperand* src;
                };
                struct { 
                    // for RETURN only
                    IROperand* rtn;
                    IROperand* func;
                };
            };
            /* The type of relop operation */
            union {
                RELOP_TYPE relop;
                int declared_size;
                bool none_flag;
            };
            /* A bi-direction list */
            struct IRCode_* prev;
            struct IRCode_* next;
        } IRCode;

```

## 实现思路

1. 首先是将``Semantic``与``Translate``分开来处理，重新构造了一个专门用于生成中间代码的模块，其中两者都调用``SymbolTable``模块，在两者调用中间加入了重置``SymbolTable``模块的方法，以避免两者相互影响。

2. 主要实现思路是完成对不同表达式和语句的翻译，尤其是对于表达式中出现的函数、结构体和数组的翻译，还有就是对条件表达式的翻译。采用的方法是实现了下述的两个方法。将所有的数组、函数和结构体单独放入``xxx_Address()``的方法中进行处理，并且所有的赋值语句（左值）都以将值写入左值语句的地址中的方法来实现，这样统一了平凡变量与函数、数组和结构体的赋值方法。对于条件表达式则交给``xxx_Condition()``的方法来处理，传入``label_false``和``label_true``用于标记语句的转到位置。

```cpp
    /* Deepth-first traversal for Exp branch, only aiming at CONDITION Expression */
    Type* Translate_DFS_Expression_Condition(TreeNode* cur_root, IROperand* label_true, IROperand* label_false);

    /* Deepth-first traversal for Exp branch, only aiming at LEFT_VALUE Expression */
    Type* Translate_DFS_Expression_Address(TreeNode* cur_root, IROperand* operand);

```

## 实验难点(TODO)

## 解决方案(TODO)

## 编译及运行方法

首先压缩包解压后得到的文件夹``Lab3``,``Test``文件夹中存储了xx个测试用例，``Code``文件夹存储了所有代码文件，``results.txt``文件存储了23个测试用例的测试结果（包括错误提示的输出和无错的空输出）。

- 如果想要直接编译运行，则在shell命令行执行``./run.sh``，则会直接编译并且对``Test``文件夹下的用例进行测试，输出的结果按序存储在``results.txt``中。
- 如果仅仅想要编译，则进入``Code``文件夹执行``make parser``，则会重新编译并在上层目录``Lab3``得到可执行文件``parser``。
- 如果想要对某一个测试用例进行测试，则在``Lab3``目录下执行``./parser xxx``,其中``xxx``代表将要被测试的用例。
