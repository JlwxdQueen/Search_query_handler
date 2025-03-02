#ifndef LOT_H
#define LOT_H

#include <string>

class Lot {
std::string title;
std::string desc;
bool isNewbie;
public:
    Lot(std::string  title, std::string  description, bool isNewbie);
    ~Lot();
    void set_title(const std::string &title);
    void set_desc(const std::string& desc);
    void set_isNewbie(bool isNewbie);
    std::string get_title();
    std::string get_desc();
    [[nodiscard]] bool get_isNewbie() const;
    [[nodiscard]] std::string to_string() const;
};

#endif