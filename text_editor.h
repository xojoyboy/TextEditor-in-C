#ifndef TEXT_EDITOR_H 
#define TEXT_EDITOR_H

#include <stdbool.h>

Document line structure
typedef struct Line {
    char* text;           // Text content of the line
    struct Line* next;    // Pointer to the next line
    struct Line* previous; // Pointer to the previous line
} Line;

// Text document structure
typedef struct Document {
    int totalLines;       // Total number of lines in the document
    Line* head;           // Pointer to the first line of the document
    Line* tail;           // Pointer to the last line of the document
} Document;

// Cursor position structure
typedef struct Cursor {
    int lineNum;          // Current line number of the cursor (0-indexed)
    int charPos;          // Current character position in the line (0-indexed)
} Cursor;

// Document manipulation functions
Document* createDocument();
void freeDocument(Document* doc);
bool insertLine(Document* doc, int lineNum, const char* text); // Inserts a line at specified position
bool deleteLine(Document* doc, int lineNum); // Deletes a line at specified position

// Text editing functions
bool insertText(Document* doc, Cursor* cursor, const char* text); // Inserts text at the cursor's position
bool deleteText(Document* doc, Cursor* cursor, int length); // Deletes text starting from the cursor's position

// Cursor manipulation functions
void moveCursor(Document* doc, Cursor* cursor, int lineNum, int charPos); // Moves the cursor to a specific position
void moveCursorUp(Document* doc, Cursor* cursor); // Moves the cursor up one line
void moveCursorDown(Document* doc, Cursor* cursor); // Moves the cursor down one line
void moveCursorLeft(Cursor* cursor); // Moves the cursor left one character
void moveCursorRight(Document* doc, Cursor* cursor); // Moves the cursor right one character

// File operations
Document* loadDocument(const char* filename); // Loads a document from a file
bool saveDocument(const Document* doc, const char* filename); // Saves the document to a file

// Display function
void displayDocument(const Document* doc); // Displays the entire document

// Utility functions
int getLineLength(const Line* line); // Gets the length of a specific line
bool isDocumentEmpty(const Document* doc); // Checks if the document is empty

#endif // TEXT_EDITOR_H

