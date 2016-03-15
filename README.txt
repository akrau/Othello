
In the player class, we have the doMove function, which can either run a 2ply minimax, or a weighted heuristic function, depending on the value of testminimax. 

We also have a function that is never run that is an AI that completes random valid moves. It was our starting point for the assignment.

Note: the timestamps on git for Clare during week 1 were a little broken.

********************

Here is what each group member contributed in the past two weeks:

Anise -- created the git repository, wrote all of the rough draft implementation for simple heuristic and minimax in week 1, figured out the algorithms for each.
Clare -- mostly debugged Anise's code to allow it to compile, tested the code, got AI to compile properly at beginning, implemented clock, attempted recursive minimax, attempted negamax.

********************

Strategies and improvements:

We attempted a recursive minimax, which would allow us to go to depths beyond 2, but we didn't have time to make it work. We also attempted negamax but it didn't really fit well into our work from last week. Thus we settled for our 2-ply Minimax from week 1 because it does a decent job. We didn't want to change what already works so we stuck with our working solution that has some level of planning moves. We think this is a good enough strategy to defeat a good number of other teams because other people might have already passed the class so they didn't try as hard on week 1 while we tried hard on week 1. 