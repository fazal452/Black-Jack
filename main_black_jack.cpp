#include <iostream>
#include <cmath>
#include <iomanip>
#include <ios>
#include <string>


using namespace ::std;

//Part 1 Library
const int DECKSIZE = 52;
const int SUITS[] = {6,3,4,5}; // ASCII CODES FOR ♠, ♥, ♦, ♣, Respectively
const string DESCRIPTION[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

//Part 2 Library
const int MAXCARDS = 12;
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

    Card* cards;
    int max_elements;
    int current_elements;


    CardArray(){

        cards = nullptr;
        max_elements = 0;
        current_elements = 0;
    }
};

//Function to Create a Full Deck of Cards

void getNewDeck(CardArray & deck){

    //Dont know what to do
    deck.max_elements = 0;
    deck.current_elements = 0;

    //Create pointer/array of Cards with size 52
    deck.cards = new Card[DECKSIZE];

    int card_count = 0;

    //Assign Values
    for (int suit = 0; suit <= 3; suit++){

        for (int rank = 1; rank <= 13; rank++){

            //Assign specific card in deck a suit
            deck.cards[card_count].suit = char (SUITS[suit]);

            //Assign specific card in deck a rank
            deck.cards[card_count].rank = rank;

            //Assign specific card in deck a description
            deck.cards[card_count].description = DESCRIPTION[rank-1];

            //Assign specific card in deck a value
            //If ACE
            if (rank == 1){
                deck.cards[card_count].value = 11;
            }

            //If Face card
            else if (rank == 11 || rank == 12 || rank == 13){
                deck.cards[card_count].value = 10;
            }

            //If Numbered
            else{
                deck.cards[card_count].value = rank;
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

            cout << (deck.cards)[card_count].description + (deck.cards)[card_count].suit + " ";
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

        temp = deck.cards[swap_index];

        deck.cards[swap_index] = deck.cards[swapee_index];

        deck.cards[swapee_index] = temp;


    }

}

//************************ Part 2 ************************//


void initHand (CardArray &hand){

    //Create 12 size Card array for hand
    hand.cards = new Card[MAXCARDS];

    hand.max_elements = MAXCARDS;
    hand.current_elements = 0;


}

void deal(const CardArray &deck,  CardArray &hand){

    hand.cards = new Card[MAXCARDS];

    int cardIndex = 0;

    while (hand.cards[cardIndex].value != 0){
        cardIndex ++;
    }

    hand.cards[cardIndex] = deck.cards[0];


}


int blackjack(CardArray & deck){

    //Create array for each Player/Dealer hand
    CardArray playerHand;
    CardArray dealerHand;

    initHand(playerHand);
    initHand(dealerHand);


    deal(deck,playerHand);


    //Placeholder DELETE
    return(0);
}













//************************ Part 3 ************************//

//************************ Part 4 ************************//

//************************ Part 5 ************************//

int main(){


    //Part 1
    CardArray testDeck;

    getNewDeck(testDeck);

    printDeck(testDeck);

    cout << "\n\n";

    shuffleDeck(testDeck);

    printDeck(testDeck);

    delete[] testDeck.cards;



//    blackjack(testDeck);



//Part 2







    return(0);
}