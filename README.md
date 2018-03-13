Caltech CS2 Assignment 9: Othello

Group member contributions:

Steve Guo: wrote constructor and naive heuristic, implemented naive algorithm, fixed some
memory leak problems, attempted to implement alpha-beta pruning
Albert Zhai: wrote minimax tree, fixed some memory leak problems, rearranged code to make neater/more efficient

How AI is tournament worthy:
We attempted to implement alpha-beta pruning, but pulled it because it didn't work. However,
our AI has a positive winrate against Simple Player. Increasing the depth of the minimax tree
allows our AI to win against better opponents at the cost of time. We think our strategy will work
because we tested our AI with various depth levels against numerous opponents and it won sometimes. 
