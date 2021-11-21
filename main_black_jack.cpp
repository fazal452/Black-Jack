#include <iostream>
#include <cmath>
#include <iomanip>
#include <ios>
#include <string>


using namespace ::std;

//Part 1 Library
const int DECKSIZE = 52;
const int SUITS[] = {6,3,4,5};
const string DESCRIPTION[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

//Part 2 Library
//Part 3 Library
//Part 4 Library
//Part 5 Library

//************************ Part 1 ************************//

//Structure for a Card
struct Card{

    string suit;
    string description;
    int rank;
    int value;

    Card(){
        suit = "";
        description = "";
        rank = 0;
        value = 0;
    }
};

//Structure for an Array of Cards
struct CardArray{

    Card* pointer;
    int max_elements;
    int current_elements;

    CardArray(){

        pointer = nullptr;
        max_elements = 0;
        current_elements = 0;
    }
};

//Function to Create a Deck of Cards

void getNewDeck(CardArray & deck){

    deck.max_elements = DECKSIZE;
    deck.current_elements = DECKSIZE;

    deck.pointer = new Card[DECKSIZE];


    //deck.pointer->suit = SUITS[suit];

    int card_count = 0;

    //Assign Values
    for (int suit = 0; suit <= 3; suit++){

        for (int rank = 1; rank <= 13; rank++){

            //Assign specific card in deck a suit
            deck.pointer[card_count].suit = char (SUITS[suit]);

            //Assign specific card in deck a rank
            deck.pointer[card_count].rank = rank;

            //Assign specific card in deck a description
            deck.pointer[card_count].description = DESCRIPTION[rank-1];

            //If ACE
            if (rank == 1){
                deck.pointer[card_count].value = 11;
            }

            //If Face card
            else if (rank == 11 || rank == 12 || rank == 13){
                deck.pointer[card_count].value = 10;
            }

            //If Numbered
            else{
                deck.pointer[card_count].value = rank;
            }


            card_count ++;
        }
    }



}

//Print out the Deck
void printDeck(const CardArray & deck){

    int card_count = 0;

    for (int suit = 0; suit <= 3; suit++){

        for (int rank = 0; rank < 13; rank++){

            card_count = suit*13 + rank;

            cout << (deck.pointer)[card_count].description + (deck.pointer)[card_count].suit + " ";
        }
        cout << endl;
    }

}

//Shuffle a Given Deck
void shuffleDeck(CardArray & deck){

    srand(time(nullptr));

    //Use a Temp variable to swap multiple indicies at random

    for(int swap_index = 0; swap_index < DECKSIZE; swap_index++){

        int swapee_index =  rand() % DECKSIZE;

        Card temp;

        temp = deck.pointer[swap_index];

        deck.pointer[swap_index] = deck.pointer[swapee_index];

        deck.pointer[swapee_index] = temp;


    }

}






//************************ Part 2 ************************//

//************************ Part 3 ************************//

//************************ Part 4 ************************//

//************************ Part 5 ************************//

int main(){

    CardArray testDeck;

    getNewDeck(testDeck);

    printDeck(testDeck);

    cout << "\n\n";


    shuffleDeck(testDeck);

    printDeck(testDeck);


    return(0);
}