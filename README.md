# multi-stage-inventory-optimization-model-
This program helps determine the optimal inventory management strategy over several stages (time periods).

It tries to minimize total cost while accounting for:

Stocking cost (cost of storing items in stock),

Supplementing cost (cost of ordering or producing more items),

Expenses (items used or demanded in each stage).

It prints:

A table of stocking and supplementing costs,

A sequence of decision tables for each stage (showing transitions, costs, and totals),

Finally, it prints the optimal decision path (the sequence of stocking/supplementing actions that leads to minimum total cost).
The problem is modeled as a multi-stage decision process, similar to Dynamic Programming.

At each stage:

You have a state (how much stock you have at the start of the stage),

You make a decision (how much to supplement or order),

You incur a cost (stocking + supplementing + possibly future cost),

You move to a next state (new stock level after expenses).

The program recursively computes minimal total costs backward (from last stage to first).
