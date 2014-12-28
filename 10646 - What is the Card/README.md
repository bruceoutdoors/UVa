[10646 - What is the Card?](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1587)
============

Although this is an easy question, it took me a really long time to figure out what it wants; and I looked at other people's code to do just that. I can only hope other questions are not so notoriously confusing/frustrating.

The key point that I missed from the question is that the operations that were executed 3 times were executed on the 27 cards that remained *after you took 25 cards out*, not on the 25 cards itself. It is only after the operations were completed, that you place the 25 cards (what they implied as the "25 remaining cards in your hand") you took out earlier on the top of remaining cards on the pile. Then only you find the Y-th card from the bottom.

The key point is to distinguish between the "pile" and the "hand".
