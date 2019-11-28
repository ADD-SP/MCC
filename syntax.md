## 约定：

+ 大写字母如$A,B,C$等均为非终结字符；
+ 小写字母、四则运算符和标点符号均为终结符

## 算术表达式语法

|                   产生式                   | 动作 |
| :----------------------------------------: | :--: |
|            $E \rightarrow TE'$             |      |
| $E' \rightarrow +TE' | -TE' | \varepsilon$ |      |
|            $T \rightarrow FT'$             |      |
| $T' \rightarrow *FT' | /FT' | \varepsilon$ |      |
|     $F \rightarrow (E) | number | Id$      |      |

