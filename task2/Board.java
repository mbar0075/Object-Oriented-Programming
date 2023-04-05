import java.util.Random;
/**
 * @author Matthias Bartolo
 * @date 30/10/2022
 */
public class Board
{
    //Initialising constants
    public static final int NOOFROWS = 16;
    public static final int NOOFCOLS = 16;
    public static final int NOOFMINES = 40;
    //Declaring board array of cells
    private Cell board[][]= new Cell[NOOFROWS][NOOFCOLS];

    /**
     * Default Constructor to initialise board
     */
    public Board()
    {
        //Calling the Cell Constructor for every Cell in the Board
        for(int row=0; row<NOOFROWS;row++){
            for(int col=0; col<NOOFCOLS;col++){
                board[row][col]=new Cell();
            } 
        }
    }

    /**
     * Method to set the mine positions on the board
     */
    public void SetMines()
    {
        //Declaring and initialising Method variables
        int randomRowPos=0;
        int randomColPos=0;

        //Declaring and initialising random instance
        Random random=new Random();

        //Looping for all the number of mines
        for(int m=0; m<NOOFMINES;m++){
            //Getting a random row and column
            randomRowPos=random.nextInt(NOOFROWS);
            randomColPos=random.nextInt(NOOFCOLS);

            //Continue to loop until finding a cell position which doesn't contain a mine
            while(board[randomRowPos][randomColPos].GetCellContent().equals("XX")){
                randomRowPos=random.nextInt(NOOFROWS);
                randomColPos=random.nextInt(NOOFCOLS);
            }
            //Assign mine to current cell
            board[randomRowPos][randomColPos].SetCellContent("XX");
            //Incrementing all the adjacent cells
            IncrementAdjacentCells(randomRowPos,randomColPos);
        }
    }

    /**
     * Method to display board
     */
    public void Display()
    {
        //Displaying column numbers
        System.out.print("--");
        for(int col=0; col<NOOFCOLS;col++){
            if(col<10)
                System.out.print("  0"+col);
            else
                System.out.print("  "+col);
        } 
        System.out.println();    
        //Displaying the respective cells based on which are hidden
        for(int row=0; row<NOOFROWS;row++){
            //Displaying row numbers
            if(row<10)
                System.out.print("0"+row);
            else
                System.out.print(row);
            //Displaying cells
            for(int col=0; col<NOOFCOLS;col++){
                if(board[row][col].GetIsShowing())
                    System.out.print("  "+board[row][col].GetCellContent());
                else
                    System.out.print("  --");
            }
            System.out.println();
        }
    }

    /**
     * Method to check if cell is a mine
     */
    public boolean IsCellMine(int row, int col)
    {
        //Respective return statements returned  if cell is mine
        if(board[row][col].GetCellContent().equals("XX"))
            return true;
        else
            return false;
    }

    /**
     * Method to check if cell is within board range
     */
    private boolean IsCellValid(int row, int col)
    {
        //Respective return statements returned if cell is in valid range
        if((row<0)||(row>=NOOFROWS)||(col<0)||(col>=NOOFCOLS))
            return false;
        else
            return true;
    }

    /**
     * Method to increment all the adjacent cells of a mine
     */
    private void IncrementAdjacentCells(int row, int col)
    {
        //Looping through all the 8 adjacent cells
        for(int rowOffset=-1; rowOffset<=1;rowOffset++){
            for(int colOffset=-1; colOffset<=1;colOffset++){
                /*Skipping iteration for colOffset=0 and rowOffset=0,
                 * as it indicates current mine position
                 */
                if(colOffset==0&&rowOffset==0)
                    continue;
                /*Checking Neighbors whether they are valid and whether they are mines,
                 * if they are not mines and are valid cells,
                 * then cells will be incremented by 1
                 */
                if(IsCellValid(row+rowOffset,col+colOffset)&&!IsCellMine(row+rowOffset,col+colOffset)){
                    int cellCount=Integer.parseInt(board[row+rowOffset][col+colOffset].GetCellContent());
                    board[row+rowOffset][col+colOffset].SetCellContent("0"+Integer.toString(cellCount+1));
                }
            }
        }
    }

    /**
     * Method to show all the 8 adjacent cells and current cell
     */
    public void ShowCells(int row, int col)
    {
        //Looping through all the 8 adjacent cells and current cell
        for(int rowOffset=-1; rowOffset<=1;rowOffset++){
            for(int colOffset=-1; colOffset<=1;colOffset++){
                /*Setting all 9 cells isShowing to true
                 */
                if(IsCellValid(row+rowOffset,col+colOffset)){
                    board[row+rowOffset][col+colOffset].SetIsShowing(true);
                }
            }
        }
    }

    /**
     * Method to check whether player has won by counting all the cells which are 
     * showing
     */
    public boolean CheckWin()
    {
        //Declaring and initialising Method variables
        int cellcounter=0;

        /*Checking every Cell, whether it is cleared, and incrementing counter respectively
         */
        for(int row=0; row<NOOFROWS;row++){
            for(int col=0; col<NOOFCOLS;col++){
                if(board[row][col].GetIsShowing())
                    cellcounter++;
            }
        }

        //Respective return statements returned
        if(((NOOFROWS*NOOFCOLS)-NOOFMINES)>cellcounter)
            return false;
        else 
            return true;
    }

    /**
     * Method used to show all the cells in the board
     */
    public void ShowAllCells()
    {
        //Setting all cells isShowing to true
        for(int row=0; row<NOOFROWS;row++){
            for(int col=0; col<NOOFCOLS;col++){
                board[row][col].SetIsShowing(true);
            }
        }

        //Calling the display method
        Display();
    }
    
    /**
     * Getter for board
     */
    public Cell [][] GetBoard(){
        return board;
    }
    
    /**
     * Setter for board
     */
    public void SetBoard(Cell [][] board){
        this.board=board;
    }
}
