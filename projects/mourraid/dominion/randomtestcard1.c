/* -----------------------------------------------------------------------
 * Using format from testUpdateCoins.c in assignment 3's help
 * Tests the effect of the village card
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

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

    int numActions = 1;		//each turn starts with 1 action

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING villageEffect():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s).\n", p, handCount);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand 
			
		villageEffect(&G, handCount);	
		
                
#if (NOISY_TEST == 1)
                printf("Player %d's number of cards after village  = %d, expected = %d\n", p, G.handCount[p], handCount);
		//stop looping and break out if hand count doesn't match expected
		if (G.handCount[p] != handCount){
			printf("TEST FAILED! Player %d's hand has %d cards in hand, but should have %d cards\n", p, G.handCount[p], handCount);
			return 0;
		}
#endif

#if (NOISY_TEST == 1)
                printf("Player %d's number of actions after village  = %d, expected = %d\n", p, G.numActions, numActions+2);
		//stop looping and break out if number of actions doesn't match expected
		if (G.numActions != numActions+2){
			printf("TEST FAILED! Player %d's hand has only %d action(s), but should have %d actions available\n", p, G.numActions, numActions+2);
			return 0;
		}
#endif
	    
        }
    }

    printf("All tests passed!\n");

    return 0;
}
