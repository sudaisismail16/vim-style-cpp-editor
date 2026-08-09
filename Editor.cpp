#include "Editor.h"
#include <iostream>

Editor::Editor(const MyString& filename) : doc(filename) {
    currentMode = MODE_NORMAL;
    cursorLine = 0;
    cursorCol = 0;
}

Paragraph& Editor::currentParagraph() {
    return doc.getChapter(0).getSection(0).getParagraph(0);
}

Line& Editor::currentLine() {
    return doc.getLineByGlobalIndex(cursorLine);
}

void Editor::gotoRowCol(int rpos, int cpos) {
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void Editor::color(int k) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

void Editor::hideConsoleCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Editor::PrintLine(int p1r, int p1c, int p2r, int p2c, char sym, float delta) {
    for (float a = 0; a <= 1; a += delta) {
        int r = ceil(p1r * (1 - a) + p2r * a);
        int c = ceil(p1c * (1 - a) + p2c * a);
        if (p1r == p2r) r = p1r;
        if (p1c == p2c) c = p2c;
        gotoRowCol(r, c);
        cout << sym;
    }
}
void Editor::drawFrame() {
    color(11);
    gotoRowCol(0, 2);
    cout << "== Sudais Ka Heavy 5000 Dollar Text Editor ==";

    color(4);
    PrintLine(1, 0, 1, 79, -37);
    PrintLine(2, 0, 20, 0, -37);
    PrintLine(2, 79, 20, 79, -37);
    PrintLine(21, 0, 21, 79, -37);
    color(7);
}

void Editor::drawStatusBar() {
    gotoRowCol(22, 0);
    if (currentMode == MODE_INSERT) {
        color(14);
        cout << "-- INSERT MODE --  (ESC to return to Normal)                  ";
    }
    else {
        color(10);
        cout << "-- NORMAL MODE --  (i: insert, x/dd/yy/p, w: save, q: quit)  ";
    }
    color(5);
    gotoRowCol(25, 0);
    cout << "  MS WORD is Overrated. ";
    color(7);
}

void Editor::render() {
    system("cls");
    hideConsoleCursor();

    drawFrame();
    drawStatusBar();

    int total = doc.getTotalLineCount();
    for (int i = 0; i < 19; i++) {
        int screenRow = 2 + i;
        gotoRowCol(screenRow, 2);
        color(7);
        if (i < total) {
            string text = doc.getLineByGlobalIndex(i).getContent().c_str();
            if (text.length() > 75)
                text = text.substr(0, 75);
            cout << text;
        }
        else {
            color(8);
            cout << "~";
            color(7);
        }
    }

}

void Editor::handleNormalMode(int ch, bool& running) {
    Paragraph& para = currentParagraph();

    if (ch == 'h') {
        if (cursorCol > 0) {
            cursorCol--;
        }
    }
    else if (ch == 'l') {
        int len = currentLine().getLength();
        if (cursorCol < len) {
            cursorCol++;
        }
    }
    else if (ch == 'j') {
        if (cursorLine < doc.getTotalLineCount() - 1) {
            cursorLine++;
            int len = currentLine().getLength();
            if (cursorCol > len) {
                cursorCol = len;
            }
        }
    }
    else if (ch == 'k') {
        if (cursorLine > 0) {
            cursorLine--;
            int len = currentLine().getLength();
            if (cursorCol > len) {
                cursorCol = len;
            }
        }
    }
    else if (ch == 'i') {
        currentMode = MODE_INSERT;
    }
    else if (ch == 'x') {
        Line& l = currentLine();
        if (cursorCol < l.getLength()) {
            l.deleteChar(cursorCol);
        }
    }
    else if (ch == 'd') {
        int next = _getch();
        if (next == 'd') {
            clipboard = para.getLine(cursorLine);
            para.removeLine(cursorLine);
            if (para.isEmpty()) {
                para.appendLine(Line(""));
            }
            if (cursorLine >= para.getLineCount()) {
                cursorLine = para.getLineCount() - 1;
            }
            cursorCol = 0;
        }
    }
    else if (ch == 'y') {
        int next = _getch();
        if (next == 'y') {
            clipboard = currentLine();
        }
    }
    else if (ch == 'p') {
        if (!clipboard.isEmpty()) {
            para.insertLine(cursorLine + 1, clipboard);
            cursorLine++;
            cursorCol = 0;
        }
    }
    else if (ch == 'w') {
        doc.saveToFile(doc.getFilename());
    }
    else if (ch == 'q') {
        running = false;
    }
}

void Editor::handleInsertMode(int ch) {
    if (ch == 27) { 
        currentMode = MODE_NORMAL;
        return; 
    }
    if (ch == 8) {
        if (cursorCol > 0) {
            currentLine().deleteChar(cursorCol - 1);
            cursorCol--;
        }
        return;
    }
    if (ch >= 32 && ch <= 126) {
        currentLine().insertChar(cursorCol, (char)ch);
        cursorCol++;
    }
}

void Editor::run() {
    bool running = true;
    render();
    while (running) {
        int ch = _getch();
        if (currentMode == MODE_NORMAL) {
            handleNormalMode(ch, running);
        }
        else if (currentMode == MODE_INSERT) {
            handleInsertMode(ch);
        }
        render();
    }
}