
import java.sql.Array;
import java.util.Random;

public class Minesweeper extends Game {
    private int playerWins = 0;
    private int playerLosses = 0;
    private int width, height, numMines, minesAdded;
    private Random rng;
    private String startingPosition;
    private int[][] everyPrevNumber;
    private boolean alreadyGenerated, over;
    private int mineX, mineY, x, y;
    private char[][] solvedGrid, hiddenGrid;


/**
     * Constructor for the Minesweeper class.
     * @param width an int variable for setting the width of the grid
     * @param height an int variable for setting the height of the grid
     * @param rng a Random variable used for generating the mine locations
     */

    public Minesweeper(int width, int height, Random rng) {
        this.width = width;
        this.height = height;
        this.rng = rng;
    }


/**
     * A recursive helper function for the processMove function. This function checks if the
     * current move is a zero, and tries to reveal adjacent tiles that are also zero to
     * reveal larger blocks of the board in less moves.
     * @param moveX the move in the x direction
     * @param moveY the move in the y direction
     * @return a string version of the hiddenGrid variable (by using the overridden toString())
     */

    protected String checkAdjacentZeros(int moveX, int moveY) {
        if (solvedGrid[moveY][moveX] == '0') {
            if (moveX != 0 && solvedGrid[moveY][moveX - 1] != hiddenGrid[moveY][moveX - 1]) {
                hiddenGrid[moveY][moveX - 1] = solvedGrid[moveY][moveX - 1];
                checkAdjacentZeros(moveX - 1, moveY);
            }
            if (moveX != width - 1 && solvedGrid[moveY][moveX + 1] != hiddenGrid[moveY][moveX + 1]) {
                hiddenGrid[moveY][moveX + 1] = solvedGrid[moveY][moveX + 1];
                checkAdjacentZeros(moveX + 1, moveY);
            }
            if (moveY != 0 && solvedGrid[moveY - 1][moveX] != hiddenGrid[moveY - 1][moveX]) {
                hiddenGrid[moveY - 1][moveX] = solvedGrid[moveY - 1][moveX];
                checkAdjacentZeros(moveX, moveY - 1);
            }
            if (moveY != height - 1 && solvedGrid[moveY + 1][moveX] != hiddenGrid[moveY + 1][moveX]) {
                hiddenGrid[moveY + 1][moveX] = solvedGrid[moveY + 1][moveX];
                checkAdjacentZeros(moveX, moveY + 1);
            }
        }
        return toString();
    }


/**
     * A helper function for prepToPlay. This function is used to add the numbers that appear on the
     * grid to the grid. Each number represents the number of mines adjacent or diagonal to it.
     * @return an updated version of solvedGrid
     */

    protected char[][] addNumbers() {
        char c;
        int number = 0;
        for (int i = 0; i < solvedGrid.length; i++) {
            for (int j = 0; j < width; j++) {
                if (solvedGrid[i][j] != '*') {
                    if (i == 0) {
                        if (j == 0) {
                            if (solvedGrid[i+1][j] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i+1][j + 1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j+1] == '*') {
                                number += 1;
                            }
                            c = Character.forDigit(number, 10);
                            solvedGrid[i][j] = c;
                            number = 0;
                        } else if (j == width - 1) {
                            if (solvedGrid[i+1][j] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i+1][j - 1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j-1] == '*') {
                                number += 1;
                            }
                            c = Character.forDigit(number, 10);
                            solvedGrid[i][j] = c;
                            number = 0;
                        } else {
                            if (solvedGrid[i+1][j] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i+1][j-1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i+1][j+1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j+1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j-1] == '*') {
                                number += 1;
                            }
                            c = Character.forDigit(number, 10);
                            solvedGrid[i][j] = c;
                            number = 0;
                        }
                    } else if (i == height - 1) {
                        if (j == 0) {
                            if (solvedGrid[i-1][j] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i-1][j+1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j+1] == '*') {
                                number += 1;
                            }
                            c = Character.forDigit(number, 10);
                            solvedGrid[i][j] = c;
                            number = 0;
                        } else if (j == width - 1) {
                            if (solvedGrid[i-1][j] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i-1][j-1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j-1] == '*') {
                                number += 1;
                            }
                            c = Character.forDigit(number, 10);
                            solvedGrid[i][j] = c;
                            number = 0;
                        } else {
                            if (solvedGrid[i-1][j] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i-1][j-1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i-1][j+1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j+1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j-1] == '*') {
                                number += 1;
                            }
                            c = Character.forDigit(number, 10);
                            solvedGrid[i][j] = c;
                            number = 0;
                        }
                    } else {
                        if (j == 0) {
                            if (solvedGrid[i-1][j] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i-1][j+1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j+1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i+1][j+1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i+1][j] == '*') {
                                number += 1;
                            }
                            c = Character.forDigit(number, 10);
                            solvedGrid[i][j] = c;
                            number = 0;
                        } else if (j == width - 1) {
                            if (solvedGrid[i-1][j] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i-1][j-1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j-1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i+1][j-1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i+1][j] == '*') {
                                number += 1;
                            }
                            c = Character.forDigit(number, 10);
                            solvedGrid[i][j] = c;
                            number = 0;
                        } else {
                            if (solvedGrid[i - 1][j] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i - 1][j - 1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i - 1][j + 1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j + 1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i][j - 1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i + 1][j + 1] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i + 1][j] == '*') {
                                number += 1;
                            }
                            if (solvedGrid[i + 1][j - 1] == '*') {
                                number += 1;
                            }
                            c = Character.forDigit(number, 10);
                            solvedGrid[i][j] = c;
                            number = 0;
                        }
                    }
                }
            }
        }

        return solvedGrid;
    }


