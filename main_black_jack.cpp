//Fazal-ur Rehman FRA22

//The Advisor follows the strategies of Bicycles Website
//It compares your current hand score to the dealers up card
//It classifies your score, and the dealers up card, as GOOD, BAD, or FAIR
//the advisor uses those two factors to inform the user to either stand or hit

//Academic honesty statement:
//I hereby confirm that this is my own work
//and I have not violated any of SFU’s Code
//of Academic Integrity and Good Conduct (S10.01).

#include <iostream>
#include <cmath>
#include <ios>
#include <string>
using namespace ::std;

//Part 1 Library
const int NUMOFSUITS = 4;
const int NUMOFRANKS = 13;
const int DECKSIZE = 52;
const string SUITS[] = {"S","H","D","C"}; // CODES FOR SPADE,HEART,DIAMONDS,CLUB
const string DESCRIPTION[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

struct Card;
struct CardArray;

void shuffleDeck(CardArray & deck);
void getNewDeck(CardArray & deck);
void printDeck(const CardArray & deck);

//Part 2 Library
const int MAXCARDS = 12;
const int WINNUM = 21;
const int DEALERTHRESHOLD = 17;

void printHand(CardArray &hand);
void initHand (CardArray &hand);
void deal(CardArray &deck, CardArray &hand);
void deleteHands(CardArray &dealerHand, CardArray &playerHand);
bool playerHit(CardArray &dealerHand, CardArray &playerHand);
bool isBust(int score);
int handScore(const CardArray& hand);
int blackjack(CardArray & deck);

//Part 3 Library
const int WIN = 1;
const int TIE = 0;
const int LOSE = -1;

void reshuffle (CardArray &deck);
bool playerToPlay(int gamesPlayed);
int blackJackTrack(CardArray &deck);

//Part 4 Library
void aceBustAdjust(CardArray & hand);

//Part 5 Library
void advisor(CardArray &dealerHand, CardArray &playerHand);
int upCard(CardArray &hand);

//************************************ Part 1 ************************************//

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

    deck.max_elements = DECKSIZE;
    deck.current_elements = 0;

    //Create pointer/array of Cards with size 52
    deck.cards = new Card[DECKSIZE];

    int card_count = 0;

    //Assign Values
    for (int suit = 0; suit < NUMOFSUITS; suit++){

        for (int rank = 1; rank <= NUMOFRANKS; rank++){

            //Assign specific card in deck a suit
            deck.cards[card_count].suit = (SUITS[suit]);

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
    //start at card 0
    int card_count = 0;

    for (int suit = 0; suit < NUMOFSUITS; suit++){

        for (int rank = 0; rank < NUMOFRANKS; rank++){

            //Index to Card number
            card_count = suit*NUMOFRANKS + rank;

            //Print each cards description and suit
            cout << (deck.cards)[card_count].description + (deck.cards)[card_count].suit + " ";
        }
        cout << endl;
    }
}

//Shuffle a Given Deck
void shuffleDeck(CardArray & deck){

    //set random speed
    srand(time(nullptr));

    //Use a Temp variable to swap multiple indicies at random
    for(int swap_index = 0; swap_index < DECKSIZE; swap_index++){

        //get random donor
        int swapee_index =  rand() % DECKSIZE;

        //Create temp variable
        Card temp = deck.cards[swap_index];

        //Swap two cards
        deck.cards[swap_index] = deck.cards[swapee_index];
        deck.cards[swapee_index] = temp;
    }
}

//************************************ Part 2 ************************************//
void deleteHands(CardArray &dealerHand, CardArray &playerHand){
    //Free up space of Hands
    delete [] dealerHand.cards;
    delete [] playerHand.cards;
}

bool playerHit(CardArray &dealerHand, CardArray &playerHand){

    //Store variable for choice
    char choice;

    //Run Advisor to assess hands
    advisor(dealerHand,playerHand);

    //Take input
    cout << "Enter h to hit or s to stand:";
    cin >> choice;
    //cout << endl;

    //Convert choice to lower for input purposes
    choice = tolower(choice);

    while (choice != 's' && choice != 'h'){
        cin.clear();
        cin.ignore(10000,'\n');

        cout << "\nUser input invalid, Please try again:";
        cin >> choice;
        choice = tolower(choice);
    }

    //Clear Input stream
    cin.clear();
    cin.ignore(10000,'\n');

    //return True if user enters char h or H
    if (choice == 'h'){
        return true;
    }
    else{
        return false;
    }
}

//See if one has busted
bool isBust(int score){

    //If ones hand has a score of > 21
    if (score > WINNUM){
        return (true);
    }
    return false;
}

//Calculate ones hand score
int handScore(const CardArray& hand){

    int score = 0;

    //iter through their hand and sum up score
    for (int element = 0; element < hand.current_elements; element++){

        score += hand.cards[element].value;
    }
    return score;
}

//Print out ones hand
void printHand(CardArray &hand){

    for (int element = 0; element < hand.current_elements; element++){

        cout << (hand.cards)[element].description + (hand.cards)[element].suit + " ";
    }
}

//Initialize one's hand
void initHand (CardArray &hand){

    //Create 12 size Card array for hand
    //Set max elements to MAXCARDS
    //And current used elements to 0
    hand.cards = new Card[MAXCARDS];
    hand.max_elements = MAXCARDS;
    hand.current_elements = 0;

}

//Distribute card from deck to any given hand
void deal(CardArray &deck, CardArray &hand){

    //Reshuffle deck if need be
    reshuffle(deck);

    //Find where to take card and where to put card
    int removeIndex = (deck.max_elements - deck.current_elements - 1);
    int placeIndex = hand.current_elements;

    //Place card form top of deck to bottom of hand
    hand.cards[placeIndex] = deck.cards[removeIndex];

    //Increment the current elements used
    deck.current_elements ++;
    hand.current_elements ++;

    //Adjust for any double aces
    aceBustAdjust(hand);

}

//Game of BAREBONES BLACKJACK
int blackjack(CardArray & deck){

    //Create array for each Player/Dealer hand
    CardArray playerHand;
    CardArray dealerHand;

    //Initialize each hand
    initHand(playerHand);
    initHand(dealerHand);

    //Give a Card to Player
    deal(deck,playerHand);

    //Give a card to Dealer
    deal(deck,dealerHand);

    //Print First Hand
    cout << "\nDEAL FIRST CARD\n---------------\n";
    cout << "+PLAYER+: ";
    printHand(playerHand);

    cout << "\n*DEALER*: ";
    printHand(dealerHand);

    //Give a Card to Player
    deal(deck,playerHand);
    //Give Dealer card after printing in order for mystery

    //Print Second Hand
    cout << "\n\nDEAL SECOND CARD\n----------------\n";
    cout << "+PLAYER+: ";
    printHand(playerHand);

    cout << "\n*DEALER*: ";
    printHand(dealerHand);
    cout << "??";

    //deal second card to dealer
    deal(deck,dealerHand);

    //If Player gets 21 natural
    if(handScore(playerHand) == WINNUM){

        //If dealer doesnt have 21
        //Player Wins
        if(handScore(dealerHand) != WINNUM){

            cout << "\n*DEALER*: ";
            printHand(dealerHand);

            cout << "\n\nBLACK JACK YOU WIN!!!";
            deleteHands(dealerHand,playerHand);
            return WIN;
        }

        //If dealer have 21
        //Player Tie
        cout << "\n*DEALER*: ";
        printHand(dealerHand);

        cout << "\nTIE!!! BOTH PLAYERS BLACK JACK";
        deleteHands(dealerHand,playerHand);
        return TIE;
    }

    //Check for Dealer 21
    if(handScore(dealerHand) == WINNUM){

        //If dealer have 21
        //Player Lose
        cout << "\n*DEALER*: ";
        printHand(dealerHand);

        cout << "\nLOSE!!!! DEALER GOT BLACKJACK";
        deleteHands(dealerHand,playerHand);
        return LOSE;
    }


    //Start Playing
    cout << "\n\nDEALING TO PLAYER\n-----------------\n";

    //Get Choice
    bool hit = playerHit(dealerHand,playerHand);

    //While Player wants to play
    while(hit){

        //Deal Player a Card
        deal(deck,playerHand);

        cout << "\n+PLAYER+: ";
        printHand(playerHand);
        cout << endl;

        if (isBust(handScore(playerHand))){

            cout << "\nBUST! YOU LOSE";
            deleteHands(dealerHand,playerHand);
            return LOSE;
        }
        //Update whether to hit or not
        hit = playerHit(dealerHand,playerHand);
    }


    //Dealer Plays out his hand
    cout << "\n\nDEALING TO DEALER\n-----------------\n";

    cout << "*DEALER*: ";
    printHand(dealerHand);

    //Dealer keeps drawing till win or bust
    while (((handScore(dealerHand)) < DEALERTHRESHOLD) && (handScore(dealerHand) < handScore(playerHand))){

        deal(deck,dealerHand);

        cout << "\n*DEALER*: ";
        printHand(dealerHand);

        aceBustAdjust(dealerHand);
        if(isBust(handScore(dealerHand))){

            cout << "\n\nDEALER HAS BUSTED, YOU WIN!!";
            deleteHands(dealerHand,playerHand);
            return WIN;
        }

    }

    //Determine Results
    cout << "\n\nRESULTS \n-----------------------------------\n";
    cout << "Player Score: " << handScore(playerHand) << " | Dealer Score: "
    << handScore(dealerHand);

    //Player scores more
    if(handScore(playerHand) > handScore(dealerHand)){
        cout << "\nYOU WIN!!!";
        deleteHands(dealerHand,playerHand);
        return WIN;
    }

    //Dealer scores more
    if(handScore(playerHand) < handScore(dealerHand)){
        cout << "\nYOU LOST!!!";
        deleteHands(dealerHand,playerHand);
        return LOSE;
    }

    //Tie
    if(handScore(playerHand) == handScore(dealerHand)){
        cout << "\nYOU TIED!!!";
        deleteHands(dealerHand,playerHand);
        return TIE;
    }

}

//************************************ Part 3 ************************************//


void reshuffle (CardArray &deck){

    //IF Deck will finish, shuffle up deck
    if (deck.current_elements >= DECKSIZE-1){

        shuffleDeck(deck);

        //Print out shuffled version
        cout << "\n\n***RESHUFFLED DECK***\n\n";
//        printDeck(deck);

        //Re init deck as new
        deck.current_elements = 0;
        deck.max_elements = DECKSIZE;
    }
}

//Get Whether player wants to play another round or not
bool playerToPlay(int gamesPlayed){

    char choice;

    //If first game
    if (gamesPlayed == 0){
        cout << "\nWELCOME TO BLACKJACK\n--------------------\n";
        cout << "Do you want to play a hand of blackjack? (y to play) :";
    }
    else{
        cout << "\n\nDo you want to play another hand of blackjack? (y to play) :";
    }

    cin >> choice;

    //make choice lower and clear input stream
    choice = tolower(choice);
    cin.clear();
    cin.ignore(10000,'\n');

    //Input checking for y or n
    while(!(choice == 'y' || choice == 'n')){

        cout << "\nWRONG INPUT, Try again (y to play, n to not play):";
        cin >> choice;

        //make choice lower and clear input stream
        choice = tolower(choice);
        cin.clear();
        cin.ignore(10000,'\n');
    }

    //Return True if player enters y or Y
    if (choice == 'y'){
        return true;
    }

    else{
        return false;
    }
}


//Play multiple Games of Black jack
//Keep Track of important variables, games played, wins, losses, ties
int blackJackTrack(CardArray &deck){

    //Keep track of vital game variables
    int gamesPlayed = 0;
    int wins = 0;
    int losses = 0;
    int draws = 0;
    int result;

    bool playing = playerToPlay(gamesPlayed);

    while (playing){

        //store result of game into whatever outcome of game is
        result = blackjack(deck);

        //reshuffle the deck if need be
        reshuffle(deck);

        gamesPlayed++;

        if (result == WIN){
            wins ++;
        }
        else if (result == TIE){
            draws ++;
        }
        else if (result == LOSE){
            losses ++;
        }

        result = NULL;

        //Ask again whether player wants to play
        playing = playerToPlay(gamesPlayed);
    }

    //Once Player quits give them stats

    if (gamesPlayed == 0){
        cout << "\nThanks for trying\n";
        return(0);
    }

    if (gamesPlayed == 1){
        cout << "\nThanks for playing, you played " << gamesPlayed << " game and your record was:\n";
    }

    else{
        cout << "\nThanks for playing, you played " << gamesPlayed << " games and your record was:\n";
    }

    cout << "wins: " << wins << endl;
    cout << "losses: " << losses << endl;
    cout << "draws: " << draws << endl;

    return(0);
}



//************************************ Part 4 ************************************//

//Aces count as 11 until you bust, in which case they become 1's

void aceBustAdjust(CardArray & hand){

    for(int element = 0; element < hand.current_elements;element++){

        //If someone has busted
        if (isBust(handScore(hand))) {

            //Replace aces value from 11 to 1
            if (hand.cards[element].rank == 1 && hand.cards[element].value != 1) {

                hand.cards[element].value = 1;

            }
        }
    }
}


//************************************ Part 5 ************************************//

//Calculate the Dealers Up card
int upCard(CardArray &hand){

    int maxCard = 0;
    //iterate though to find max value card
    for(int element = 0; element < hand.current_elements;element++){

        //store max
        maxCard = max(maxCard,hand.cards[element].value);
    }
    return maxCard;
}

//Functions that advises player on optimal winning strategies
void advisor(CardArray &dealerHand, CardArray &playerHand){

    const int GOODCARD = 7;
    const int FAIRCARD = 3;
    const int GOODSCORE = 17;
    const int FAIRSCORE = 12;

    //Store the vital playing cards of each player
    int dealerScore = handScore(dealerHand);
    int playerScore = handScore(playerHand);

    int dealerUpCard = upCard(dealerHand);
    int playerUpCard = upCard(playerHand);

    cout << "ADVISOR: ";

    // If Dealer has a GOOD card
    if (dealerUpCard >= GOODCARD){

        if (playerScore < GOODSCORE){
            cout << "You should HIT\n         Dealer's up card score is good at " << dealerUpCard
                 << " but your score is only " << playerScore <<  "\n";
        }

        else{
            cout << "You should STAND\n         Dealer's up card score is good at "<< dealerUpCard
                 << " but your score is " << playerScore <<  "\n";
        }
    }

        //If dealer has a FAIR card
    else if(dealerUpCard > FAIRCARD && dealerUpCard < GOODCARD){

        if (playerScore < FAIRSCORE){
            cout << "You should HIT\n         Dealer's up card score is bad at " << dealerUpCard
                 << " and your score is only " << playerScore <<  "\n";
        }

        else{
            cout << "You should STAND\n         Dealer's up card is bad at " << dealerUpCard
                 << " and your score is good enough at " << playerScore <<  "\n";;
        }
    }

        //If Dealer has a BAD card
    else if(dealerUpCard <= FAIRCARD){

        if (playerScore < FAIRSCORE + 1){
            cout << "You should HIT\n         Dealer's up card score is fair at " << dealerUpCard
                 << " but your score is only " << playerScore <<  "\n";;
        }

        else{
            cout << "You should STAND\n         Dealer's up card score is fair at " << dealerUpCard
                 << " and your score is good enough at " << playerScore << "\n";
        }
    }
}

//************************************  MAIN  ************************************//

int main(){

    //Get New Deck
    CardArray testDeck;
    getNewDeck(testDeck);

    cout << "STANDARD DECK:\n";
    printDeck(testDeck);

    cout << "\nSHUFFLED DECK:\n";
    shuffleDeck(testDeck);
    printDeck(testDeck);

    //Play the game of Black Jack
    blackJackTrack(testDeck);

    //Delete deck once your finished
    delete[] testDeck.cards;

    return(0);
}