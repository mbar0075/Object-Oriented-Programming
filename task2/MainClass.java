/**
 * @author Matthias Bartolo
 * @date 30/10/2022
 */
public class MainClass
{
    public static void main(String args[]){
        //Variable winGame to indicate whether player won the game
        boolean winGame =false;

        //User input variables
        int inputRow=0,inputCol=0;

        //Declaring and Initialising class instances
        InputValidation input = new InputValidation();
        Board grid = new Board();

        //Setting mines position
        grid.SetMines();

        //Displaying Menu
        System.out.println("Welcome player to MineSweeper");
        System.out.println("\nTo win the game you must clear all the cells not containing any mines");
        System.out.println("Good Luck");

        //Game Loop
        do{
            grid.Display();

            //User input
            inputRow=input.GetIntInput("Row",0,grid.NOOFROWS-1);
            inputCol=input.GetIntInput("Column",0,grid.NOOFCOLS-1);

            //Checking if user input cell is mine
            if(!grid.IsCellMine(inputRow,inputCol)){
                //Cell isn't mine
                /*If all the adjacent cells do not contain a mine and current cell
                 * is not showing, then all adjacent cells are cleared,
                 * else only the current cell is shown
                 */
            
                Cell [][] board=grid.GetBoard();
                if(!board[inputRow][inputCol].GetIsShowing()&&board[inputRow][inputCol].GetCellContent().equals("00")){
                    grid.ShowCells(inputRow,inputCol);
                }
                else {
                    board[inputRow][inputCol].SetIsShowing(true);
                    grid.SetBoard(board);
                }
                    

                //Checking if the player won the game
                winGame=grid.CheckWin();
                if(winGame){
                    //Showing winning message
                    System.out.println("\f");
                    grid.ShowAllCells();
                    System.out.println("Congratulations, You have won the game!");
                    break;
                }
            }
            else{
                //Cell was mine and message is shown
                System.out.println("\f");
                grid.ShowAllCells();
                System.out.println("\nUnfortunately the Cell entered was a mine");
                break;
            }

            System.out.println("\f");
        }while(!winGame);

        System.out.println("\n\nThank you for playing :)");
    }
}
