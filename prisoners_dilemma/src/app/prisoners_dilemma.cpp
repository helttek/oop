#include "prisoners_dilemma.hpp"
#include "exceptions.hpp"
#include "matrix.hpp"
#include "strategy_factory.hpp"

#include <cstddef>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <system_error>

PrisonersDilemmaApp::PrisonersDilemmaApp(int argc, char **argv)
    : args(argv, argv + argc),
      strategies({"tough-tit-for-tat", "soft-tit-for-tat", "go-by-majority", "all-cooperate",
                  "all-defect", "random"}),
      availableModes({"detailed", "fast", "tournament"}), configsDirectory(),
      steps(-1), mode(""), matrixFile()
{
  try
  {
    ValidateArgs();
    LoadRules();
    LoadStrategies();
    PrepareGameMode();
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << "Failed to create game: " << e.what() << std::endl;
  }
}

void PrisonersDilemmaApp::Start()
{
}

void PrisonersDilemmaApp::LoadStrategies()
{
  StrategyFactory stratFactory();
}

void PrisonersDilemmaApp::PrepareGameMode()
{
  if (this->mode == "detailed")
  {
    return;
  }
  if (this->mode == "fast")
  {
    return;
  }
  if (this->mode == "tournament")
  {
    return;
  }
  throw std::runtime_error("failed to prepare game mode: unknown game mode");
}

void PrisonersDilemmaApp::ValidateArgs()
{
  for (int i = 1; i < this->args.size(); ++i)
  {
    if (!CheckIfOption(args[i]))
    {
      try
      {
        ValidateStrat(args[i]);
      }
      catch (const NotAStrat &e)
      {
        std::cout << "failed to validate strategy: " << e.what() << std::endl;
      }
    }
  }
  if (stratsToPlay.size() < 3)
  {
    throw std::runtime_error(
        "at least 3 strategies needed, only " +
        std::to_string(stratsToPlay.size()) + " provided.");
  }
  this->mode = (stratsToPlay.size() == 3) ? "detailed" : "tournament";
}

void PrisonersDilemmaApp::CheckIfMode(const std::string &m)
{
  std::string modeString("--mode=");
  size_t pos = m.find(modeString);
  if (pos == std::string::npos)
  {
    throw NotAnOption("[" + m + "] " + "not an option.");
  }
  if (pos)
  {
    throw NotAnOption(
        "[" + m + "] " +
        "not an option (maybe you meant \"--mode=<mode_name>\").");
  }
  if (pos >= m.size())
  {
    throw InvalidOption("invalid mode []");
  }
  std::string tmp = m.substr(modeString.size());
  if (!IsValidMode(tmp))
  {
    throw InvalidOption("invalid mode [" + m + "].");
  }
  this->mode = tmp;
}

int PrisonersDilemmaApp::IsValidMode(const std::string &m)
{
  for (auto availableMode : availableModes)
  {
    if (m == availableMode)
    {
      return 1;
    }
  }
  return 0;
}

void PrisonersDilemmaApp::CheckIfStepsOption(const std::string &so)
{
  std::string stepsString("--steps=");
  size_t pos = so.find(stepsString);
  if (pos == std::string::npos)
  {
    throw NotAnOption("[" + so + "] " + "not an option.");
  }
  if (pos)
  {
    throw NotAnOption(
        "[" + so + "] " +
        "not an option (maybe you meant \"--steps=<number_of_steps>\").");
  }
  if (stepsString.size() >= so.size())
  {
    throw InvalidOption("invalid number of steps []");
  }
  int tmp = IsValidStepsOption(so.substr(stepsString.size()));
  if (tmp <= 0)
  {
    throw InvalidOption("invalid number of steps [" + so + "].");
  }
  this->steps = tmp;
}

int PrisonersDilemmaApp::IsValidStepsOption(const std::string &so)
{
  try
  {
    int t = std::stoi(so);
    return t;
  }
  catch (const std::invalid_argument &e)
  {
    return -1;
  }
}

void PrisonersDilemmaApp::CheckIfConfigsOption(const std::string &co)
{
  std::string configsString("--configs=");
  size_t pos = co.find(configsString);
  if (pos == std::string::npos)
  {
    throw NotAnOption("[" + co + "] " + "not an option.");
  }
  if (pos)
  {
    throw NotAnOption("[" + co + "] " +
                      "not an option (maybe you meant "
                      "\"--configs=<path_to_configs_directory>\").");
  }
  if (configsString.size() >= co.size())
  {
    throw InvalidOption("invalid path to configs directory []");
  }
  try
  {
    std::filesystem::path tmp =
        IsValidConfigsOption(co.substr(configsString.size()));
    this->configsDirectory = tmp;
  }
  catch (const std::filesystem::filesystem_error &e)
  {
    throw InvalidOption(e.what());
  }
}

