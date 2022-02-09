#include <iostream>
#include "defns.h"
#include <cstring>
#include <stdio.h>

using namespace std;

int main(){

    symbol Symbols[NSYMBOLS];

    //First Step: Initialising Symbol Struct
    for(int i = 0; i < NSYMBOLS; i++){
        Symbols[i].symbol = char (i);
        Symbols[i].freq = 0;
        Symbols[i].parent = NULL;
        Symbols[i].left = NULL;
        Symbols[i].right = NULL;
        strcpy(Symbols[i].encoding,"");
    }

    //Second Step: Reading Input from the file
    //This Character reads from the file
    char fchar;

    //Using stdin as input stream
    while(!feof(stdin)){
        fchar = fgetc(stdin);
        int index =  (int) fchar;
        Symbols[index].freq++;
    }

    for(int i = 0; i < NSYMBOLS; i++){
        if(Symbols[i].freq > 0)
        {
            cout << i << "\t" << Symbols[i].freq << endl;
        }
    }
    return 0;
}