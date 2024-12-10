#ifndef CONTROLLER_STRATEGY_H
#define CONTROLLER_STRATEGY_H

#include <boost/program_options.hpp>

class controller;

class controller_strategy {
protected:
    controller *contr;

public:
    explicit controller_strategy(controller *contr): contr(contr) {
    }

    virtual void response_to_commit(int argc, boost::program_options::variables_map vm) = 0;

    virtual ~controller_strategy() = default;
};


// -------------------------------------------------------------------------------------------------
class strategy_context {
    std::vector<std::shared_ptr<controller_strategy> > controller_strategies;
    controller *contr;

public:
    explicit strategy_context(controller *contr);
    void run_strategy(int argc, const boost::program_options::variables_map& vm);
};


// -------------------------------------------------------------------------------------------------
class help_strategy : public controller_strategy {
public:
    explicit help_strategy(controller *contr) : controller_strategy(contr) {
    }

    void response_to_commit(int argc, boost::program_options::variables_map vm) override;
};


// -------------------------------------------------------------------------------------------------
class load_instances_strategy : public controller_strategy {
public:
    explicit load_instances_strategy(controller *contr) : controller_strategy(contr) {
    }

    void response_to_commit(int argc, boost::program_options::variables_map vm) override;
};


// -------------------------------------------------------------------------------------------------
class auto_load_instances_strategy : public controller_strategy {
public:
    explicit auto_load_instances_strategy(controller *contr) : controller_strategy(contr) {
    }

    void response_to_commit(int argc, boost::program_options::variables_map vm) override;
};


// -------------------------------------------------------------------------------------------------
class create_synthetic_instances_strategy : public controller_strategy {
public:
    explicit
    create_synthetic_instances_strategy(controller *contr) : controller_strategy(contr) {
    }

    void response_to_commit(int argc, boost::program_options::variables_map vm) override;
};


// -------------------------------------------------------------------------------------------------
class solve_strategy : public controller_strategy {
public:
    explicit solve_strategy(controller *contr) : controller_strategy(contr) {
    }

    void response_to_commit(int argc, boost::program_options::variables_map vm) override;
};


// -------------------------------------------------------------------------------------------------
class solve_parallel_strategy : public controller_strategy {
public:
    explicit solve_parallel_strategy(controller *contr) : controller_strategy(contr) {
    }

    void response_to_commit(int argc, boost::program_options::variables_map vm) override;
};


// -------------------------------------------------------------------------------------------------
class heuristic_strategy : public controller_strategy {
public:
    explicit heuristic_strategy(controller *contr) : controller_strategy(contr) {
    }

    void response_to_commit(int argc, boost::program_options::variables_map vm) override;
};

#endif
