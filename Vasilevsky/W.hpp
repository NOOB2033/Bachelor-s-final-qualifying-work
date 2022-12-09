#ifndef BACHELOR_S_FINAL_QUALIFYING_WORK_W_HPP
#define BACHELOR_S_FINAL_QUALIFYING_WORK_W_HPP


#include "../dependencies/dependencies.hpp"


class IW {
public:

    virtual void set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table) = 0;
    virtual std::vector<std::vector<size_t>> get_W() = 0;

private:

    virtual void search_setOfDistinctiveness(std::vector<std::vector<size_t>>& result,
                                             std::vector<bool>& check,
                                             size_t state) = 0;

    virtual void compareTwoStates(std::vector<std::vector<size_t>>& result,
                                  std::vector<bool>& check,
                                  size_t first_state,
                                  size_t second_state,
                                  size_t depth) = 0;

    virtual std::vector<std::vector<size_t>> optimization_W(std::vector<std::vector<std::vector<size_t>>>& W) = 0;
};


namespace synchronous {

class W : public IW {
public:

    virtual void set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table) override;
    virtual std::vector<std::vector<size_t>> get_W() override;

private:

    virtual void search_setOfDistinctiveness(std::vector<std::vector<size_t>>& result,
                                             std::vector<bool>& check,
                                             size_t state) override;

    virtual void compareTwoStates(std::vector<std::vector<size_t>>& result,
                                  std::vector<bool>& check,
                                  size_t first_state,
                                  size_t second_state,
                                  size_t depth) override;

    virtual std::vector<std::vector<size_t>> optimization_W(std::vector<std::vector<std::vector<size_t>>>& W) override;

    std::vector<std::vector<std::pair<size_t, size_t>>> table;
};

}


namespace parallel {

class W : public IW {
public:

    virtual void set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table) override;
    virtual std::vector<std::vector<size_t>> get_W() override;

private:

    virtual void search_setOfDistinctiveness(std::vector<std::vector<size_t>>& result,
                                             std::vector<bool>& check,
                                             size_t state) override;

    virtual void compareTwoStates(std::vector<std::vector<size_t>>& result,
                                  std::vector<bool>& check,
                                  size_t first_state,
                                  size_t second_state,
                                  size_t depth) override;

    virtual std::vector<std::vector<size_t>> optimization_W(std::vector<std::vector<std::vector<size_t>>>& W) override;

    std::vector<std::vector<std::pair<size_t, size_t>>> table;
};

}


#endif //BACHELOR_S_FINAL_QUALIFYING_WORK_W_HPP
