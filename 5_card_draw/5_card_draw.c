// Card shuffling and dealing program using structures
// deanallen, sept28th, 2020
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 
#include <string.h>

#define CARDS 52
#define FACES 13

// card structure definition                  
struct card {                                 
   const char *face; // define pointer face   
   const char *suit; // define pointer suit   
}; 

typedef struct card Card; // new type name for struct card   

// prototypes
void fillDeck(Card * const wDeck, const char * wFace[], 
   const char * wSuit[]);
void shuffle(Card * const wDeck);
void deal(const Card * const wDeck);

// hand classifiers
bool highCard(Card hand[5]);
bool twoPair(Card hand[5]);
bool threeKind(Card hand[5]);
bool straight(Card hand[5]);
bool flush(Card hand[5]);
bool fullHouse(Card hand[5]);
bool fourKind(Card hand[5]);
bool royalFlush(Card hand[5]);

int main(void)
{ 
    Card deck[CARDS]; // define array of Cards
    Card hand[5]; // hand of 5

    // initialize array of pointers
    const char *face[] = { "Ace", "Deuce", "Three", "Four", "Five",
        "Six", "Seven", "Eight", "Nine", "Ten",
        "Jack", "Queen", "King"};

    // initialize array of pointers
    const char *suit[] = { "Hearts", "Diamonds", "Clubs", "Spades"};

    srand(time(NULL)); // randomize

    fillDeck(deck, face, suit); // load the deck with Cards
    shuffle(deck); // put Cards in random order
    deal(deck); // deal all 52 Cards



    // create hand from deckl
    hand[0].face = deck[0].face;
    hand[0].suit = deck[0].suit;
    hand[1].face = deck[1].face;
    hand[1].suit = deck[1].suit;
    hand[2].face = deck[2].face;
    hand[2].suit = deck[2].suit;
    hand[3].face = deck[3].face;
    hand[3].suit = deck[3].suit;
    hand[4].face = deck[4].face;
    hand[4].suit = deck[4].suit;

    // tests
    printf("\nHand: \n");
    for (int i = 0; i < 5; i++)
    {
        printf("%s ", hand[i].face);
        printf("%s\n", hand[i].suit);
    }
    printf("-----------------------\n Tests:\n");

    // is highCard
    bool highCardTest = highCard(hand);
    printf("High Card?: %s\n", highCardTest ? "true" : "false");
    
    // is twoPairTest: result true
    bool twoPairTest = twoPair(hand);
    printf("Pair?: %s\n", twoPairTest ? "true" : "false");

    // is three kind test: result true
    hand[0].face = "Ten"; hand[0].suit = "Hearts";
    hand[1].face = "Ten"; hand[1].suit = "Hearts";
    hand[2].face = "Ten"; hand[2].suit = "Hearts";
    hand[3].face = "Five"; hand[3].suit = "Hearts";
    hand[4].face = "Six"; hand[4].suit = "Hearts";
    bool threeKindTest = threeKind(hand);
    printf("threeKind?: %s\n", threeKindTest ? "true" : "false");
    
    // is straight: result true
    hand[0].face = "Six"; hand[0].suit = "Hearts";
    hand[1].face = "Three"; hand[1].suit = "Hearts";
    hand[2].face = "Four"; hand[2].suit = "Hearts";
    hand[3].face = "Five"; hand[3].suit = "Hearts";
    hand[4].face = "Seven"; hand[4].suit = "Hearts";
    bool straightTest = straight(hand);
    printf("straight?: %s\n", straightTest ? "true" : "false");

    // is fullHouse: result true
    hand[0].face = "Six"; hand[0].suit = "Hearts";
    hand[1].face = "Six"; hand[1].suit = "Hearts";
    hand[2].face = "Six"; hand[2].suit = "Hearts";
    hand[3].face = "Five"; hand[3].suit = "Hearts";
    hand[4].face = "Five"; hand[4].suit = "Hearts";
    bool fullHouseTest = fullHouse(hand);
    printf("full house?: %s\n", fullHouseTest ? "true" : "false");
    

    // is royalFlushL result true
    hand[0].face = "Ace"; hand[0].suit = "Hearts";
    hand[1].face = "King"; hand[1].suit = "Hearts";
    hand[2].face = "Queen"; hand[2].suit = "Hearts";
    hand[3].face = "Jack"; hand[3].suit = "Hearts";
    hand[4].face = "Ten"; hand[4].suit = "Hearts";
    bool royalFlushTest = royalFlush(hand);
    printf("royal flushg test?: %s\n", royalFlushTest ? "true" : "false");


    
} 

