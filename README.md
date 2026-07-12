```
  __    __  _                  __  __  
 / /   / /_(_)__  __ _____ ___/ /  \ \ 
< <   / __/ / _ \/ // / -_) _  /    > >
 \_\  \__/_/_//_/\_, /\__/\_,_/    /_/ 
                /___/
```
# TinyEd - The Smallest Terminal Text Editor for Windows

A ultra-minimal, interactive, fullscreen terminal text editor written in C (~1.2 KB source code) for Windows terminal environments. It runs natively, doesn't require any dependency (no python, no heavy curses libraries), and uses Windows `conio.h` to keep binary and source code size down.

## Features
- **Visual Interface**: Shows the filename and save status (`[Saved]` / `[Modified]`) at the top, and displays a reverse-video highlight cursor (`\x1b[7m`).
- **Interactive File Open & Save**: Open and Save files directly inside the editor.
- **Micro Footprint**: Written in ~45 lines of simple C.

## Keyboard Shortcuts
- `Ctrl + S`: Prompt for target path and Save the file.
- `Ctrl + O`: Prompt for file path and Open the file.
- `Left/Right Arrow Keys`: Move cursor.
- `Backspace`: Delete character.
- `ESC`: Exit editor.

## Getting Started
To compile the editor yourself, use any standard C compiler (e.g., GCC):
```powershell
gcc -O3 tinyed.c -o tinyed.exe
```

Run the editor:
```powershell
# Opens/Creates a file
.\tinyed.exe filename.txt

# Or run it with no arguments to start with "untitled.txt"
.\tinyed.exe
```
