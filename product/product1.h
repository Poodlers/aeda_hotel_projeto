#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
#include <iomanip>


/// Class which represents a product
///
/// Defined by quality, price, ID, type and stock
class Product {
public:
    /// Product Initializer
    ///
    /// Creates a random product with stock of 100
    Product();

    /// Product Initializer
    ///
    /// \param quality  quality of the product
    /// \param price  price of the product
    /// \param type  type of product
    Product(const unsigned int& quality, const float& price, const std::string & type);

    /// Returns the quality
    ///
    /// \return quality of the product
    unsigned int getQuality() const;

    /// Returns the price
    ///
    /// \return price of the product
    float getPrice() const;

    /// Returns the ID
    ///
    /// \return id of the product
    unsigned int getId() const;

    /// Returns the product type
    ///
    /// \return type of product
    std::string getType() const;

    /// Changes the quality type
    ///
    /// \param quality - quality to set to product
    void setQuality(const unsigned int& quality);

    /// Changes the price type
    ///
    /// \param price - price to set to product
    void setPrice(const float& price);

    /// Changes the type
    ///
    /// \param type - type to set to product
    void setType(const std::string & type);

    /// reduces the parameter stock of the product object by 1
    void reduceStock();

    /// Returns the stock of the product
    ///
    /// \return stock
    unsigned int getStock() const;

    /// Changes the stock of the product
    /// \param stock
    void setStock(const unsigned int& stock);

    ///Overloaded operator << to print the product's info in a formatted way
    friend std::ostream& operator <<(std::ostream& o, Product& product);

private:
    /// quality of the product
    unsigned int quality;
    /// price of the product
    float price;
    /// id of the product
    unsigned int Id;
    /// variable to keep product ids unique
    static int totalId;
    /// type of product
    /// can be catering, cleaning or other
    std::string type;
    ///amount of the product in the warehouse
    unsigned int stock;
};

#endif