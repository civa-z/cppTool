#include "sequence_matcher.hpp"

class StaticLable{
public:
    StaticLable():label(-1), number(-1){}
    StaticLable(int label, int number):label(label), number(number){}
    bool operator==(const StaticLable& other) const {
        return this->label == other.label;
    }
    /*
    StaticLable& operator=(const StaticLable& other){
        this->label = other.label;
        this->number = other.label;
        return *this;
    }
    */
private:
    int label;
    int number;
};

class ScrlSequenceRecognizer{
public:
    ScrlSequenceRecognizer();
    ~ScrlSequenceRecognizer();
    int pushItem(StaticLable);
    void reset();

private:
    std::vector<SequenceMatcher<StaticLable>*> gestureSequenceList;
};

