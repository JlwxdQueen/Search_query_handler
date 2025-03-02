#include "../include/Lot.h"

#include <iostream>
#include <ostream>
#include <utility>

Lot::Lot(std::string title, std::string description, const bool isNewbie) :
    title(std::move(title)), desc(std::move(description)), isNewbie(isNewbie) {
}

Lot::~Lot() {
    std::cout << "lot " << title << " deleted" << std::endl;
    if (isNewbie) {
        std::cout << "created by newbie user" << std::endl;
    } else {
        std::cout << "created by old user" << std::endl;
    }
}

void Lot::set_title(const std::string &title) {
    this->title = title;
}

void Lot::set_desc(const std::string &desc) {
    this->desc = desc;
}

void Lot::set_isNewbie(const bool isNewbie) {
    this->isNewbie = isNewbie;
}

std::string Lot::get_title() {
    return title;
}

std::string Lot::get_desc() {
    return desc;
}

bool Lot::get_isNewbie() const {
    return isNewbie;
}

std::string Lot::to_string() const {
    std::string result;
    result += "title: " + title + "\n";
    result += " description: " + desc + "\n";
    return result;
}
