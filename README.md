# hotmilk
A rudimentary, esorteric text editor with an 'append-only' model, where escape sequences are typed manually in order to reflect the corresponding changes in the output file.

Supported escape sequences:

- `\t` - tab
- `\n` - newline
- `\b` - backspace

Some hotmilk-specific control sequences are / were (intended to be) implemented in this text editor in order to be able to interact with the output file, such as:

- `^s` - save (to existing file)
- `^x` - exit

## Example:

A line such as:

> #include <stdio.h>\n\nint main()\n{\n\tprintf("%s\\n", "Hello, World!");\n\t\n\treturn 0;\n}^s^x

\- would output the following in the output file:

```c
#include <stdio.h>

int main()
{
    printf("%s\n", "Hello, World!");
    return 0;
}
```

## Note:

This project is unfinished, lacks certain features and was made to be a proof of concept.
