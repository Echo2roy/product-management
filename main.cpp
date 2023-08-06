#include <iostream>

#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "json.hpp"


using json = nlohmann::json;


class Product {
private:
    std::string code;
    std::string name;
    std::string brand;
    std::string description;
    std::string dosage_instruction;
    double price;
    int quantity;
    std::string category;
    bool requires_prescription;

public:
    // Constructor
    Product(std::string code, std::string name, std::string brand, std::string description,
            std::string dosage_instruction, double price, int quantity,
            std::string category, bool requires_prescription)
            : code(code), name(name), brand(brand), description(description),
              dosage_instruction(dosage_instruction), price(price),
              quantity(quantity), category(category), requires_prescription(requires_prescription) {
    }

    // Setter methods
    void setName(const std::string& newName) { name = newName; }
    void setBrand(const std::string& newBrand) { brand = newBrand; }
    void setDescription(const std::string& newDescription) { description = newDescription; }
    void setDosageInstruction(const std::string& newDosageInstruction) { dosage_instruction = newDosageInstruction; }
    void setPrice(double newPrice) { price = newPrice; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setCategory(const std::string& newCategory) { category = newCategory; }
    void setRequiresPrescription(bool newRequiresPrescription) { requires_prescription = newRequiresPrescription; }

    // Getter methods
    std::string getCode() const {return code; }
    std::string getName() const { return name; }
    std::string getBrand() const { return brand; }
    std::string getDescription() const { return description; }
    std::string getDosageInstruction() const { return dosage_instruction; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    std::string getCategory() const { return category; }
    bool requiresPrescription() const { return requires_prescription; }

    // Function to generate a random string of given length
    std::string generateRandomString(int length) {
        const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, characters.size() - 1);

        std::stringstream ss;
        for (int i = 0; i < length; ++i) {
            ss << characters[dis(gen)];
        }

        return ss.str();
    }
};

std::string generateRandomString(int length) {
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characters.size() - 1);

    std::stringstream ss;
    for (int i = 0; i < length; ++i) {
        ss << characters[dis(gen)];
    }

    return ss.str();
}

// Function to save product information to a JSON file
void saveProductToJson(const Product& product) {
    json productJson;

    // Check if the file already exists
    std::string filename = "products.json";
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        // Read the existing JSON data from the file
        inputFile >> productJson;
        inputFile.close();
    }

    // Add the new product information as a new record in the JSON data
    productJson.push_back({
        {"code", product.getCode()},
        {"name", product.getName()},
        {"brand", product.getBrand()},
        {"description", product.getDescription()},
        {"dosage_instruction", product.getDosageInstruction()},
        {"price", product.getPrice()},
        {"quantity", product.getQuantity()},
        {"category", product.getCategory()},
        {"requires_prescription", product.requiresPrescription()}
    });

    // Save the updated JSON data to the file
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << std::setw(4) << productJson << std::endl;
        outputFile.close();
        std::cout << "Product information saved to " << filename << " successfully!" << std::endl;
    } else {
        std::cout << "Unable to open " << filename << " for writing." << std::endl;
    }
}

int main() {

    //Menu
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Add Product" << std::endl;
    std::cout << "2. Search Products By Name" << std::endl;
    std::cout << "3. Search Products By Brand" << std::endl;
    std::cout << "4. Search Products By Category" << std::endl;
    std::cout << "5. Exit" << std::endl;

    int choice;
    std::string name, brand, description, category;
    double price;
    int quantity;
    bool requires_prescription;
    Product product(generateRandomString(32), "", "", "", "", 0.0, 0, "", false);

    while (true) {
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the name of the product: ";
                std::cin.ignore(); // Ignore the newline character from the previous input
                std::getline(std::cin, name);
                product.setName(name);

                std::cout << "Enter the brand of the product: ";
                std::getline(std::cin, brand);
                product.setBrand(brand);

                std::cout << "Enter the product description: ";
                std::getline(std::cin, description);
                product.setDescription(description);

                std::cout << "Enter the price of the product: ";
                std::cin >> price;
                product.setPrice(price);

                std::cout << "Enter the quantity of the product: ";
                std::cin >> quantity;
                product.setQuantity(quantity);

                std::cout << "Enter the category of the product: ";
                std::cin.ignore(); // Ignore the newline character from the previous input
                std::getline(std::cin, category);
                product.setCategory(category);

                std::cout << "Does the product require a prescription? (0 for No, 1 for Yes): ";
                std::cin >> requires_prescription;
                product.setRequiresPrescription(requires_prescription);

                saveProductToJson(product);
                std::cout << "Product added successfully!" << std::endl;
                break;
            case 2:
                // Search Products By Name
                // Implement this functionality here...
                std::cout << "Search Products By Name - Coming Soon!" << std::endl;
                break;
            case 3:
                // Search Products By Brand
                // Implement this functionality here...
                std::cout << "Search Products By Brand - Coming Soon!" << std::endl;
                break;
            case 4:
                // Search Products By Category
                // Implement this functionality here...
                std::cout << "Search Products By Category - Coming Soon!" << std::endl;
                break;
            case 5:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please choose a valid option (1-5)." << std::endl;
        }
    }

    // Accessing attributes using getter methods
    std::cout << "Product Code: " << product.getCode() << std::endl;
    std::cout << "Name: " << product.getName() << std::endl;
    std::cout << "Brand: " << product.getBrand() << std::endl;
    std::cout << "Description: " << product.getDescription() << std::endl;
    std::cout << "Dosage Instruction: " << product.getDosageInstruction() << std::endl;
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << product.getPrice() << std::endl;
    std::cout << "Quantity: " << product.getQuantity() << std::endl;
    std::cout << "Category: " << product.getCategory() << std::endl;
    std::cout << "Requires Prescription: " << std::boolalpha << product.requiresPrescription() << std::endl;

    return 0;
}