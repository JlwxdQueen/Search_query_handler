#ifndef RELEVANCEPROCESSOR_H
#define RELEVANCEPROCESSOR_H

#include <string>
#include <utility>
#include <vector>
#include <unordered_set>

class RelevanceProcessor {
    std::string seekedInfo;
    std::vector<std::pair<std::string, float>> comparedInfo;

public:
    explicit RelevanceProcessor(std::string seekedInfo) : seekedInfo(std::move(seekedInfo)) {}
    ~RelevanceProcessor() = default;

    void set_relevance(const std::string& info, float relevance);
    [[nodiscard]] float get_relevance(const std::string& info) const;

    void calculate_relevance(const std::vector<std::string>& comparedInfos);

private:
    static std::unordered_set<std::string> createVocabulary(const std::vector<std::string>& documents);

    static std::string normalizeTerm(const std::string& term);

    static float TF(const std::string& term, const std::string& document);

    static float IDF(const std::string& term, const std::vector<std::string>& documents);

    static float TF_IDF(const std::string& term, const std::string& document, const std::vector<std::string>& documents);
    static std::vector<float> stringToTFIDFVector(const std::string& document, const std::vector<std::string>& documents);

    static float cosineSimilarity(const std::vector<float>& vector1, const std::vector<float>& vector2);
};

#endif