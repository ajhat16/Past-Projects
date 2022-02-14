import java.util.Scanner;

public abstract class Game {
    protected abstract String prepToPlay();
    protected abstract boolean isOver();
    protected abstract boolean isValid(String move);
    protected abstract String processMove(String move);
    protected abstract String finalMessage();
    public abstract String getName();
    public abstract int getPlayerWins();
    public abstract int getPlayerLosses();


    /**
     * This function holds the general formula for how every game is played. The function prepares the game,
     * then continues to prompt for the next move until 'quit' is entered or the game ends.
     * @param user a scanner used throughout each file of the code.
     */
    public void play(Scanner user) {
        String move;
        String processStatement;
        System.out.println(prepToPlay());

        while (!isOver()) {
            System.out.print("Enter Your Move or 'quit' to quit> ");
            move = user.next();
            while (!isValid(move)) {
                System.out.print("Invalid Move! try again> ");
                move = user.next();
            }
            if (move.equals("quit")) {
                break;
            }
            processStatement = processMove(move);
            if (processStatement != null) {
                System.out.println(processStatement);
            }
        }
        System.out.println(finalMessage());
    }
}


