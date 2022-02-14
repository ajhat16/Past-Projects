import java.util.Random;
import java.util.Scanner;

public class GameGrabber {
    private Game[] games;
    private Scanner user;
    private int menuChoice;
    private boolean choiceIsGood;
    private Game currGame;

    /**
     * Constructor for the GameGrabber class
     * @param games an array of class Game that stores the possible games that can be played
     * @param user a Scanner for all user inputs in the code
     */
    public GameGrabber(Game[] games, Scanner user) {
        this.games = games;
        this.user = user;
    }

    /**
     * A function to output the menu where the player can choose what game they would like to play,
     * or if they would like to quit. If they chose a game, the function calls the play function
     * for the game they chose. When the user is done playing the game, the menu is output again,
     * and the process repeats itself. If the choice is invalid, it prompts the user to make a
     * different choice. The menu also shows the number of wins and losses for each game separately.
     */
    public void doMenu() {
        while(menuChoice != games.length) {
            for (int i = 0; i < games.length; i++) {
                currGame = games[i];
                if (currGame.getPlayerWins() == 1 && currGame.getPlayerLosses() == 1) {
                    if (currGame.getName().equals("NumberGuesser")) {
                        System.out.println(i + ") Number Guesser (" + currGame.getPlayerWins() + " Win, " + currGame.getPlayerLosses() + " Loss)");
                    } else {
                        System.out.println(i + ") " + currGame.getName() + " (" + currGame.getPlayerWins() + " Win, " + currGame.getPlayerLosses() + " Loss)");
                    }
                } else if (currGame.getPlayerLosses() == 1) {
                    if (currGame.getName().equals("NumberGuesser")) {
                        System.out.println(i + ") Number Guesser (" + currGame.getPlayerWins() + " Wins, " + currGame.getPlayerLosses() + " Loss)");
                    } else {
                        System.out.println(i + ") " + currGame.getName() + " (" + currGame.getPlayerWins() + " Wins, " + currGame.getPlayerLosses() + " Loss)");
                    }
                } else if (currGame.getPlayerWins() == 1) {
                    if (currGame.getName().equals("NumberGuesser")) {
                        System.out.println(i + ") Number Guesser (" + currGame.getPlayerWins() + " Win, " + currGame.getPlayerLosses() + " Losses)");
                    } else {
                        System.out.println(i + ") " + currGame.getName() + " (" + currGame.getPlayerWins() + " Win, " + currGame.getPlayerLosses() + " Losses)");
                    }
                } else {
                    if (currGame.getName().equals("NumberGuesser")) {
                        System.out.println(i + ") Number Guesser (" + currGame.getPlayerWins() + " Wins, " + currGame.getPlayerLosses() + " Losses)");
                    } else {
                        System.out.println(i + ") " + currGame.getName() + " (" + currGame.getPlayerWins() + " Wins, " + currGame.getPlayerLosses() + " Losses)");
                    }
                }
            }
            System.out.println(games.length + ") Quit");
            choiceIsGood = false;
            while(!choiceIsGood) {
                System.out.print("Pick a game (0-" + games.length + ") ");
                menuChoice = user.nextInt();
                if (menuChoice >= 0 && menuChoice <= games.length) {
                    choiceIsGood = true;
                }
            }
            if (menuChoice == games.length) {
                break;
            } else {
                games[menuChoice].play(user);
            }
        }
        System.out.println("goodbye");
    }

    public static void main(String[] args) {

        Scanner user = new Scanner(System.in);
        Random rng = new Random();
        WordsList words = new WordsList(rng);
        Hangman hangman = new Hangman(words, 3, 5, 20);
        NumberGuesser numberGuesser = new NumberGuesser(rng, 100, 8);
        RPS rps = new RPS(rng, 2, 2);
        WordJumble wordJumble = new WordJumble(words, rng, 3, 5, 5);
        Minesweeper minesweeper = new Minesweeper(6,6,rng);
        Game[] games = new Game[]{hangman, numberGuesser, rps, wordJumble, minesweeper};
        GameGrabber gameGrabber = new GameGrabber(games, user);
        gameGrabber.doMenu();
    }
}
