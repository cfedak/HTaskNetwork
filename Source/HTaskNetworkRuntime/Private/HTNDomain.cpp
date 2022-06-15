#include "HTNDomain.h"

bool FHTNDomain::IsCompoundTask(FName TaskName) const { 
	return CompoundTasks.Contains(TaskName); 
}