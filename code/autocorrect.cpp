#include <iostream>
#include <fstream>
#include <sstream>
#include "console.h"
#include "simpio.h"  // for getLine
#include "map.h"
#include "lexicon.h"
using namespace std;

void printWordList(const Lexicon& english, const Map<string, string> &misspelledLetters);
void getMisspelledLetters(Map<string,string> &misspelledLetters, Lexicon &english);
string getMisspelledWord (string word, const Map<string, string> &misspelledLetters);

int main() {
    //map misspelled letters to what computer missppels them as: ex. g -> gb on my computer
    Map<string,string> misspelledLetters;
    cout<<"Enter the name of a dictionary file you want the program to read from."<<endl;
    cout<<"File must have only one word per line."<<endl;
    string dictionary = getLine("Type dictionary filename or directory (enter for default dictionary): ");
    if (dictionary == "") dictionary = "wordsEn.txt";
    Lexicon english(dictionary);
    getMisspelledLetters(misspelledLetters, english);
    printWordList(english, misspelledLetters);
    return 0;
}
// todo: make file to write to -- just write to the end of ahk file

//gets user input of how their computer misspells things (ex. types gb instead of g)
void getMisspelledLetters(Map<string,string> &misspelledLetters, Lexicon& english) {
    while (true) {
        string misspelledLetter  = getLine("Enter letter or character your keyboard misspells (enter when done): "); //ex. g
        if (misspelledLetter == "") break;
        string misspelledResult =  getLine("Enter letter(s) it types instead: "); //ex. gb
        misspelledLetters[misspelledLetter] = misspelledResult;
    }



}


//prints the list of misspelled words& correct words in format ::misspelled::correct
//maybe export list as text file
void printWordList(const Lexicon& english, const Map<string, string> &misspelledLetters) {
    ofstream file;
    file.open("AutoCorrect.ahk.txt", ios::app);
    //gets user input of how their computer misspells non-words such as //
    while (true) {
        string additionalWordCorrect = getLine("Enter correct spelling of non-word (ex. //) or non-standard word such as your name that your computer misspells (enter when done): ");
        if (additionalWord == "") break;
        string additionalWordMisspelled = getLine("Enter how your computer misspells it: ");
        file<<"::"<<additionalWordMisspelled<<"::"<<additionalWordCorrect<<endl;

    }

    // writes mappings of misspelled words to correct words
    for (string word: english) {
        string misspelled = getMisspelledWord(word, misspelledLetters);
        if (misspelled != word) file<<"::"<<misspelled<<"::"<<word<<endl;
    }

    // todo: save file as .ahk
    file.close();
}

//returns the misspelled word corresponding to the dictionary word
string getMisspelledWord (string word, const Map<string, string> &misspelledLetters){
    string misspelled = "";
    for (char c: word) {
        if (misspelledLetters.containsKey(charToString(c))) misspelled += misspelledLetters[charToString(c)];
        else misspelled += charToString(c);
    }
    return misspelled;
}















