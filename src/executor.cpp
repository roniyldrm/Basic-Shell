#include "executor.hpp"
#include "shell.hpp"
#include <iostream>

int Executor::execute(Shell& shell, const ParsedPipeline& pipeline) const {
    if (pipeline.stages.empty())
        return 0;

    if (pipeline.stages.size() > 1) {
        std::cerr << "myshell: pipelines (`|`) are not implemented yet\n";
        shell.last_status_ = 1;
        return shell.last_status_;
    }

    shell.runBuiltinOrExternal(pipeline.stages.front());
    return shell.last_status_;
}
