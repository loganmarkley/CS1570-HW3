Score: 100

## Comments:
- Excellent work, just a few suggestions to keep in mind (these are mostly nitpicking, since your code is already very well written):
- In your `printGameSummary` and `shareWordle` pre- and post-conditions, you specified that specific parameters were required to be specific variables. This is usually a sign that your function is poorly designed; in this specific case, it would have been better to:
	- `printGameSummary`: take in the friendship value as a prameter, and then return the new friendship value (instead of modifying by reference)
	- `shareWordle`: I'm not sure why you specified the exact variables you wanted to be passed in, but generally this should be unnecessary, as your parameter names ought to be (and were, in this case) descriptive enough to tell the user what to pass in.

	Generally, I would not have taken off for this, unless it were blatantly incorrect, and I understand that you were modifying a previous project, and wanted to make as few changes as possible while retaining functionality. However, I still feel that I have to tell you that this is generally a sign that things have gone wrong.
- Your comments were generally pointless:
	- First of all, the big "block comments" (`//--------- declarations ----------`, etc.) are completely unnecessary. If you feel the need to annotate a whole block of code with a comment (ie. name a block of code), that's called a function. Block comments just add unnecessary clutter to your code.
	- Your comments describing your variables were a mixed bag, but generally I would advise against these, as it's usually better to choose a more descriptive variable name rather than band-aid it with a comment.
	- Your comments narrating what your code was doing (ie. on loops, etc.) were generally useless, as your code is (and should be) self-explanatory.

	However, I did not take off, as you did not have so many comments so as to significantly clutter up the code.
- I noticed that you used several single line `if` statements without curly braces. While this is technically legal, I would advise against it, because it can introduce bugs later on if you want to add another line and you're not careful. In other words, I would recommend always putting curly braces.
- I really liked the aesthetic touches you put into the output, very good work.

Overall, pretty much perfect code; very well done. Keep up the good work!