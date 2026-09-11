
// SkincareStep.h declares the SkincareStep class, which stores one product
// application (name, product, amount, timing, order, concern, and
// instructions) used within a GlowLoop skincare routine.

#ifndef SKINCARE_STEP_H
#define SKINCARE_STEP_H

#include <string>

// Describes one product application within a skincare routine.
class SkincareStep {
private:
  std::string stepName;
  std::string productName;
  std::string amountToUse;
  std::string timeOfDay;
  int stepOrder;
  std::string skinConcern;
  std::string instructions;

public:
  // Creates a blank skincare step.
  SkincareStep();

  // Creates a fully specified skincare step.
  SkincareStep(const std::string &stepName, const std::string &productName,
               const std::string &amountToUse, const std::string &timeOfDay,
               int stepOrder, const std::string &skinConcern,
               const std::string &instructions);

  // Displays every detail about this skincare step. When the caller knows
  // the step's live position in its routine, it passes a 1-based
  // "position" so the printed order always matches the current list
  // instead of the (possibly stale or duplicated) stored order value.
  void displayStep(int position = -1) const;

  // Returns the general type of skincare step.
  const std::string &getStepName() const;

  // Returns the product's name.
  const std::string &getProductName() const;

  // Returns the recommended amount to apply.
  const std::string &getAmountToUse() const;

  // Returns whether the step belongs to Morning or Night.
  const std::string &getTimeOfDay() const;

  // Returns the requested position in the routine.
  int getStepOrder() const;

  // Returns the concern addressed by the product.
  const std::string &getSkinConcern() const;

  // Returns the application directions.
  const std::string &getInstructions() const;
};

#endif
