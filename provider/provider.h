#ifndef PROVIDER_H
#define PROVIDER_H
#include <vector>
#include <string>
#include "../product/product1.h"


///Provider
///
///Class which represents a provider
class Provider{
public:
    ///
    /// \param n - name of provider
    /// \param p - vector of products available
    Provider(const std::string &n, std::vector<Product *> &p);

    ///
    /// \param n - name of provider
    /// \param size - number of products to create
    Provider(const std::string &n, unsigned &size);

    ///
    /// \return name of provider
    std::string getName() const;

    ///
    /// \return vector of products
    std::vector<Product *> getProducts() const;

    ///
    /// \return number of products
    unsigned getNumProducts() const;

    ///
    /// \param n - name of provider to set
    void setName(const std::string &n);

    ///
    /// \param p - vector of products to set
    void setProducts(const std::vector<Product *> &p);
private:
    /// name of provider
    std::string name;
    /// products available
    std::vector<Product *> products;
    /// number of products
    unsigned numProducts;
};

#endif