/**
     * Prepares the game for the next play through by initializing variables, setting up the
     * Minesweeper grid, giving instructions, and giving a safe starting location for the
     * player, as well as the number of mines in the grid.
     * @return a string stating the purpose/rules of the game, the number of mines, the move format,
     * and a safe place for the user to start.
     */

    @Override
    protected String prepToPlay() {
        minesAdded = 0;
        numMines = (width * height) / 6;
        solvedGrid = new char[height][width];
        everyPrevNumber = new int[numMines][2];
        over = false;
        for (int i = 0; i < numMines; i++) {
            everyPrevNumber[i][0] = -1;
            everyPrevNumber[i][1] = -1;
        }

        while (minesAdded != numMines) {
            alreadyGenerated = false;
            mineX = rng.nextInt(width);
            mineY = rng.nextInt(height);
            for (int[] i : everyPrevNumber) {
                if (i[0] == mineX && i[1] == mineY) {
                    alreadyGenerated = true;
                    break;
                }
            }
            if (!alreadyGenerated) {
                solvedGrid[mineY][mineX] = '*';
                minesAdded += 1;
                everyPrevNumber[minesAdded - 1][0] = mineX;
                everyPrevNumber[minesAdded - 1][1] = mineY;
            }
        }
        solvedGrid = addNumbers();
        hiddenGrid = new char[height][width];

        int safeX = 0;
        int safeY = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (solvedGrid[i][j] == '0') {
                    safeX = j;
                    safeY = i;
                }
            }
        }
        x = safeX;
        y = safeY;

        return "Minesweeper is played by revealing tiles on the grid. The number you reveal means that many mines are" +
                "adjacent or diagonal to it. Try to reveal the entire grid without hitting a mine. Enter your move" +
                "in the form \"x,y\". There are " + numMines + " mines. A safe starting point is " + safeX + "," + safeY +
                "\n" + toString();
    }


    /**
     * Checks if the game is over. The game is over if the player hits a mine, or the player reveals
     * every tile (except for the mines).
     * @return true if the game is over, false if otherwise
     */

    @Override
    protected boolean isOver() {
        if (solvedGrid[y][x] == '*') {
            return true;
        }

        for (int i = 0; i < hiddenGrid.length; i++) {
            for (int j = 0; j < width; j++) {
                if (!Character.isDigit(hiddenGrid[i][j])) {
                    if (solvedGrid[i][j] != '*') {
                        return false;
                    }
                }
            }
        }
        return true;
    }


/**
     * Checks if a move is valid or not. A move is valid if it is "quit" or if it is in the correct
     * format (as stated in prepToPlay).
     * @param move a String of the player's move
     * @return returns true if the move is valid, false if otherwise
     */

    @Override
    protected boolean isValid(String move) {
        try {
            if (move.equals("quit")) {
                over = true;
                return true;
            }
            if (move.contains(",")) {
                Integer.parseInt(move.substring(0, move.indexOf(",")));
                Integer.parseInt(move.substring(move.indexOf(",") + 1));
                return true;
            }
        } catch (NumberFormatException e) {
            return false;
        }
        return false;
    }


/**
     * A function for processing the move a player makes. It processes the move by revealing the tile
     * the player chose. It also calls the checkAdjacentZeros function to see if more tiles can be
     * revealed at the same time.
     * @param move a String containing the player's move
     * @return a String version of hiddenGrid
     */

    @Override
    protected String processMove(String move) {
        x = Integer.parseInt(move.substring(0, move.indexOf(",")));
        y = Integer.parseInt(move.substring(move.indexOf(",") + 1));

        hiddenGrid[y][x] = solvedGrid[y][x];

        return checkAdjacentZeros(x, y);
    }


/**
     * A function to return the game's final message. The final message states if the player wins
     * or if the player loses. It also shows the fully solved grid.
     * @return a String stating the grid and if a player won or lost
     */

    @Override
    protected String finalMessage() {
        hiddenGrid = solvedGrid;

        if (solvedGrid[y][x] == '*' || over) {
            playerLosses += 1;
            return "You Lose. Solved Grid:\n" + toString();
        }
        playerWins += 1;
        return "You Win! Solved Grid:\n" + toString();
    }


/**
     * A function to get the name of the game
     * @return a String stating the name of the game (Minesweeper)
     */

    @Override
    public String getName() {
        return "Minesweeper";
    }


/**
     * A function to get the amount of wins a player has
     * @return an amount of wins a player has
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


/**
     * A function used to convert hiddenGrid into a string
     * @return hiddenGrid as a string
     */

    @Override
    public String toString() {
        String board = "";

        for (int i = 0; i < hiddenGrid.length; i++) {
            for (int j = 0; j < width; j++) {
                board += hiddenGrid[i][j];
            }
            if (i != hiddenGrid.length - 1) {
                board += "\n";
            }

        }

        return board;
    }
}

