#include "CircularLinkedList.h"
#include "SkincareStep.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

using SkincareRoutine = CircularLinkedList<SkincareStep>;

// Converts text to lowercase so searches are not case-sensitive.
std::string toLowercase(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(),
                   [](unsigned char character) {
                       return static_cast<char>(std::tolower(character));
                   });
    return text;
}

// Reads an integer safely and keeps prompting until the input is valid.
int readInteger(const std::string& prompt, int minimum, int maximum) {
    int value;

    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minimum && value <= maximum) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Please enter a number from " << minimum << " to "
                  << maximum << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Reads a required line of text and rejects blank input.
std::string readRequiredText(const std::string& prompt) {
    std::string value;

    do {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (value.empty()) {
            std::cout << "This field cannot be blank.\n";
        }
    } while (value.empty());

    return value;
}

// Adds the four starter products to each daily routine.
void loadStarterRoutines(SkincareRoutine& morningRoutine,
                         SkincareRoutine& nightRoutine) {
    morningRoutine.add(SkincareStep(
        "Cleanser", "Gentle Facial Cleanser", "1-2 pumps", "Morning", 1,
        "Cleansing", "Massage gently onto wet skin, then rinse."));
    morningRoutine.add(SkincareStep(
        "Serum", "Vitamin C Serum", "2-3 drops", "Morning", 2,
        "Brightening", "Apply evenly to clean, dry skin."));
    morningRoutine.add(SkincareStep(
        "Moisturizer", "Daily Moisturizer", "Pea-sized amount", "Morning", 3,
        "Hydration", "Smooth gently over the face and neck."));
    morningRoutine.add(SkincareStep(
        "Sunscreen", "Broad-Spectrum SPF 30", "2 finger lengths", "Morning", 4,
        "Sun protection", "Apply evenly as the final morning step."));

    nightRoutine.add(SkincareStep(
        "Cleanser", "Gentle Facial Cleanser", "1-2 pumps", "Night", 1,
        "Cleansing", "Massage gently onto wet skin, then rinse."));
    nightRoutine.add(SkincareStep(
        "Serum", "Niacinamide Treatment Serum", "2-3 drops", "Night", 2,
        "Texture and oil balance", "Apply evenly to clean, dry skin."));
    nightRoutine.add(SkincareStep(
        "Eye Cream", "Hydrating Eye Cream", "Rice-grain amount per eye", "Night", 3,
        "Under-eye hydration", "Pat gently around each eye using a ring finger."));
    nightRoutine.add(SkincareStep(
        "Moisturizer", "Night Moisturizer", "Pea-sized amount", "Night", 4,
        "Overnight hydration", "Smooth gently over the face and neck."));
}

// Lets the user select the Morning or Night routine.
SkincareRoutine& selectRoutine(SkincareRoutine& morningRoutine,
                               SkincareRoutine& nightRoutine,
                               std::string& timeOfDay) {
    std::cout << "\nSelect routine:\n1. Morning\n2. Night\n\n";
    int routineChoice = readInteger("Choice: ", 1, 2);

    if (routineChoice == 1) {
        timeOfDay = "Morning";
        return morningRoutine;
    }

    timeOfDay = "Night";
    return nightRoutine;
}

// Collects step information and inserts it in ascending step order.
void addSkincareStep(SkincareRoutine& morningRoutine,
                     SkincareRoutine& nightRoutine) {
    std::string timeOfDay;
    SkincareRoutine& selectedRoutine =
        selectRoutine(morningRoutine, nightRoutine, timeOfDay);

    std::string stepName = readRequiredText("Step name: ");
    std::string productName = readRequiredText("Product name: ");
    std::string amountToUse = readRequiredText("Amount to use: ");
    int stepOrder = readInteger("Step order: ", 1, 1000);
    std::string skinConcern = readRequiredText("Skin concern: ");
    std::string instructions = readRequiredText("Instructions: ");

    SkincareStep newStep(stepName, productName, amountToUse, timeOfDay,
                         stepOrder, skinConcern, instructions);
    selectedRoutine.addInOrder(
        newStep, [](const SkincareStep& left, const SkincareStep& right) {
            return left.getStepOrder() < right.getStepOrder();
        });

    std::cout << "\nSkincare step added successfully.\n";
}

