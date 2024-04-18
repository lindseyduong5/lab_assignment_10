/*Lindsey Duong
4/18/23
Lab Assignment 10*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie structure
struct Trie {
    struct Trie *children[ALPHABET_SIZE];
    int isEndOfWord;
    int count;
};

// Initializes a trie node
struct Trie *createNode() {
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    if (node) {
        node->isEndOfWord = 0;
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Inserts the word to the trie structure
void insert(struct Trie *root, char *word) {
    struct Trie *temp = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (!temp->children[index]) {
            temp->children[index] = createNode();
        }
        temp = temp->children[index];
    }
    temp->isEndOfWord = 1;
    temp->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *root, char *word) {
    struct Trie *temp = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (!temp->children[index]) {
            return 0;
        }
        temp = temp->children[index];
    }
    return (temp != NULL && temp->isEndOfWord) ? temp->count : 0;
}

// Deallocates the trie structure
void deallocateTrie(struct Trie *root) {
    if (root) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (root->children[i]) {
                deallocateTrie(root->children[i]);
            }
        }
        free(root);
    }
}

// Initializes a trie structure
struct Trie *createTrie() {
    return createNode();
}

// Reads the dictionary from a file
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    int numWords = 0;
    char word[100]; // Assuming maximum word length is 100 characters

    while (fscanf(file, "%s", word) != EOF) {
        pInWords[numWords] = strdup(word);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void) {
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    struct Trie *root = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }

    // Test with sample words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }

    deallocateTrie(root);

    return 0;
}
