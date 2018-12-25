#include "EntercCommand.h"

/**
 * Function name: EntercCommand
 * The function operation: Constructs a new EntercCommand
 */
EntercCommand::EntercCommand() {}

/**
 * Function name: EntercCommand
 * The function operation: The function gets an input from the user, and waits untill the connection is made
 * @param parameters vector<string>, int
 * @param position int
 * @return int
 */
int EntercCommand::execute(vector<string> &parameters, int position) {
    cout << "Please wait until connection established:";
    char temp[2];
    fgets(temp, sizeof(temp), stdin);
    return AMOUNT_MOVEMENT;
}
