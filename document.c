#include "text_editor.h"
#include <stdlib.h>
#include <string.h>

// Creates a new Document
Document* createDocument() {
    Document* doc = (Document*)malloc(sizeof(Document));
    if (doc == NULL) return NULL; // Check for malloc failure

    doc->totalLines = 0;
    doc->head = NULL;
    doc->tail = NULL;
    return doc;
}

// Frees a Document and all its Lines
void freeDocument(Document* doc) {
    if (doc == NULL) return;

    Line* current = doc->head;
    while (current != NULL) {
        Line* next = current->next;
        free(current->text); // Free the text of the line
        free(current); // Free the line itself
        current = next;
    }
    free(doc); // Finally, free the document
}

// Inserts a line at the specified position in the Document
bool insertLine(Document* doc, int lineNum, const char* text) {
    if (doc == NULL || lineNum < 0 || lineNum > doc->totalLines) return false;

    Line* newLine = (Line*)malloc(sizeof(Line));
    if (newLine == NULL) return false; // Check for malloc failure

    newLine->text = strdup(text); // Duplicate the text for the new line
    if (newLine->text == NULL) {
        free(newLine);
        return false;
    }

    if (lineNum == 0) { // Insert at the beginning
        newLine->next = doc->head;
        newLine->previous = NULL;
        if (doc->head != NULL) doc->head->previous = newLine;
        doc->head = newLine;
        if (doc->tail == NULL) doc->tail = newLine;
    } else if (lineNum == doc->totalLines) { // Insert at the end
        newLine->next = NULL;
        newLine->previous = doc->tail;
        if (doc->tail != NULL) doc->tail->next = newLine;
        doc->tail = newLine;
        if (doc->head == NULL) doc->head = newLine;
    } else { // Insert in the middle
        Line* current = doc->head;
        for (int i = 0; i < lineNum; ++i) {
            current = current->next;
        }
        newLine->next = current;
        newLine->previous = current->previous;
        current->previous->next = newLine;
        current->previous = newLine;
    }

    doc->totalLines++;
    return true;
}

// Deletes a line at the specified position from the Document
bool deleteLine(Document* doc, int lineNum) {
    if (doc == NULL || lineNum < 0 || lineNum >= doc->totalLines) return false;

    Line* current = doc->head;
    for (int i = 0; i < lineNum; ++i) {
        current = current->next;
    }

    if (current->previous != NULL) current->previous->next = current->next;
    if (current->next != NULL) current->next->previous = current->previous;

    if (lineNum == 0) doc->head = current->next;
    if (lineNum == doc->totalLines - 1) doc->tail = current->previous;

    free(current->text);
    free(current);
    doc->totalLines--;
    return true;
}


