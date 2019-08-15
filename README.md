<h1> PokerCalc </h1>
A C++ console application that helps friends settle their poker debts at the end of a friendly game.

[Try it on Repl.it here](https://repl.it/@jonnydmobile/PokerCalc) 

<h3>The Reason for PokerCalc</h3>
My friends and I have a weekly poker night in which we play friendly $1-buyin poker. Usually we end the night before any 
one player has amassed all of the chips. At this point, we're left with a bit of a puzzle - figuring out who owes how much
to whom. Thus, the necessity for PokerCalc was born.

<h3>PokerCalc's Algorithm</h3>
PokerCalc works with a greedy algorithm that works as follows:

<h6>Description</h6>
<ol>
    <li> Generate an empty graph,
    <li> Add a node to the graph for each player,
    <li> Set the value of each node to the amount the player owes or is owed (positive and negative values, respectively).
    <li> Separate the node's into winners and losers lists
    <li> Heapify both lists - the winners into a min heap, and the losers into a max heap
    <li> While the loser that owes the most owes more than 0, 
    <ol>
        <li> determine the minimum between the loser that owes the most and the winner that is owed the most
        <li> Add an edge to the graph from loser to winner in that amount
        <li> Adjust the winner's and loser's values after the transfer
    </ol>
    <li> The completed graph represents a solution to the problem where each directed edge represents a transfer from a 
    losing player to a winning player
</ol>

<h6>The Algorithm</h6>

```
settlePayments(G(V,E))
    losers = ∅
    winners = ∅
    for each player in V
        if player's value > 0
            losers.push_back(player)
        else
            winners.push_back(player)
        
    make min-heap of losers
    make max-heap of winners

    currentLoser losers.get_max()
    losers.pop_max()

    while currentLoser's value != 0
        currentWinner = winners.get_min()
        winners.pop_min()
        
        transferAmount = min(currentLoser's value, -(currentWinner's value))
     
        E(currentLoser, currentWinner) = transferAmount
        currentLoser's value -= transferAmount
        currentWinner's value += transferAmount
    
        losers.add_heap(currentLoser)
        winners.add_heap(currentWinner)
        currentLoser = losers.get_max()
```

<h6>Complexity</h6>
<ul>
  <li>Let n be the number of players.
  <li>The first for loop runs in Θ(n) time.
  <li>Heapifying each list requires O(nlgn) time
  <li>The while loop will run at most once per player since either the loser's or the winner's balance will equal 0 after
  the transfer is applied on each iteration. Therefore, the while loop runs O(n) times
  <ul>
      <li> Removing and adding to the heap requires O(lg n) time.
  </ul>
</ul>
Therefore, the total running time of the algorithm is
O(n) + O(nlgn) + O(n) * O(lg n) = O(nlgn)

<h3>The Future of PokerCalc</h3>
The next step for PokerCalc will be to write it in a form that can be hosted as a web app with a graphical interface.
I would also like to add a visualization that displays the graph.
