#include "sequence_matcher.hpp"


class ScrlSequenceRecognizer{
public:
    ScrlSequenceRecognizer();
    ~ScrlSequenceRecognizer();
    int pushItem(int item);
    void reset();

private:
    std::vector<SequenceMatcher<int>*> gestureSequenceList;
};

