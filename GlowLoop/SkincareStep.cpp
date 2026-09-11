#include "SkincareStep.h"

#include <iostream>

// Creates a blank skincare step with a default order of zero.
SkincareStep::SkincareStep() : stepOrder(0) {}

// Initializes all information needed to display and organize a skincare step.
SkincareStep::SkincareStep(const std::string& stepName,
                           const std::string& productName,
                           const std::string& amountToUse,
                           const std::string& timeOfDay,
                           int stepOrder,
                           const std::string& skinConcern,
                           const std::string& instructions)
    : stepName(stepName),
      productName(productName),
      amountToUse(amountToUse),
      timeOfDay(timeOfDay),
      stepOrder(stepOrder),
      skinConcern(skinConcern),
      instructions(instructions) {}

// Prints all stored information in a readable format.
void SkincareStep::displayStep() const {
    std::cout << "Step: " << stepName << '\n'
              << "Product: " << productName << '\n'
              << "Amount: " << amountToUse << '\n'
              << "Time of Day: " << timeOfDay << '\n'
              << "Step Order: " << stepOrder << '\n'
              << "Skin Concern: " << skinConcern << '\n'
              << "Instructions: " << instructions << '\n';
}

// Returns the general step name.
const std::string& SkincareStep::getStepName() const {
    return stepName;
}

// Returns the specific product name.
const std::string& SkincareStep::getProductName() const {
    return productName;
}

// Returns the recommended application amount.
const std::string& SkincareStep::getAmountToUse() const {
    return amountToUse;
}

// Returns the routine's time of day.
const std::string& SkincareStep::getTimeOfDay() const {
    return timeOfDay;
}

// Returns the numerical position of the step.
int SkincareStep::getStepOrder() const {
    return stepOrder;
}

// Returns the product's intended skin concern.
const std::string& SkincareStep::getSkinConcern() const {
    return skinConcern;
}

// Returns the directions for applying the product.
const std::string& SkincareStep::getInstructions() const {
    return instructions;
}
