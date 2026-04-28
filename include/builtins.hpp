#pragma once
#include <string>
#include <vector>

/// Each returns exit status for the shell (0 = ok).
int builtin_cd(const std::vector<std::string>& args);
int builtin_pwd(const std::vector<std::string>& args);
int builtin_echo(const std::vector<std::string>& args);
int builtin_ls(const std::vector<std::string>& args);
int builtin_help(const std::vector<std::string>& args);
