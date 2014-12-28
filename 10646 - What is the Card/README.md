[10646 - What is the Card?](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1587)
============

### Layman Explanation

Although this is an easy question, it took me a really long time to figure out what it wants; and I looked at other people's code to do just that. I can only hope other questions are not so notoriously confusing/frustrating.

The key point that I missed from the question is that the operations that were executed 3 times were executed on the 27 cards that remained *after you took 25 cards out*, not on the 25 cards itself. It is only after the operations were completed, that you place the 25 cards (what they implied as the "25 remaining cards in your hand") you took out earlier on the top of remaining cards on the pile. Then only you find the Y-th card from the bottom.

The key point is to distinguish between the "pile" and the "hand".

Therefore here's how you interpret the input:

1. The top card of the remaining 27 cards is AH. Y = 0.
2. AH's value is 10, X=10, AH is discarded. Y = 10.
3. X-10 = 0, so no more cards are discarded
4. Next card is 2D. 2D's value is 2. X=2. Y = 12.
5. 10-X=8, so 8 cards are removed off the top of the pile
6. Next card is JD. Only JD is removed. X=10. Y = 22.
7. Take the 25 cards in your hand and place on top of the pile.
8. the Y-th (22th) card from the bottom is 8H.

