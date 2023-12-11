# Introduction to the Classic Word Guessing Game
Writing computer programs to play games as optimally as possible is a difficult task. When humans sit down to play a game, we can draw on past experience, adapt to our opponents' strategies, and learn from our mistakes. Computers, traditionally, blindly follow a preset algorithm that (hopefully) causes it to act somewhat intelligently. Though computers have bested their human masters in some games, most notably checkers and chess, the programs that do so often draw on hundreds of years of human game experience and use extraordinarily complex algorithms and optimizations to out-calculate their opponents. Modern advances in artificial intelligence are actively revolutionizing optimal strategies for many games.

While there are many viable strategies for building competitive computer game players, our approach here is a nefarious one centered on a mischievous program that bends the rules of of a classic word game to trounce its human opponent time and time again. In building this program, you'll cement your skills with dynamic memory management, C-string operations, command-line arguments, and general programming savvy. Plus, you'll end up with a piece of software that is highly entertaining. 

The game of interest here is a classic word guessing game that goes by many names: Hangman, Stickman, Snowman, Letter Box, Wheel of Fortune, etc. In case you aren't familiar with the classic game, the rules are as follows:

Player One (a.k.a. the chooser) chooses a secret word, then writes out a number of dashes equal to the word length.
Player Two (a.k.a. the guesser) begins guessing letters. Whenever the guesser guesses a letter contained in the hidden word, the chooser reveals each instance of that letter in the word. Otherwise, the guess is wrong.
The game ends either when all the letters in the word have been revealed or when the guesser has run out of wrong guesses.
A nuance of Step 1 that is fundamental to the game is that the chooser accurately represents the word chosen throughout the gameplay. That way, when the guesser guesses a letter, the chooser can reveal whether or not the guessed letter is in the word. But what happens if the chooser is evil and doesn't do this...? 


# Introduction to the Evil Word Guessing Game
If the chooser is evil and doesn't play by the rules, the chooser can have an enormous advantage, especially if the chooser is actively keeping a full record of ALL possible words AND can quickly analyze the word list for an optimally evil strategy to make the game as difficult as possible for the guesser. 

As an example, suppose that you are the guesser, and you have revealed a set of letters until you arrive at the following word pattern with only one guess remaining: 

D O – B L E

There are only two words in the English language that match this pattern: “doable” and “double.” If the chooser is playing fairly, then you have a 50-50 chance of winning this game if you guess 'A' or 'U' as the missing letter. However, if your opponent is evil and hasn't actually committed to either word, then there is no possible way you can win this game. No matter what letter you guess, your opponent can claim to have picked the other word, and you will lose the game. That is, if you guess that the word is “doable,” the chooser can pretend to have committed to “double” the whole time, and vice-versa.

Let's illustrate this technique with an example. Suppose that you are playing the game and it's your turn to choose a word, which we'll assume is of length four. Rather than committing to a secret word, you instead are evil and compile a list of every four-letter word in the English language. For simplicity, let's assume that English only has a few four-letter words, all of which are reprinted here:

ALLY     BETA     COOL     DEAL     ELSE     FLEW     GOOD     HOPE     IBEX

Now, suppose that your opponent guesses the letter 'E.' You now need to tell your opponent which letters in the word that you've “chosen” are E's. Of course, you haven't chosen a word, and so you have multiple options about where you reveal the E's. Here's the above word list, with E's highlighted in each word:

ALLY     BETA     COOL     DEAL     ELSE     FLEW     GOOD     HOPE     IBEX

Notice that every word in the word list falls into one of five “patterns:”

–––– which is the pattern for ALLY, COOL, and GOOD.
–E–– which is the pattern for BETA and DEAL.
E––E which is the pattern for ELSE.
––E– which is the pattern for FLEW and IBEX.
–––E which is the pattern for HOPE.
Also notice how the word list is in alphabetical order AND the pattern list is printed in the order the patterns first appear in the alphabetical word list. 

Since the letters you reveal have to correspond to some word in your word list, you can choose to move forward with any one of the above five patterns. There are many ways for an evil chooser to pick which pattern to reveal; perhaps you want to steer your opponent toward a smaller family with more obscure words or toward a larger family in the hopes of keeping your options open. For this project, in the interests of simplicity, we adopt the latter approach and always choose the pattern with the largest of the remaining word families. For our example gameplay, it means that you should pick the pattern ––––, which reduces the word list down to:

ALLY     COOL     GOOD

Since no letters were revealed, the guess is wrong and your opponent has used up one of their guesses.

Let's continue with our example gameplay using this evil strategy. Given this three-word word list, if your opponent guesses the letter O, then you would break your word list down into two patterns:

–––– which is the pattern for ALLY.
–OO– which is the pattern for COOL and GOOD.
Once again, notice how the updated word list is in alphabetical order AND the pattern list is printed in the order the patterns first appear in the alphabetical word list. 

The second pattern has a family that is larger than the first, and so you choose it, revealing two O's in the word and reducing your list down to:

COOL     GOOD

Now, what happens if your opponent guesses a letter that doesn't appear anywhere in your word list? For example, what happens if your opponent now guesses 'T'? This isn't a problem. If you try splitting the word list apart into patterns, you'll find that there's only one pattern –OO–, in which T appears nowhere and which contains both COOL and GOOD. Since there is only one possible pattern here, it's trivially the largest family, and by picking it you'd maintain the word list you already had. Of course, the guesser loses another guess by picking 'T' here.

There are two possible outcomes of this game. First, your opponent might be smart enough to pare the word list down to one word and then guess what that word is. In this case, congratulations are in order as that's an impressive feat considering the scheming you were up to! Second, your opponent may be completely stumped and will run out of guesses. When this happens, pick the first word alphabetically in your word list and present it as the word you had chosen all along. The beauty of this setup is that your opponent will have no way of knowing that you were dodging guesses the whole time; instead, it looks like you simply picked an unusual word and stuck with it the whole way.
