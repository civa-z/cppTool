#include "ScrlSequenceRecognizer.hpp"

const std::vector< std::pair< std::vector<int>, std::pair<bool, int> >> gestureSequenceTab =
{
  //{ {sequence  }, {loop , ID} },
    { {11, 12    }, {true , 13} },
    { {11, 21    }, {true , 14} },
    { {12, 21    }, {true , 14} },
    { {31, 32    }, {true , 15} },
    { {41, 42, 43}, {true , 21} },
    { {41, 43, 42}, {true , 22} },
    { {11, 51    }, {false, 23} },
    { {12, 51    }, {false, 23} },
    { {21, 51    }, {false, 23} },
    { {61, 62    }, {false, 25} },
    { {71, 72    }, {false, 28} },
    { {72, 71    }, {false, 29} }
};

ScrlSequenceRecognizer::ScrlSequenceRecognizer(){
    for (auto item : gestureSequenceTab ){
        std::vector<StaticLable> staticGestureSequence;
        for (auto staticGestureItem : item.first){
            staticGestureSequence.push_back(StaticLable(staticGestureItem, 0));
        }
        if (item.second.first)
            gestureSequenceList.push_back(new LoopSequenceMatcher<StaticLable>(staticGestureSequence, item.second.second));
        else
            gestureSequenceList.push_back(new NormalSequenceMatcher<StaticLable>(staticGestureSequence, item.second.second));
    }
}

ScrlSequenceRecognizer::~ScrlSequenceRecognizer(){}

int ScrlSequenceRecognizer::pushItem(StaticLable item){
    int result = -1;
    for (auto gestureSequence : gestureSequenceList){
        auto gestureID = gestureSequence->pushItem(item);
        if (gestureID >= 0)
            result = gestureID;
    }
    
    return result;
}