// Removes a product from the selected routine by product or step name.
void removeSkincareStep(SkincareRoutine& morningRoutine,
                        SkincareRoutine& nightRoutine) {
    std::string timeOfDay;
    SkincareRoutine& selectedRoutine =
        selectRoutine(morningRoutine, nightRoutine, timeOfDay);
    std::string searchText =
        toLowercase(readRequiredText("Enter the step or product to remove: "));

    bool removed = selectedRoutine.removeIf(
        [&searchText](const SkincareStep& step) {
            return toLowercase(step.getStepName()) == searchText ||
                   toLowercase(step.getProductName()) == searchText;
        });

    if (removed) {
        std::cout << "\nSkincare step removed successfully.\n";
    } else {
        std::cout << "\nSkincare step not found.\n";
    }
}

// Searches both daily routines for a step or product name.
void searchForStep(const SkincareRoutine& morningRoutine,
                   const SkincareRoutine& nightRoutine) {
    std::string searchText =
        toLowercase(readRequiredText("Enter step or product name: "));
    auto matchesSearch = [&searchText](const SkincareStep& step) {
        return toLowercase(step.getStepName()) == searchText ||
               toLowercase(step.getProductName()) == searchText;
    };

    const SkincareStep* foundStep = morningRoutine.findIf(matchesSearch);
    if (foundStep == nullptr) {
        foundStep = nightRoutine.findIf(matchesSearch);
    }

    if (foundStep == nullptr) {
        std::cout << "\nSkincare step not found.\n";
    } else {
        std::cout << "\nStep found!\n\n";
        foundStep->displayStep();
    }
}

// Displays a complete routine in its stored order.
void displayRoutine(const SkincareRoutine& routine,
                    const std::string& routineName) {
    std::cout << "\n" << routineName << " Skincare Routine:\n\n";

    if (routine.empty()) {
        std::cout << "The skincare routine is currently empty.\n";
        return;
    }

    std::size_t displayedPosition = 1;
    routine.forEach([&displayedPosition](const SkincareStep& step) {
        std::cout << displayedPosition << ". " << step.getProductName() << '\n'
                  << "   Step: " << step.getStepName() << '\n'
                  << "   Amount: " << step.getAmountToUse() << "\n\n";
        ++displayedPosition;
    });
}

// Moves through a routine one node at a time and wraps after its final node.
void startRoutine(const SkincareRoutine& routine,
                  const std::string& routineName) {
    if (routine.empty()) {
        std::cout << "\nThe skincare routine is currently empty.\n";
        return;
    }

    std::size_t currentPosition = 0;

    while (true) {
        const SkincareStep* currentStep = routine.at(currentPosition);
        std::cout << "\n" << routineName << " ROUTINE\n\nCurrent Step:\n\n";
        currentStep->displayStep();
        std::cout << "\n1. Next Step\n2. End Routine\n\n";

        int choice = readInteger("Choice: ", 1, 2);
        if (choice == 2) {
            std::cout << "Routine ended.\n";
            return;
        }

        currentPosition = (currentPosition + 1) % routine.size();
        if (currentPosition == 0) {
            std::cout << "\nThe cycle is complete; returning to the first step.\n";
        }
    }
}

// Prints the main menu choices.
void displayMainMenu() {
    std::cout << "\n================================\n"
              << "            GLOWLOOP\n"
              << "      Skincare Routine Manager\n"
              << "================================\n\n"
              << "1. Add Skincare Step\n"
              << "2. Remove Skincare Step\n"
              << "3. Search for Skincare Step\n"
              << "4. Display Morning Routine\n"
              << "5. Display Night Routine\n"
              << "6. Start Morning Routine\n"
              << "7. Start Night Routine\n"
              << "8. Exit\n\n";
}

// Starts GlowLoop and processes menu selections until the user exits.
int main() {
    SkincareRoutine morningRoutine;
    SkincareRoutine nightRoutine;
    loadStarterRoutines(morningRoutine, nightRoutine);

    bool programIsRunning = true;
    while (programIsRunning) {
        displayMainMenu();
        int menuChoice = readInteger("Enter your choice: ", 1, 8);

        switch (menuChoice) {
            case 1:
                addSkincareStep(morningRoutine, nightRoutine);
                break;
            case 2:
                removeSkincareStep(morningRoutine, nightRoutine);
                break;
            case 3:
                searchForStep(morningRoutine, nightRoutine);
                break;
            case 4:
                displayRoutine(morningRoutine, "Morning");
                break;
            case 5:
                displayRoutine(nightRoutine, "Night");
                break;
            case 6:
                startRoutine(morningRoutine, "MORNING");
                break;
            case 7:
                startRoutine(nightRoutine, "NIGHT");
                break;
            case 8:
                programIsRunning = false;
                std::cout << "\nThank you for using GlowLoop!\n";
                break;
        }
    }

    return 0;
}
