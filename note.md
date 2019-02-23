# Build a simple DB from scratch

## Chapter 1  build a simple REPL (read-execute-print loop)

1. `size_t` 与`ssize_t`

   `size_t` : 即`unsigned int`数据类型，定义在`<stdio.h>`,`<stdlib.h>`,`<stddef.h>`,`<string.h>`等文件中

   `ssize_t` : 与`size_t`相同，不过是`signed`类型

2. `<stdio.h>` 中 `getc`与`fgetc`的不同：前者可以以宏的形式实现，而后者不能（`f`理解为`function`），这样就有以下三点值得注意：

   - `getc`的参数不能是有副作用的表达式
   - `fgetc`是函数，所以可以将它的地址作为参数传递给其他函数
   - `fgetc`的时间开销可能更长，因为这是一个函数

3. 参数为指针时，在函数内部改变指针，则函数结束后指针地址不变，仍为初始时的地址，因此应该传递指针的指针。

## Chapter 2  simplest SQL compiler

1. 