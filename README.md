# BF

 Brainf*ck interpreter written in modern C++. This implementation uses tape with 3000 cells on stack. Very small interpreter for a very small language. It's a trivial implementation for a challenge.

**CHALLENGE: To write the interpreter as small in size as possible**.

The original was only `296B` we've to get close to it. With every update I'll try to decrease the size. The end goal is to eventually write it in x86-64 Assembly. For the time being check out my repo for AVX2 SIMD examples for linear algebra : [Here](https://github.com/ArcShahi/ASM-x86-64)

Anyways here's how to use it :

```powershell
# Copy the bf++.cpp in your favorite IDE and just compile with -std=c++20 or above
# I've named the interpreter : "bf++" you can name it whatever you want then run like this
bf++ hello.bf

# Binary mode for raw IO
bf++ hello.bf -b
```

It's current size is ~`30KB`, which is a LOT!!!


## Interpreter implementation details

The Official site : https://brainfuck.org/

Implemented according to : **The Epistle to the Implementors.**

1.  For the sake of consistency, this brainfuck implementations as it's default behavior, ensures both that brainfuck programs receive only a ten when an end-of-line is input, and that an end-of-line is output when a brainfuck program outputs a ten. It's a full-featured implementation that also provides an option to turn off any such filtration, for programs that do binary i/o by passing `-b` flag in command line when invoking the `bf++` interpreter.
2.  The end of input, or end-of-file (EOF) command sets the cell at the pointer to 0.
3.  Characters in brainfuck source other than the commands `+,-.<>[]` are comments, not errors; implementation ignores it.
4.  The tape arrays has 3000 cells, pointer starts at the left end. The > and < commands need not be equally numerous within balanced [].
5.  i/o is done during execution, so interactive programs work.
6.  Matching `[]` loop entry-exit lookup before execution is fastest and is used.


## Known Issues
- Doesn't check for arrow pointer for out of bounds

----



## AI Policy
**AI usage for code generation and documentation is forbidden for this project.**
> Shahi (*prefers natural stupidity over artificial intelligence*
