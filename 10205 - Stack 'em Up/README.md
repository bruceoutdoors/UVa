10205 - Stack 'em Up
============

### Problem in layman terms:

Explaining the sample input:

- The starting sequence is from 1 to 52, ordered first alphabetically by suit, then by value in the order given:
  - "Clubs", "Diamonds", "Hearts", "Spades"
  - "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"
- number of shuffling sequences is 2.
- this is followed by 2x52 integers denoting the shuffling sequences.
- then shuffle sequences 1 and 2 are applied in respective order, delimited by a newline (If the sequence is 1 2 2 1 separated by newline, then the shuffling sequences will be applied in that order)
- an empty line denotes that there are no more shuffle sequences to apply. 
- output the final sequence

### Algorithm Walkthrough:

2 **3** 29 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
27 28 1 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52

**1:**
- well, 2 is in where 1 should be. 
- What's in 2th position? Not 1, but 3. 
- What's in 3th position? Not 3, but 29.
- What's in 29th position? 1!
- So swap 29th with 1th position:
    
1 **3** 29 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
27 28 2 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52

**2:**
- well, 3 is in where 2 should be. 
- What's in 3th position? Not 2, but 29. 
- What's in 29th position? 2!
- So swap 29th with 2th position:  
      
1 2 **29** 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
27 28 3 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52

**3:** 
- well, 29 is in where 3 should be. 
- What's in 29th position? 3!
- So swap 29th with 3th position:
    
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52

--------------------------------

The following swap sequence:

1. 29th with 1th position
2. 29th with 2th position
3. 29th with 3th position

executed in ascending order will sort the shuffling sequence, but applied in descending order, it applies the shuffling sequence to a sequence.


### Possible Optimizations:

applying the same shuffle even number of times will not change the order (e.g. if u apply 1 2 3 3 4 3 then its same as 1 2 4 3)
