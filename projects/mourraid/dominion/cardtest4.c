/* -----------------------------------------------------------------------
 * Using format from testUpdateCoins.c
 * Tests the effect of the cutpurse card
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>FAILED
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
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
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING cutpurseEffect():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d cards in hand.\n", p, handCount);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand 
	
		cutpurseEffect(&G, G.handCount[p]);		//since great_hall is implemented in cardEffect, the 2nd, 3rd, 4th, and 6th parameters should not matter
                
		
                
#if (NOISY_TEST == 1)
                printf("G.handcount[p] = %d, expected = %d\n", G.handCount[p], handCount+1);
		//stop looping and break out if hand count doesn't match expected
		if (G.handCount[p] != handCount+1){
			printf("TEST FAILED! G.handCount[p] (%d) did not match handCount (%d)\n", G.handCount[p], handCount);
			return 1;
		}
#endif
	    
        }
    }

    printf("All tests passed!\n");

    return 0;
}
