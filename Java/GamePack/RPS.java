import java.util.Random;

public class RPS extends Game {
    private Random rng;
    private int requiredWins;
    private int maxLosses;
    private int wins, losses;
    private int moveOptions;
    private String aiMove;
    private int playerWins = 0;
    private int playerLosses = 0;
    /**
     * The constructor for the RPS (rock paper scissors) class.
     * @param rng a variable of type Random to generate the AI's move
     * @param requiredWins the amount of wins the player must reach before that player wins the set
     * @param maxLosses the number of losses the player is allowed to get before the AI wins the set
     */
    public RPS(Random rng, int requiredWins, int maxLosses) {
        this.rng = rng;
        this.requiredWins = requiredWins;
        this.maxLosses = maxLosses;
    }

    /**
     * This function prepares the game for using the 'settings' given by the constructor.
     * @return returns a message stating the rules, and the required wins/losses before the player wins/loses.
     */
    @Override
    protected String prepToPlay() {
        wins = 0;
        losses = 0;
        return "Enter rock, paper, or scissors. Beat me "+requiredWins+" times before I win "+maxLosses+" times!";
    }

    /**
     * This function checks if the game has ended by looking if the required wins have been reached,
     * or the max number of losses has been reached.
     * @return returns a value of true if the game has ended, or false if the game is still being played
     */
    @Override
    protected boolean isOver() {
        return wins == requiredWins || losses == maxLosses;
    }

    /**
     * This function checks if a move is valid or not. In RPS, the move is valid if the player enters
     * rock, paper, or scissors. Any other move will prompt an invalid move.
     * @param move a string variable that holds the move the user entered
     * @return returns true if the move is valid, and false if the move is invalid
     */
    @Override
    protected boolean isValid(String move) {
        return move.equals("rock") || move.equals("paper") || move.equals("scissors") || move.equals("quit");
    }

    /**
     * This function processes the move. It first generates a random move for the AI. Then it checks to
     * see if the move the player entered beats the move generated for the AI. This function also increments
     * the number of wins/losses depending on if the play won or lost.
     * @param move a string variable that holds the move the user entered
     * @return returns a string stating if the player won, lost, or tied
     */
    @Override
    protected String processMove(String move) {
        moveOptions = rng.nextInt(3);
        if (moveOptions == 0) {
            aiMove = "rock";
        } else if (moveOptions == 1) {
            aiMove = "paper";
        } else {
            aiMove = "scissors";
        }

        if (aiMove.equals("rock")) {
            if (move.equals("paper")) {
                wins += 1;
                return "rock vs. paper you Win";
            } else if (move.equals("scissors")) {
                losses += 1;
                return "rock vs. scissors you lose";
            }
        } else if (aiMove.equals("paper")) {
            if (move.equals("scissors")) {
                wins += 1;
                return "paper vs. scissors you Win";
            } else if (move.equals("rock")) {
                losses += 1;
                return "paper vs. rock you lose";
            }
        } else {
            if (move.equals("rock")) {
                wins += 1;
                return "scissors vs. rock you Win";
            } else if (move.equals("paper")) {
                losses += 1;
                return "scissors vs. paper you lose";
            }
        }

        return aiMove + " vs. " + move + " We Tie";
    }

    /**
     * Outputs the final message of the game (who won the set)
     * @return returns a string that either states if the player won the set, or lost the set
     */
    @Override
    protected String finalMessage() {
        if (wins == requiredWins) {
            playerWins += 1;
            return "You win the set";
        } else {
            playerLosses += 1;
            return "you lose the set";
        }
    }

    /**
     * Gets the name of the game.
     * @return returns a string stating the name of the game
     */
    @Override
    public String getName() {
        return "Rock Paper Scissors";
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
