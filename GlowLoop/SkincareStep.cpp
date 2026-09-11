
// SkincareStep.cpp implements the SkincareStep class declared in
// SkincareStep.h: its constructors, its accessors, and the displayStep()
// routine used to print a step's details to the console.

#include "SkincareStep.h"

#include <iostream>

// Creates a blank skincare step with a default order of zero.
SkincareStep::SkincareStep() : stepOrder(0) {}

// Initializes all information needed to display and organize a skincare step.
SkincareStep::SkincareStep(const std::string &stepName,
                           const std::string &productName,
                           const std::string &amountToUse,
                           const std::string &timeOfDay, int stepOrder,
                           const std::string &skinConcern,
                           const std::string &instructions)
    : stepName(stepName), productName(productName), amountToUse(amountToUse),
      timeOfDay(timeOfDay), stepOrder(stepOrder), skinConcern(skinConcern),
      instructions(instructions) {}

// Prints all stored information in a readable format. The stored order
// value is only used to pick an insertion point, so it is not printed;
// when the caller supplies a live position, that is shown instead.
void SkincareStep::displayStep(int position) const {
  std::cout << "Step: " << stepName << '\n'
            << "Product: " << productName << '\n'
            << "Amount: " << amountToUse << '\n'
            << "Time of Day: " << timeOfDay << '\n';

  if (position >= 0) {
    std::cout << "Step Order: " << position << '\n';
  }

  std::cout << "Skin Concern: " << skinConcern << '\n'
            << "Instructions: " << instructions << '\n';
}

// Returns the general step name.
const std::string &SkincareStep::getStepName() const { return stepName; }

// Returns the specific product name.
const std::string &SkincareStep::getProductName() const { return productName; }

// Returns the recommended application amount.
const std::string &SkincareStep::getAmountToUse() const { return amountToUse; }

// Returns the routine's time of day.
const std::string &SkincareStep::getTimeOfDay() const { return timeOfDay; }

// Returns the numerical position of the step.
int SkincareStep::getStepOrder() const { return stepOrder; }

// Returns the product's intended skin concern.
const std::string &SkincareStep::getSkinConcern() const { return skinConcern; }

// Returns the directions for applying the product.
const std::string &SkincareStep::getInstructions() const {
  return instructions;
}
