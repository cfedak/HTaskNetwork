#include "HTaskNetworkDomain.h"

bool FHTaskNetworkDomain::IsCompoundTask(FName TaskName) const { 
	return CompoundTasks.Contains(TaskName); 
}