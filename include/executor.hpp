#pragma once
#include "pipeline.hpp"

class Shell;

class Executor {
public:
    int execute(Shell& shell, const ParsedPipeline& pipeline) const;
};
