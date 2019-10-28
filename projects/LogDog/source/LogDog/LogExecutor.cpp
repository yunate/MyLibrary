#include "LogExecutor.h"

DumpToFileExecutor::DumpToFileExecutor(const DogString & path):
    m_path(path)
{
}

bool DumpToFileExecutor::Executor(const DogString & logStr)
{
    return false;
}

bool UpLoadExecutor::Executor(const DogString & logStr)
{
    return false;
}
