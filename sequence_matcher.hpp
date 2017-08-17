#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class SequenceMatcher{
public:
    SequenceMatcher(std::vector<T> sequence, unsigned int sequence_id):
            sequence(sequence), sequence_id(sequence_id){
        m_start_it = this->sequence.end();
        m_now_it = this->sequence.end();
        m_previous_it = this->sequence.end();
    }

    /************************************************************
        -1:Not accepted item
        -2:Same item with previous
        -3:Start itme of one round sequence
        -4:Not start itme for a new round quence
        -5:Matched except item
        Positive ID: Sequence ID when matched total sequence
    ************************************************************/
    int pushItem(T item){
        m_now_it = std::find(sequence.begin(), sequence.end(), item);

        // No item matched
        if (m_now_it == sequence.end()){
            reset();
            return -1;
        }

        // Still the previous input item for multi item sequence, do nothing
        if (m_now_it == m_previous_it)
            return -2;
        
        // For one item static gesture, matched
        if (sequence.size() == 1){
            reset();
            return sequence_id;
        }

        // Check if is a new round match
        if (m_start_it != sequence.end())
            if(!match_sequence_expect())
                reset();

        if (m_start_it == sequence.end()){
            if (match_sequence_begin()){
                return -3;
                start_item = item;
            } else {
                return -4;
            }
        }

        if (matched_sequence_end())
            return sequence_id;
        else
            return -5;
    }

    T getStartItem(){
        return start_item;
    }

    virtual bool match_sequence_begin()=0;
    virtual bool match_sequence_expect()=0;
    virtual bool matched_sequence_end()=0;

    void reset(){
        m_start_it = sequence.end();
        m_previous_it = sequence.end();
    }

protected:
    const std::vector<T> sequence;
    const int sequence_id;

    // m : matched
    T start_item;

    typename std::vector<T>::const_iterator m_start_it;
    typename std::vector<T>::const_iterator m_previous_it;
    typename std::vector<T>::const_iterator m_now_it;
};

template<typename T>
class LoopSequenceMatcher: public SequenceMatcher<T>{
public:
    LoopSequenceMatcher(std::vector<T> sequence, unsigned int sequence_id):
        SequenceMatcher<T>::SequenceMatcher(sequence, sequence_id){}

    virtual bool match_sequence_begin() override final {
        this->m_start_it = this->m_now_it;
        this->m_previous_it = this->m_now_it;
        return true;
    }

    virtual bool match_sequence_expect() override final{
        auto expect_it = this->m_previous_it + 1;
        expect_it = (expect_it == this->sequence.end()) ? this->sequence.begin() : expect_it;
        // Not matched
        if (expect_it != this->m_now_it)
            return false;
        else
            return true;
    }

    virtual bool matched_sequence_end() override final {
       this->m_previous_it = this->m_now_it;
       if (this->m_now_it == this->m_start_it){
            ++(this->m_start_it);
            this->m_start_it = (this->m_start_it == this->sequence.end()) ? this->sequence.begin() : this->m_start_it;
            return true;
        } else {
            return false;
        }
    }

};

template<typename T>
class NormalSequenceMatcher: public SequenceMatcher<T>{
public:
    NormalSequenceMatcher(std::vector<T> sequence, unsigned int sequence_id):
         SequenceMatcher<T>::SequenceMatcher(sequence, sequence_id){}

    virtual bool match_sequence_begin() override final {
        if (this->m_now_it == this->sequence.begin()){
            this->m_start_it = this->m_now_it;
            this->m_previous_it = this->m_now_it;
            return true;
        } else {
            return false;
        }
    }

    virtual bool match_sequence_expect() override final {
        auto expect_it = this->m_previous_it + 1;
        if (expect_it != this->m_now_it){
            this->reset();
            return false;
        } else {
            return true;
        }
    }

    virtual bool matched_sequence_end() override final {
        this->m_previous_it = this->m_now_it;
        if ((this->m_now_it + 1) == this->sequence.end()){
            this->reset();
            return true;
        }
        else {
            return false;
        }
    }
};