// place strings into Card structures
void fillDeck(Card * const wDeck, const char * wFace[], 
   const char * wSuit[]) { 
   // loop through wDeck
   for (size_t i = 0; i < CARDS; ++i) { 
      wDeck[i].face = wFace[i % FACES];
      wDeck[i].suit = wSuit[i / FACES];
   } 
} 

// shuffle cards
void shuffle(Card * const wDeck)
{ 
   // loop through wDeck randomly swapping Cards
   for (size_t i = 0; i < CARDS; ++i) { 
      size_t j = rand() % CARDS;
      Card temp = wDeck[i];      
      wDeck[i] = wDeck[j];
      wDeck[j] = temp;      
   } 
} 

// deal cards
void deal(const Card * const wDeck) { 
   // loop through wDeck
   printf("Deck\n");
   for (size_t i = 0; i < CARDS; ++i) {
      printf("%5s of %-8s%s", wDeck[i].face, wDeck[i].suit,
         (i + 1) % 4 ? "  " : "\n");
   } 
   printf("-----------------------");

} 

bool highCard(Card hand[5]) {
    //check face for highcard
    for (int i = 0; i < 5; i+=1) {
        if(strcmp(hand[i].face, "King") == 0) {
            return true;
        } else if (strcmp(hand[i].face, "Queen") == 0) {
            return true;
        } else if (strcmp(hand[i].face, "Jack") == 0) {
            return true;
        } else if (strcmp(hand[i].face, "Ace") == 0) {
            return true;
        }
    }
    //if no high card, return false
    return false;  
}

