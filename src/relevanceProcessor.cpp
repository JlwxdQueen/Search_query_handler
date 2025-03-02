#include "../include/relevanceProcessor.h"

#include <iterator>
#include <algorithm>
#include <complex>
#include <sstream>
#include <unordered_set>
#include <iostream>

void RelevanceProcessor::set_relevance(const std::string &info, float relevance) {
    const auto it = std::ranges::find_if(comparedInfo,
                                         [&info](const std::pair<std::string, float> &pair) {
                                             return pair.first == info;
                                         });
    if (it != comparedInfo.end()) {
        it->second = relevance;
    } else {
        comparedInfo.emplace_back(info, relevance);
    }
}

float RelevanceProcessor::get_relevance(const std::string &info) const {
    const auto it = std::ranges::find_if(comparedInfo,
                                         [&info](const std::pair<std::string, float> &pair) {
                                             return pair.first == info;
                                         });
    return (it != comparedInfo.end()) ? it->second : 0.0f;
}

void RelevanceProcessor::calculate_relevance(const std::vector<std::string> &comparedInfos) {
    const std::vector<float> seekedVector = stringToTFIDFVector(seekedInfo, comparedInfos);

    for (const auto &info: comparedInfos) {
        std::vector<float> comparedVector = stringToTFIDFVector(info, comparedInfos);

        const float relevance = cosineSimilarity(seekedVector, comparedVector);

        set_relevance(info, relevance);
    }
}

std::unordered_set<std::string> RelevanceProcessor::createVocabulary(const std::vector<std::string> &documents) {
    std::unordered_set<std::string> vocabulary;
    for (const auto &doc: documents) {
        std::istringstream iss(doc);
        std::string word;
        while (iss >> word) {
            vocabulary.insert(word);
        }
    }
    return vocabulary;
}


std::string RelevanceProcessor::normalizeTerm(const std::string &term) {
    std::string normalized = term;
    std::ranges::transform(normalized, normalized.begin(), ::tolower);
    std::erase_if(normalized, ::ispunct);
    return normalized;
}

float RelevanceProcessor::TF(const std::string &term, const std::string &document) {
    std::istringstream iss(document);
    std::vector words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
    const std::string normalizedTerm = normalizeTerm(term);
    const long long termCount = std::ranges::count_if(words, [&normalizedTerm](const std::string &word) {
        return normalizeTerm(word) == normalizedTerm;
    });
    return (!words.empty()) ? static_cast<float>(termCount) / static_cast<float>(words.size()) : 0.0f;
}

float RelevanceProcessor::IDF(const std::string &term, const std::vector<std::string> &documents) {
    int documentFrequency = 0;
    for (const auto &document: documents) {
        if (document.find(term) != std::string::npos) {
            documentFrequency++;
        }
    }
    const auto N = static_cast<float>(documents.size());
    if (documentFrequency == 0) {
        return 0.0f;
    }
    return std::log(N / static_cast<float>(documentFrequency));
}

float RelevanceProcessor::TF_IDF(const std::string &term, const std::string &document,
                                 const std::vector<std::string> &documents) {
    const float tf = TF(term, document);
    const float idf = IDF(term, documents);
    return tf * idf;
}

std::vector<float> RelevanceProcessor::stringToTFIDFVector(const std::string &document,
                                                           const std::vector<std::string> &documents) {
    std::unordered_set<std::string> vocabulary = createVocabulary(documents);
    std::vector terms(vocabulary.begin(), vocabulary.end());
    std::vector tfidfVector(terms.size(), 0.0f);

    std::istringstream iss(document);
    std::string word;
    while (iss >> word) {
        if (auto it = std::ranges::find(terms, word); it != terms.end()) {
            const size_t index = std::distance(terms.begin(), it);
            tfidfVector[index] = TF_IDF(word, document, documents);
        }
    }
    return tfidfVector;
}


float RelevanceProcessor::cosineSimilarity(const std::vector<float> &vector1, const std::vector<float> &vector2) {
    float dotProduct = 0.0f;
    for (size_t i = 0; i < vector1.size(); ++i) {
        dotProduct += vector1[i] * vector2[i];
    }

    float norm1 = 0.0f;
    for (const float value: vector1) {
        norm1 += value * value;
    }
    norm1 = std::sqrt(norm1);

    float norm2 = 0.0f;
    for (const float value: vector2) {
        norm2 += value * value;
    }
    norm2 = std::sqrt(norm2);

    if (norm1 == 0 || norm2 == 0) {
        std::cerr << "Warning: One of the vectors has zero norm." << std::endl;
        return 0.0f;
    }

    return dotProduct / (norm1 * norm2);
}
