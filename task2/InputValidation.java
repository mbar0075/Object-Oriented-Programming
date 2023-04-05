import java.util.Scanner;
import java.util.InputMismatchException;

/**
 * @author Matthias Bartolo
 * @date 02/11/2022
 */
public class InputValidation {
    // Declaring and Initialising Scanner instance
    private static Scanner sc = new Scanner(System.in);

    /**
     * Default Constructor
     */

    public InputValidation() {

    }

    /**
     * Method for getting and validating an integer type input
     */
    public int GetIntInput(String inputText, int minInputRange, int maxInputRange) {
        // Variable which will hold the user input
        int uinput = minInputRange - 1;

        // Looping until the correct user input is inputted
        do {
            // try catch being used to catch exceptions
            try {
                System.out.println("Please Input " + inputText + ":");
                uinput = sc.nextInt();
            } catch (InputMismatchException e) {
                // Setting condition to display error statement
                uinput = minInputRange - 1;
                // Clearing Scanner
                sc.nextLine();
            }

            // Error message is displayed
            if (uinput < minInputRange || uinput > maxInputRange) {
                System.out
                        .println("\nInvalid Input\nInput must be in range of: " + minInputRange + "-" + maxInputRange);
            }
        } while (uinput < minInputRange || uinput > maxInputRange);
        // Returning validated user input
        return uinput;
    }

}
