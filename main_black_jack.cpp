#include <iostream>
#include <cmath>
#include <iomanip>
#include <ios>
#include <string>

using namespace ::std;


string SUITS[] = {"s","h","d","c"};
string DESCRIPTION[] = {"A","1","2","3","4","5","6","7","8","9","10","J","Q","K"};


//Part 1

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

    deck.max_elements = 52;
    deck.current_elements = 52;

    deck.pointer = new Card[52];


    //deck.pointer->suit = SUITS[suit];

    int card_count = 0;

    //Assign Values
    for (int suit = 0; suit <= 3; suit++){

        for (int rank = 1; rank <= 13; rank++){

            //Assign specific card in deck a suit
            deck.pointer[card_count].suit = SUITS[suit];

            //Assign specific card in deck a rank
            deck.pointer[card_count].rank = rank;

            //Assign specific card in deck a description
            deck.pointer[card_count].suit = DESCRIPTION[rank-1];

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
                deck.pointer[card_count].value = rank % 10;
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

            cout << ((deck.pointer)[card_count].suit) << "" << ((deck.pointer)[card_count].rank) << " ";
        }

        cout << endl;
    }



}





//Part 2

//Part 3

//Part 4

//Part 5

int main(){

    CardArray testDeck;

    getNewDeck(testDeck);

    printDeck(testDeck);


    return(0);
}