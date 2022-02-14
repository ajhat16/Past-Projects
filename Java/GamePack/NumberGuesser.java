import java.util.Random;

public class NumberGuesser extends Game{
    private Random rng;
    private int maxNumber;
    private int maxGuesses;
    private int hiddenNumber;
    private int numberOfGuesses;
    private int guess;
    private int playerWins = 0;
    private int playerLosses = 0;

    /**
     * A constructor for the NumberGuesser function
     * @param rng a Random variable used for generating a random number for the player to guess
     * @param maxNumber an int storing the highest number rng can go to
     * @param maxGuesses an int storing the max number of guesses allowed in the game
     */
    public NumberGuesser(Random rng, int maxNumber, int maxGuesses) {
        this.rng = rng;
        this.maxNumber = maxNumber;
        this.maxGuesses = maxGuesses;
    }

    /**
     * Prepares the game for the next play through by initializing the number of guesses to zero, and
     * picking a random number for the player to guess
     * @return returns a string stating the range of the random number, the number of guesses the player has, the goal of the player
     */
    @Override
    protected String prepToPlay() {
        numberOfGuesses = 0;
        guess = 0;
        hiddenNumber = rng.nextInt(maxNumber) + 1;
        return "I've picked a number 1 to "+maxNumber+". You get "+maxGuesses+" guesses to guess it";
    }

    /**
     * Checks if the game is over by comparing the max number of guesses to the number of guesses
     * that have been made, or comparing the player's guess to the hidden number.
     * @return
     */
    @Override
    protected boolean isOver() {
        if (guess == hiddenNumber) {
            playerWins += 1;
            return true;
        } else if (maxGuesses == numberOfGuesses) {
            playerLosses += 1;
            return true;
        }
        return false;
    }

    /**
     * Checks if the move was valid or not. A move is valid if the move is 'quit', or if every
     * character in the string is a digit
     * @param move a string variable storing a player's move
     * @return returns true if the move is 'quit', or is only digits
     */
    @Override
    protected boolean isValid(String move) {
        for (int i = 0; i < move.length(); i++) {
            if (move.equals("quit")) {
                playerLosses += 1;
                return true;
            } else if (!Character.isDigit(move.charAt(i))) {
                return false;
            }
        }
        return true;
    }

    /**
     * Processes the move by incrementing the number of guesses, changing the player's guess
     * to an integer, then comparing that integer to the hidden number.
     * @param move a string variable storing the player's move
     * @return returns 'Too Low' if the move is too low, 'Too High' if the move is too high, or 'That's it!' if the player guesses the hidden number
     */
    @Override
    protected String processMove(String move) {
        numberOfGuesses += 1;
        guess = Integer.parseInt(move);
        if (guess < hiddenNumber) {
            return "Too Low";
        } else if (guess > hiddenNumber) {
            return "Too High";
        }
        return "That's it!";
    }

    /**
     * A function to store the final message of the game for when the game ends
     * @return returns the final message of the game: 'The number was: <hiddenNumber>'
     */
    @Override
    protected String finalMessage() {
        return "The number was: " + hiddenNumber;
    }

    /**
     * Stores the name of the game
     * @return returns a string stating the name of the game (NumberGuesser)
     */
    @Override
    public String getName() {
        return "NumberGuesser";
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
