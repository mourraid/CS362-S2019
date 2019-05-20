/* -----------------------------------------------------------------------
 * Using format from testUpdateCoins.c in assignment 3's help
 * Tests the effect of adventurer card
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = rand();
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    int beforeTreasureCount;
    int afterTreasureCount;
    int tempCount;

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING adventurerEffect():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d card(s).\n", p, handCount);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand 
		
		//Count the number of treasures in the player's hand before adventurer's effect goes off	
		beforeTreasureCount = 0;		
		tempCount = 0;
		while (tempCount < G.handCount[p]){
			//if the card at current position is copper, silver, or gold
			if (handCard(p, &G) == 4 || handCard(p, &G) == 5 || handCard(p, &G) == 6){
				beforeTreasureCount++;
			}
			tempCount++; 	
		} 
		
		adventurerEffect(&G);
	
		//Count the number of treasures in the player's hand now that the player has played the adventurer card	
		afterTreasureCount = 0;		
		tempCount = 0;
		while (tempCount < G.handCount[p]){
			//if the card at current position is copper, silver, or gold
			if (handCard(p, &G) == 4 || handCard(p, &G) == 5 || handCard(p, &G) == 6){
				afterTreasureCount++;
			} 	
			tempCount++;
		} 
               	
		
                
#if (NOISY_TEST == 1)
                printf("Player %d's number of treasure cards after adventurer  = %d, expected = %d\n", p, afterTreasureCount, beforeTreasureCount+2);
		//stop looping and break out if hand count doesn't match expected
		if (afterTreasureCount != beforeTreasureCount+2){
			printf("TEST FAILED! afterTreasureCount (%d) is not two treasure cards greater than beforeTreasureCount (%d)\n", afterTreasureCount, beforeTreasureCount+2);
			return 0;
		}
#endif
	    
        }
    }

    printf("All tests passed!\n");

    return 0;
}
