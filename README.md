# PseudoSmartBot-Tic-Tac-Toe

A command-line Tic Tac Toe game written in C++ where you play against a rule-based bot that uses basic heuristics to make decisions. The bot is not unbeatable, but it plays with a degree of strategy, hence the name.

---

## How It Works

The player is assigned X and the bot plays as O. The board is a 3x3 grid with positions numbered 1 through 9, laid out as follows:

```
 1 | 2 | 3
 4 | 5 | 6
 7 | 8 | 9
```

Players alternate turns. The player enters a position number to place their mark. The game ends when either side wins or the board is full (draw).

---

## Bot Strategy

The bot follows a priority-based decision tree on each turn:

1. **Win if possible** - checks if any move results in an immediate win and takes it
2. **Block the player** - if the player is one move from winning, the bot blocks that position
3. **Take the center** - if position 5 is free, the bot claims it
4. **Take a corner** - prefers corners (1, 3, 7, 9) over edges
5. **Take any available cell** - fallback if none of the above apply

This approach covers most common situations but can be outplayed with deliberate strategy, which is what makes it "pseudo" smart.

---
