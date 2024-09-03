# hotmilk
hotmilk ! a rudimentary text editor you never knew you never needed ! it is as close to being useless as a text editor can get , all the while still being perfectly functional !

every input in this text editor is manual ! you have to provide escape sequences for what you want the program to do , i.e.

this may be a line you input in hotmilk :

> #include <stdio.h>\n\nint main()\n{\n\tprintf("%s\\n", "Hello, World!");\n\t\n\treturn 0;\n}^S^X

this will be the output :

```c
#include <stdio.h>

int main()
{
    printf("%s\n", "Hello, World!");
    return 0;
}
```

followed by the program saving the changes to a file and exiting due to the hotmilk-specific sequences such as "^S" and "^X" !


hotmilk is provided "as-is" with no guarantees of efficiency , usability , or sanity preservation .

if you make a mistake at the start of your file , please use '\b' in order to delete everything you have written in order to get back to it and make changes .

thank you !
