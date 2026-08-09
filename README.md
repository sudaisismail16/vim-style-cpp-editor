# Vim-Style Text Editor (C++)

A terminal-based text editor built from scratch in C++, inspired by Vim's modal editing philosophy. Implements a full document object model — Document → Chapter → Section → Paragraph → Line — with a custom string implementation and no reliance on the STL `std::string`.

## Features

### Modal Editing
- **Normal Mode** (default) — navigation and text manipulation
- **Insert Mode** — direct text entry, like a standard text editor
- **Command-Line Mode** — execute file and search commands

### Navigation
`h` `j` `k` `l` movement, `w` / `b` word jumps, `0` / `$` line start/end, `gg` / `G` file start/end, `Ctrl+d` / `Ctrl+u` half-page scroll

### Editing
- Delete: `dd`, `D`, `x`
- Yank & paste: `yy`, `p`, `P`
- Undo / redo: `u`, `Ctrl+r`
- Repeat last command: `.`
- Toggle case: `~`

### Insert Mode
Selection, copy/cut/paste (`Ctrl+C/X/V`), indent/unindent (`Tab` / `Shift+Tab`), standard backspace/delete

### Command-Line Mode
- File ops: `:w`, `:q`, `:wq`, `:q!`
- Search: `:/pattern`, `:?pattern`, `:n`, `:N`
- Find & replace: `:%s/old/new/g`
- Line numbers: `:set number` / `:set nonumber`

### Custom Console UI
Console dimensions, font, and color are configured at startup for a cleaner terminal presentation.

## Architecture

The document model is a strict containment hierarchy, each level owning a collection of the level below it:

```
Document
 └── Chapter
      └── Section
           └── Paragraph
                └── Line
```

`Editor` drives the mode state machine (Normal / Insert / Command) and dispatches keystrokes to the appropriate document operations.

A custom `MyString` class replaces `std::string` throughout — implemented from scratch (construction, copying, concatenation, comparison, etc.) per project constraints.

## Project Structure

```
Header Files/
  Chapter.h
  Document.h
  Editor.h
  Line.h
  MyString.h
  Paragraph.h
  Section.h

Source Files/
  BSCS25024_Project.cpp   # entry point
  Chapter.cpp
  Document.cpp
  Editor.cpp
  Line.cpp
  MyString.cpp
  Paragraph.cpp
  Section.cpp
```

## Build

Compile all source files together with any C++ compiler supporting C++11 or later, e.g.:


## Notes

Built as a course project exploring object-oriented design, custom data structure implementation, and terminal-based UI/state management in C++.
