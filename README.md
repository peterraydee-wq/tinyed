```
  __    __  _           ____   __  __  
 / /   / /_(_)__  __ __/ __/__/ /  \ \ 
< <   / __/ / _ \/ // / _// _  /    > >
 \_\  \__/_/_//_/\_, /___/\_,_/    /_/ 
                /___/                  
```
# < tinyEd > - the smallest terminal text editor for windows & linux (in dev.)
![size](https://img.shields.io/badge/size-2.75MB-blue)

an ultra-minimal, interactive, fullscreen terminal text editor written in C (~1.2 KB source code) for windows terminal environments. it runs natively, doesn't require _any_ dependency (no python, no heavy curses libraries), and uses windows `conio.h` to keep binary and source code size down.

### note
if you want the minimal version _(1.67 KB)_ its release 1.0.0.

## features
- **visual interface**: shows the filename and save status (`[Saved]` / `[Modified]`) at the top, and displays a reverse-video highlight cursor (`\x1b[7m`).
- **interactive file open & save**: open and Save files directly inside the editor.
- **small footprint**: written in ~45 lines of simple C.

## keyboard shortcuts
- `ctrl + s`: prompt for target path and Save the file.
- `ctrl + o`: prompt for file path and Open the file.
- `left/right arrow keys`: move cursor.
- `backspace`: delete character.
- `esc`: exit editor.

## getting started
to compile the editor yourself, use any standard C compiler (e.g., GCC):
```powershell
gcc -O3 tinyed.c -o tinyed.exe
```

run the editor:
```powershell
# Opens/Creates a file
.\tinyed.exe filename.txt

# Or run it with no arguments to start with "untitled.txt"
.\tinyed.exe
```

## important note!
_this was made with artificial intelligence._
