/**
 * @author Matthias Bartolo
 * @date 30/10/2022
 */
public class Cell
{
    //Class variables
    private boolean isShowing;
    private String cellContent;

    /**
     * Constructor for objects of class Cell
     */
    public Cell()
    {
        //Initialising instance variables
        SetCellContent("00");
        SetIsShowing(false);
    }
    
    /**
     * Getter for Cell Content
     */
    public String GetCellContent(){
        return cellContent;
    }
    
    /**
     * Getter for IsShowing
     */
    public boolean GetIsShowing(){
        return isShowing;
    }
    
    /**
     * Setter for Cell Content
     */
    public void SetCellContent(String cellContent){
        this.cellContent=cellContent;
    }
    
    /**
     * Setter for IsShowing
     */
    public void SetIsShowing(boolean isShowing){
        this.isShowing=isShowing;
    }
}
