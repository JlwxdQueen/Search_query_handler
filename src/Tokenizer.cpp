#include "../include/Tokenizer.h"

#include <algorithm>
#include <unordered_set>

void Tokenizer::removeSpecialCharacters(std::string& str) {
    const auto newEnd = std::ranges::remove_if(str, [](char c) {
        return c == '!' || c == '?' || c == '.' || c == ',';
    }).begin();

    str.erase(newEnd, str.end());
}

void Tokenizer::removeExtraSpaces(std::string& str) {

    str.erase(str.begin(), std::ranges::find_if(str, [](const unsigned char c) {
        return !std::isspace(c);
    }));

    str.erase(std::find_if(str.rbegin(), str.rend(), [](const unsigned char c) {
        return !std::isspace(c);
    }).base(), str.end());

    std::string result;
    bool wasSpace = false;

    for (const char c : str) {
        if (std::isspace(c)) {
            if (!wasSpace) {
                result += ' ';
                wasSpace = true;
            }
        } else {
            result += c;
            wasSpace = false;
        }
    }

    str = result;
}

std::vector<std::string> Tokenizer::tokenize(const std::string& str) {
    std::vector<std::string> words;
    std::string currentWord;

    for (const char c : str) {
        if (c == ' ') {
            words.push_back(currentWord);
            currentWord.clear();
        } else {
            currentWord += c;
        }
    }
    return words;
}

std::vector<std::string> Tokenizer::removeStopWords(const std::vector<std::string>& words) {
    const std::unordered_set stopWordsSet(stopWords.begin(), stopWords.end());
    std::vector<std::string> result;

    for (const auto& word : words) {
        if (!stopWordsSet.contains(word)) {
            result.push_back(word);
        }
    }

    return result;
}

std::string Tokenizer::tokenizedToString(const std::vector<std::string>& words) {
    std::string result;
    for (const auto& word : words) {
        result += word;
        result += " ";
    }
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}