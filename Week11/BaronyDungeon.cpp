#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Max depth of the dungeon
const int MAX_DEPTH = 10;

// Randomizing the floor where the exit is
const int EXIT_ROOM_DEPTH = rand() % MAX_DEPTH;

// Function showing current floor with ascii art
void printRoomASCII(int depth) {
    cout << "\nYou enter Room #" << depth << endl;
    cout << R"(
      _____
     /     \
    | () () |
     \  ^  /
      |||||
      |||||)";
    cout << "\n" << endl;
}

// Function stopping exploration past max depth
bool exploreRoom(int depth) {
    if (depth >= MAX_DEPTH) {
        cout << "\nYou've reached the deepest part of the dungeon...\n";
        cout << "But it's a dead end. You have no choice but to climb back up.\n";
        return false;
    }

    printRoomASCII(depth);

    // Random events
    int event = rand() % 5;

    if (depth == EXIT_ROOM_DEPTH) {
        cout << "You found the EXIT of the dungeon! You are free! \n";
        return true;
    } else if (event == 0) {
        cout << "A trapdoor opens above you... A boulder drops and squashes you!\n";
        return false;
    } else if (event == 1) {
        cout << "A skeleton attacks! You bravely smash it to pieces.\n";
    } else if (event == 2) {
        cout << "You found a small pile of gold. (+10 gold)\n";
    } else if (event == 3) {
        cout << "You stumble into an ogre but you did not aggro it and sneak away.\n";
    } else if (event == 4) {
        cout << "You walk into a gnome with a lightning staff, he fries you instantly. \n";
        return false;
    } else if (event == 5) {
        cout << "You see a slime approach you... You efforlessly chop it to pieces.\n";
    } else if (event == 6) {
        cout << "A large rat squrries toward you, you squash it under your boot.\n";
    } else if (event == 7) {
        cout << "You see a bandit busy counting the gold from his last kill... You sneak up to him and stab him in the back killing him instantly. (+25 gold)\n";
    } else if (event == 8) {
        cout << "You come across a friendly looking shopkeeper. He may be friendly but his prices aren't... You leave without buying anything.\n";
    } else if (event == 9) {
        cout << "You come across a large fountain. You reluctantly decide to drink from it... You feel pretty good after (+10 health)\n";
    } else {
        cout << "The room is eerily quiet... You seem safe... for now\n";
    }

    // Player chooses next action
    cout << "\nChoose your path: [L]eft, [R]ight, [F]orward, or [E]xit dungeon: ";
    char choice;
    cin >> choice;

    if (choice == 'E' || choice == 'e') {
        cout << "You decide to exit the dungeon early. You are a coward but alive nonetheless!\n";
        return false;
    }

    // Recursive call adding to the floor count until the player escapes or dies
    return exploreRoom(depth + 1);
}

int main() {

    // Randomizing exit based on the time the program is executed
    srand(time(0));

    cout << "Welcome to the Dungeon of Barony \n";
    cout << "You are an adventurer seeking treasure and glory.\n";
    cout << "Beware! Danger lurks in every corner...\n";

    bool success = exploreRoom(1);

    if (success) {
        cout << "\n Congratulations, hero! You survived the Barony Dungeon!\n";
    } else {
        cout << "\n Your journey ends here... The dungeon claims another.\n";
    }

    return 0;
}
