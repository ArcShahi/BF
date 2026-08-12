# BF

 Brainf*ck interpreter written in modern C++. This implementation uses tape with 3000 cells on stack. Very small interpreter for a very small language. It's a trivial implementation for a challenge.

**CHALLENGE: To write the interpreter as small in size as possible**.

The original was only `296B` we've to get close to it. With every update I'll try to decrease the size. The end goal is to eventually write it in x86-64 Assembly. For the time being check out my repo for AVX2 SIMD examples for linear algebra : [Here](https://github.com/ArcShahi/ASM-x86-64)

Anyways here's how to use it :

```powershell
# Copy the bf++.cpp in your favorite IDE and just compile with -std=c++20 or above
# I've named the interpreter : "bf++" you can name it whatever you want then run like this
bf++ hello.bf
```

It's current size is ~`30KB`, which is a LOT!!!

## Known Issues
- Doesn't check for arrow pointer for out of bounds

----

The Official site : https://brainfuck.org/

## AI Policy
**AI usage for code generation and documentation is forbidden for this project.**
> Shahi (*prefers natural stupidity over artificial intelligence*
