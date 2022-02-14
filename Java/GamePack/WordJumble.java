import java.util.Random;

public class WordJumble extends Game {
    private Random rng = new Random();
    private WordsList wl = new WordsList(rng);
    private int minWordLen, maxWordLen, maxGuesses;
    private String word, jumbledWord;
    private int numberOfGuesses;
    private int newNumber;
    private int[] everyPrevNumber;
    private boolean alreadyGenerated;
    private String guess;
    private int playerWins = 0;
    private int playerLosses = 0;

    /**
     * Constructor for the WordJumble class.
     * @param wl a variable of type WordList that stores the list of words rng will randomly choose from
     * @param rng a variable of type Random that is used for randomly generating words for the player
     * @param minWordLen a variable of type int storing the minimum word length for the game
     * @param maxWordLen a variable of type int storing the maximum word length for the game
     * @param maxGuesses a variable of type int storing the maximum number of guess allowed for the game
     */
    public WordJumble(WordsList wl, Random rng, int minWordLen, int maxWordLen, int maxGuesses) {
        this.wl = wl;
        this.rng = rng;
        this.minWordLen = minWordLen;
        this.maxWordLen = maxWordLen;
        this.maxGuesses = maxGuesses;
    }

    /**
     * A function that prepares the game for the next play through by generating a random word, then randomizing
     * the letters in that word. It also resets the number of guesses to zero.
     * @return returns a string stating general information about the game, including the jumbled word and the maximum number of guesses
     */
    @Override
    protected String prepToPlay() {
        word = wl.getWord(minWordLen, maxWordLen);
        guess = "";
        jumbledWord = "";
        numberOfGuesses = 0;
        everyPrevNumber = new int[word.length()];
        newNumber = rng.nextInt(word.length());

        for (int i = 0; i < word.length(); i++) {
            everyPrevNumber[i] = -1;
        }

        while (jumbledWord.length() != word.length()) {
            alreadyGenerated = false;
            for (int i : everyPrevNumber) {
                if (i == newNumber) {
                    alreadyGenerated = true;
                    break;
                }
            }
            if (!alreadyGenerated) {
                jumbledWord += word.charAt(newNumber);
                everyPrevNumber[newNumber] = newNumber;
            }
            newNumber = rng.nextInt(word.length());
        }
        return "The following is a jumbled up word: "+jumbledWord+" You get "+maxGuesses+" guesses to guess it";
    }

    /**
     * Checks to see if the game has ended or not
     * @return returns true if the maximum number of guesses has been reached, or if the player guesses the word. returns false otherwise.
     */
    @Override
    protected boolean isOver() {
        if (guess.equals(word)) {
            playerWins += 1;
            return true;
        } else if (numberOfGuesses == maxGuesses) {
            playerLosses += 1;
            return true;
        }

        return false;
    }

    /**
     * Checks if a move is valid or not
     * @param move a string storing the player's move
     * @return always returns true because any move is valid in this game
     */
    @Override
    protected boolean isValid(String move) {
        if (move.equals("quit")) {
            playerLosses += 1;
        }
        return true;
    }

    /**
     * A function to process the move the player made. In this function, the move is processed by checking
     * to see if the move is the same as the hidden word. This function also increments the number of guesses
     * the player has made.
     * @param move a string variable storing the player's move
     * @return returns a string stating "That's not it" if the player's guess is incorrect. if the guess is correct, returns an empty string.
     */
    @Override
    protected String processMove(String move) {
        guess = move;
        numberOfGuesses += 1;
        if (!guess.equals(word)) {
            return "That's not it";
        }
        return null;
    }

    /**
     * A function to store the final message of the game
     * @return returns the final message: "The word was <word>".
     */
    @Override
    protected String finalMessage() {
        return "The word was " + word;
    }

    /**
     * A function that gets the name of the game
     * @return returns the name of the game: "Word jumble"
     */
    @Override
    public String getName() {
        return "Word jumble";
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
