import java.util.Random;

public class Hangman extends Game {
    private final WordsList words;
    private final int minWordLength;
    private final int maxWordLength;
    private final int maxGuesses;
    private String hiddenWord;
    private int guessesCounter;
    private String hint;
    private int playerWins = 0;
    private int playerLosses = 0;

    /**
     * A constructor for the Hangman class
     * @param words a WordsList variable storing the possible words that could be in the game
     * @param minWordLen an int variable storing the minimum word length allowed in the game
     * @param maxWordLen an int variable storing the maximum word length allowed in the game
     * @param maxGuesses an int variable storing the maximum number of guesses allowed in the game
     */
    public Hangman(WordsList words, int minWordLen, int maxWordLen, int maxGuesses) {
        this.words = words;
        this.minWordLength = minWordLen;
        this.maxWordLength = maxWordLen;
        this.maxGuesses = maxGuesses;
    }

    /**
     * Prepares the game for the next play through by generating a random word and resetting the number
     * of guesses to zero. It also resets hint to one '_' for each letter in the word.
     * @return returns a string stating the length of the word, the maximum number of guesses, and the goal of the player
     */
    @Override
    protected String prepToPlay() {
        hint = "";
        guessesCounter = 0;
        hiddenWord = words.getWord(minWordLength, maxWordLength);
        for (int i = 0; i < hiddenWord.length(); i++) {
            hint += "_";
        }
        return ("I've picked a " + hiddenWord.length() + " letter word. Guess letters you think are in the word. " +
                            "You get " + maxGuesses + " guesses.");
    }

    /**
     * A function that checks if the game is over. The game is over if the number of guesses
     * is the same as the maximum number of guesses, and checking if the hint is the same as the hidden word.
     * @return returns true if the max number of guesses has been reached, or true if the player guesses the word
     */
    @Override
    protected boolean isOver() {
        if (hiddenWord.equals(hint)) {
            playerWins += 1;
            return true;
        } else if (guessesCounter == maxGuesses) {
            playerLosses += 1;
            return true;
        }
        return false;
    }

    /**
     * Checks if a move is valid or not. A move is valid if the move is one letter long, or if its 'quit'
     * @param move a string storing the player's move
     * @return returns true if the length of move is 1 or if move is 'quit'
     */
    @Override
    protected boolean isValid(String move) {
        if (move.equals("quit")) {
            playerLosses += 1;
        }
        return move.length() == 1 || move.equals("quit");
    }

    /**
     * This function processes the move by searching the word for the guessed letter. If it finds the
     * letter, hint is updated to show that letter in its corresponding location. If the letter is not
     * found, hint stays the same. It also increments the number of guesses made by 1.
     * @param move a string variable storing the player's move
     * @return returns hint no matter what (it does not matter if hint updated or not)
     */
    @Override
    protected String processMove(String move) {
        for (int i = 0; i < hiddenWord.length(); i++) {
            if (hiddenWord.charAt(i) == move.charAt(0) && i != hiddenWord.length() - 1) {
                hint = hint.substring(0, i) + move.charAt(0) + hint.substring(i + 1);
            } else if (hiddenWord.charAt(i) == move.charAt(0)) {
                hint = hint.substring(0, i) + move.charAt(0) + "";
            }
        }
        guessesCounter += 1;
        return hint;
    }

    /**
     * Stores the final message for when the game ends
     * @return returns a string stating what the hidden word was
     */
    @Override
    protected String finalMessage() {
        return "The word was: " + hiddenWord;
    }

    /**
     * A function to get the name of the game
     * @return returns the name of the game ("Hangman")
     */
    @Override
    public String getName() {
        return "Hangman";
    }

    /**
     * A function to get the amount of wins a player has
     * @return a amount of wins a player has
     */
    @Override
    public int getPlayerWins() {
        return playerWins;
    }
    /**
     * A function to get the amount of losses a player has
     * @return an amount of losses a player has
     */
    @Override
    public int getPlayerLosses() {
        return playerLosses;
    }
}
