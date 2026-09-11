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
    SkincareStep(const std::string& stepName,
                 const std::string& productName,
                 const std::string& amountToUse,
                 const std::string& timeOfDay,
                 int stepOrder,
                 const std::string& skinConcern,
                 const std::string& instructions);

    // Displays every detail about this skincare step.
    void displayStep() const;

    // Returns the general type of skincare step.
    const std::string& getStepName() const;

    // Returns the product's name.
    const std::string& getProductName() const;

    // Returns the recommended amount to apply.
    const std::string& getAmountToUse() const;

    // Returns whether the step belongs to Morning or Night.
    const std::string& getTimeOfDay() const;

    // Returns the requested position in the routine.
    int getStepOrder() const;

    // Returns the concern addressed by the product.
    const std::string& getSkinConcern() const;

    // Returns the application directions.
    const std::string& getInstructions() const;
};

#endif
