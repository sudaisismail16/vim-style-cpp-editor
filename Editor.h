#pragma once
#include "Document.h"
#include <conio.h>
#include <windows.h>

const int MODE_NORMAL = 0;
const int MODE_INSERT = 1;

class Editor {
private:
    Document doc;
    int currentMode;
    int cursorLine;
    int cursorCol;
    Line clipboard;
    Paragraph& currentParagraph();
    Line& currentLine();
    void gotoRowCol(int rpos, int cpos);
    void color(int k);
    void hideConsoleCursor();
    void PrintLine(int p1r, int p1c, int p2r, int p2c, char sym = -37, float delta = 0.01f);
    void drawFrame();
    void drawStatusBar();
    void handleNormalMode(int ch, bool& running);
    void handleInsertMode(int ch);
    void render();
public:
    Editor(const MyString& filename);
    void run();
};