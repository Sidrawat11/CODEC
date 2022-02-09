#include<iostream>
#include "defns.h"
#include <cstring>
#include <stdio.h>
#include <fstream>

using namespace std;

void insertion_sort(tree toBeSorted[],int n){
    int i,j;
    tree key;
    for(int i =0; i < n; i++){
        key = toBeSorted[i];
        j = i-1;
        while (j >= 0 && toBeSorted[j].freq > key.freq)
        {
            toBeSorted[j + 1] = toBeSorted[j];
            j = j - 1;
        }
        toBeSorted[j + 1] = key;
    }
};

void shiftToLeft(tree arg[], int n){
    for(int i = 1; i < n; i++){
        int j = i+1;
        arg[i] = arg[j];
    }
};

void createBinaryTree(tree arg[], int n){  
    if(n <= 3){
        n--;
    }
    int itr = 0;
    while(n >= 1){
        tree tL, tR;
        tL.freq = arg[0].freq;
        tL.symbol = arg[0].symbol;
        tL.index = arg[0].index;
        tL.root = arg[0].root;

        tR.freq = arg[1].freq;
        tR.symbol = arg[1].symbol;
        tR.index = arg[1].index;
        tR.root = arg[1].root;

        symbol *t = new symbol;
        t->parent = NULL;
        t->left = tL.root;
        t->right = tR.root;
        t->freq = tL.freq + tR.freq;

        arg[0].freq = t->freq;
        arg[0].symbol = t->symbol;
        arg[0].root = t;
        
        shiftToLeft(arg, n);
        for(int i = 1; i < n; i++){
            int j =  i-1;
            tree temp;
            if(arg[j].freq >= arg[i].freq){
                temp = arg[j];
                arg[j] = arg[i];
                arg[i] = temp;
            }else{
                break;
            }
        }
        n--;
   }
 };

void encode_binary(symbol *node, char str2[]){
    
    if(node->left != NULL){
    encode_binary(node->left, strcat(str2,"0"));}

    if(node->right != NULL){
        encode_binary(node->right, strcat(str2, "1"));}

    cout << node->symbol << "  " << str2;
};
int main(int argc, char *argv[]){

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

    ifstream infile(argv[1]);

    if(!infile.is_open()){
        cerr << "Unable to open file: " << endl;
        return 1;
    }

    string f_index;
    
    string f_freq;
    int alpha_Count = 0;
    int nonAlpha_count = 0;
    
    while(infile >> f_index >> f_freq){        
        int ind = stoi(f_index);
        int freqN = stoi(f_freq);
        if((ind >= 65 && ind <= 90) || (ind >= 97 && ind <= 122)){
            alpha_Count++;
        }
        else{
            nonAlpha_count++;
        }
        Symbols[ind].freq = freqN;
    }

    tree Alpha[alpha_Count];             //Total Alpahbetic Characters  
    tree NonAlpha[nonAlpha_count];       //Total Non-Alphabetic Characters

    int index_Alpha = 0;
    int nonAlpha_Index = 0;

    for(int i = 0; i < NSYMBOLS; i++){
        if(Symbols[i].freq > 0){
         if((i >= 65 && i <= 90) || (i >= 97 && i <= 122)){
             Alpha[index_Alpha].index = i;
             Alpha[index_Alpha].symbol = Symbols[i].symbol;
             Alpha[index_Alpha].freq = Symbols[i].freq;
             Alpha[index_Alpha].root = &Symbols[i];
             index_Alpha++;
         }
         else{
             NonAlpha[nonAlpha_Index].index = i;
             NonAlpha[nonAlpha_Index].symbol = Symbols[i].symbol;
             NonAlpha[nonAlpha_Index].freq = Symbols[i].freq;
             NonAlpha[nonAlpha_Index].root = &Symbols[i];
             nonAlpha_Index++;
         }
        }       
    }  
    if(strcmp(argv[2],"insertion") == 0){
    insertion_sort(Alpha, alpha_Count);
    insertion_sort(NonAlpha, nonAlpha_count);
    }
    
    
    createBinaryTree(Alpha, alpha_Count);
    createBinaryTree(NonAlpha, nonAlpha_count);

    symbol *root= new symbol;
    root->left = Alpha[0].root;
    root->right = NonAlpha[0].root;
    root->freq = Alpha[0].freq + NonAlpha[0].freq;
    return 0;
}

