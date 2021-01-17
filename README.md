# boggle

Boggle solver

Reads a Boggle board (four lines of four lowercase characters) and emits
all possible words.

Default is to use the included `common-words.txt`, which comes from
www.wordfrequency.info. Alternatively you can change the commented lines
to use `/usr/share/dict/words` and get a ton of words you probably have
never seen before.

Known bug: I don't handle `Qu`, which is a single tile in the actual game.