bool twoPair(Card hand[5]) {
    // check all cards against eachother for pairs
    for (int i = 0; i < 5; i+=1) {
        for (int j = 0; j < 5; j+=1) {
            // dont compare the same card
            if(i != j) {
                if(strcmp(hand[i].face, hand[j].face) == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool threeKind(Card hand[5]) {
    // loop three times for checking three different cards
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                // dont compare the same card
                if(i != j && i != k && j != k ) {
                    if(strcmp(hand[i].face, hand[j].face) == 0 && strcmp(hand[i].face, hand[k].face) == 0) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool straight(Card hand[5]) {


    // convert fase string to int
    int *intHand = malloc(5 * sizeof(int*));
    int counter = 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp(hand[i].face, "One") == 0)
            *(intHand + counter) = 1;
        else if(strcmp(hand[i].face, "Two") == 0)
            *(intHand + counter) = 2;
        else if(strcmp(hand[i].face, "Three") == 0)
            *(intHand + counter) = 3;
        else if(strcmp(hand[i].face, "Four") == 0)
            *(intHand + counter) = 4;
        else if(strcmp(hand[i].face, "Five") == 0)
            *(intHand + counter) = 5;
        else if(strcmp(hand[i].face, "Six") == 0)
            *(intHand + counter) = 6;
        else if(strcmp(hand[i].face, "Seven") == 0)
            *(intHand + counter) = 7;
        else if(strcmp(hand[i].face, "Eight") == 0)
            *(intHand + counter) = 8;
        else if(strcmp(hand[i].face, "Nine") == 0)
            *(intHand + counter) = 9;
        else if(strcmp(hand[i].face, "Ten") == 0)
            *(intHand + counter) = 10;
        else if(strcmp(hand[i].face, "Jack") == 0)
            *(intHand + counter) = 11;
        else if(strcmp(hand[i].face, "Queen") == 0)
            *(intHand + counter) = 12;
        else if(strcmp(hand[i].face, "King") == 0)
            *(intHand + counter) = 13;
        else if(strcmp(hand[i].face, "Ace") == 0)
            *(intHand + counter) = 14;
        
        // counter increase for intHand to place value
        counter++;
    }

    // insertion sort to on int faces
    int temp, i, j = 0;
    for(i=0;i<5;i++){
        for(j=i+1;j<5;j++){
            if(*(intHand + (i))>*(intHand + (j))){
                temp= *(intHand + (i));
                *(intHand + (i))=*(intHand + (j));
                *(intHand + (j))=temp;
            }
        }
    }

    // see if subtracting previous index is 1, eg 2-1=1 so that would true for a straight
    for (int i = 1; i < 5; i++) {
        int dif = *(intHand + (i))-*(intHand + (i-1));
        // if dif isnt one, its not a straight
        if(dif != 1) {
            return false;
        }
    }
    return true;
}


bool flush(Card hand[5]) {
    // check if suits are all the same
    if(strcmp(hand[0].suit, hand[1].suit) == 0 &&
    strcmp(hand[1].suit, hand[2].suit) == 0 &&
    strcmp(hand[2].suit, hand[3].suit) == 0 &&
    strcmp(hand[3].suit, hand[4].suit) == 0) {
        return true;
    }

    return false;
}

bool fullHouse(Card hand[5]) {
    // loop three times for checking three different cards
    char temp[10] = "";
    bool threeP = false;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                // dont compare the same card
                if(i != j && i != k && j != k ) {
                    if(strcmp(hand[i].face, hand[j].face) == 0 && strcmp(hand[i].face, hand[k].face) == 0) {
                        strncpy(temp, hand[i].face, 10);
                        threeP = true;
                    }
                }
            }
        }
    }
    bool twoP = false;
    // check all cards against eachother for pairs
    for (int i = 0; i < 5; i+=1) {
        for (int j = 0; j < 5; j+=1) {
            // dont compare the same card and make sure the pair isnt the same as the tripple found previously
            if(i != j) {
                if(strcmp(hand[i].face, hand[j].face) == 0 && strcmp(hand[i].face, temp) != 0) {
                    twoP = true;
                }
            }
        }
    }
    // check for distinct pair and tripple
    if(threeP && twoP) {
        return true;
    }

    return false;

}

bool fourKind(Card hand[5]) {
    // compare 4 distinct cards
    for (int i = 0; i < 10; i+=2) {
        for (int j = 0; j < 10; j+=2) {
            for (int k = 0; k < 10; k+=2) {
                for (int l = 0; l < 10; l+=2) {
                    // dont compare the same card
                    if(i != j && i != k && i != l && j != k && j != l && k != l) {
                        if(strcmp(hand[i].face, hand[j].face) == 0 && strcmp(hand[i].face, hand[k].face) == 0
                            && strcmp(hand[i].face, hand[l].face) == 0) {
                                // printf("%s, %s, %s, %s",hand[i].face, hand[j].face, hand[k].face, hand[l].face);
                                return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}


bool royalFlush(Card hand[5]) {
    // high card check
    bool highCards = false;

    // high card individ check
    bool a = false;
    bool k = false;
    bool q = false;
    bool j = false;
    bool t = false;

    //check for five high cards
    for (int i = 0; i < 5; i++)
    {
        if(strcmp(hand[i].face, "Ace") == 0) {
            a = true;
        } 

        if(strcmp(hand[i].face, "King") == 0) {
            k = true;
        } 

        if(strcmp(hand[i].face, "Queen") == 0) {
            q = true;
        } 

        if(strcmp(hand[i].face, "Jack") == 0) {
            j = true;
        }

        if(strcmp(hand[i].face, "Ten") == 0) {
            t = true;
        }
    }
    // check if all is high
    if(a && k && q && j && t) {
        highCards = true;
    }
    

    // if flush and straight, its a straight flush
    if(flush(hand) && highCards ==1) {
        return true;
    }
    return false;
}

/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