std::filesystem::path
PrisonersDilemmaApp::IsValidConfigsOption(const std::string &co)
{
  std::filesystem::path path(co);
  std::error_code ec;

  if (!std::filesystem::exists(path, ec))
  {
    if (ec)
    {
      throw std::filesystem::filesystem_error(
          "error while checking path (" + ec.message() + ").", ec);
    }
    else
    {
      throw std::filesystem::filesystem_error(
          "path [" + co + "] doesn't exist.", ec);
    }
  }
  if (!std::filesystem::is_directory(path, ec))
  {
    if (ec)
    {
      throw std::filesystem::filesystem_error(
          "error while checking if path is directory (" + ec.message() + ").",
          ec);
    }
    else
    {
      throw std::filesystem::filesystem_error(
          "path [" + co + "] exists, but not a directory.", ec);
    }
  }
  return std::filesystem::path(path);
}

void PrisonersDilemmaApp::CheckIfMatrixOption(const std::string &mo)
{
  std::string matrixString("--matrix=");
  size_t pos = mo.find(matrixString);
  if (pos == std::string::npos)
  {
    throw NotAnOption("[" + mo + "] " + "not an option.");
  }
  if (pos)
  {
    throw NotAnOption(
        "[" + mo + "] " +
        "not an option (maybe you meant \"--matrix=<filename>\").");
  }
  if (matrixString.size() >= mo.size())
  {
    throw InvalidOption("invalid matrix file []");
  }
  try
  {
    std::filesystem::path tmp =
        IsValidMatrixOption(mo.substr(matrixString.size()));
    this->matrixFile = tmp;
  }
  catch (const std::filesystem::filesystem_error &e)
  {
    throw InvalidOption(e.what());
  }
}

std::filesystem::path
PrisonersDilemmaApp::IsValidMatrixOption(const std::string &mo)
{
  std::filesystem::path path(mo);
  std::error_code ec;

  if (!std::filesystem::exists(path, ec))
  {
    if (ec)
    {
      throw std::filesystem::filesystem_error(
          "error while checking path (" + ec.message() + ").", ec);
    }
    else
    {
      throw std::filesystem::filesystem_error(
          "path [" + mo + "] doesn't exist.", ec);
    }
  }
  if (!std::filesystem::is_regular_file(path, ec))
  {
    if (ec)
    {
      throw std::filesystem::filesystem_error(
          "error while checking if path is regular file (" + ec.message() +
              ").",
          ec);
    }
    else
    {
      throw std::filesystem::filesystem_error(
          "path [" + mo + "] exists, but not a regular file.", ec);
    }
  }
  return std::filesystem::path(path);
}

int PrisonersDilemmaApp::CheckIfOption(const std::string &option)
{
  try
  {
    CheckIfMode(option);
    return 1;
  }
  catch (NotAnOption)
  {
  }
  catch (const InvalidOption &e)
  {
    std::cout << "failed to validate option: " << e.what() << std::endl;
    return -1;
  }

  try
  {
    CheckIfStepsOption(option);
    return 1;
  }
  catch (NotAnOption)
  {
  }
  catch (const InvalidOption &e)
  {
    std::cout << "failed to validate option: " << e.what() << std::endl;
    return -1;
  }

  try
  {
    CheckIfConfigsOption(option);
    return 1;
  }
  catch (NotAnOption)
  {
  }
  catch (const InvalidOption &e)
  {
    std::cout << "failed to validate option: " << e.what() << std::endl;
    return -1;
  }

  try
  {
    CheckIfMatrixOption(option);
    return 1;
  }
  catch (NotAnOption)
  {
  }
  catch (const InvalidOption &e)
  {
    std::cout << "failed to validate option: " << e.what() << std::endl;
    return -1;
  }

  return 0;
}

void PrisonersDilemmaApp::ValidateStrat(const std::string &strat)
{
  for (auto strategy : this->strategies)
  {
    if (strat == strategy)
    {
      this->stratsToPlay.insert(strat);
      return;
    }
  }
  throw NotAStrat("unknown strategy name \"" + strat + "\".");
}

void PrisonersDilemmaApp::LoadRules()
{
  try
  {
    this->matrix = (!this->matrixFile.empty()) ? Matrix::LoadRulesFromFile(this->matrixFile) : Matrix::LoadDefaultRules();
    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        std::cout << this->matrix[i * 3 + j] << " ";
      }
      std::cout << std::endl;
    }
  }
  catch (std::runtime_error e)
  {
    throw std::runtime_error(std::string("failed to load rules: ") + e.what());
  }
}
