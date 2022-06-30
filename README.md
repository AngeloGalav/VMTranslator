# VMTranslator

A simple VM HACK to Assembly HACK translator made for the Computer Architecture course. 
The code isn't the best, mainly because we were restricted to using only `std` libraries without the possibility of using syscalls or anything else.

## How to compile & use

The provided Makefile should help you with everything. 
The file to translate *must* have a `.vm` extension, or else it will cause an error. You can easily remove this feauture as it doesn't really adds anything besides some stupid errors. 

```bash
make
./VMTranslator Program.vm
```

The program was tested on Manjaro Linux. 