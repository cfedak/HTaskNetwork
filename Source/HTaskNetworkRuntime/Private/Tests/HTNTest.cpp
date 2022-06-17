#include "Misc/AutomationTest.h"
#include "HTaskNetworkDomain.h"
#include "Operator.h"
#include "Condition.h"
#include "HTaskNetworkPlanner.h"

BEGIN_DEFINE_SPEC(FDomainTest, "HTNRuntime.DomainTests", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
END_DEFINE_SPEC(FDomainTest)
void FDomainTest::Define()
{
	BeforeEach([this]() {

	});

	Describe("Add Something", [this]() {
		It("should plan", [this]() {
			FHTaskNetworkDomain Domain;
			FPrimitiveTask& SprintToEnemy = Domain.PrimitiveTask(TEXT("SprintToEnemy"));
			UOperator* Op = NewObject<UOperator>();
			USetEffect* Set = NewObject<USetEffect>();
			Set->Init(TEXT("Location"), TEXT("Enemy"));
			Op->Effects.Push(Set);
			SprintToEnemy.Operator = Op;

			FPrimitiveTask& WalkToBridge = Domain.PrimitiveTask(TEXT("WalkToBridge"));
			UOperator* Op2 = NewObject<UOperator>();
			USetEffect* Set2 = NewObject<USetEffect>();
			Set2->Init(TEXT("Location"), TEXT("Bridge"));
			Op2->Effects.Push(Set);
			WalkToBridge.Operator = Op2;

			FPrimitiveTask& DoTrunkSlam = Domain.PrimitiveTask(TEXT("DoTrunkSlam"));
			DoTrunkSlam.Operator = NewObject<UOperator>();

			FPrimitiveTask& ChooseBridgeToCheck = Domain.PrimitiveTask(TEXT("ChooseBridgeToCheck"));
			ChooseBridgeToCheck.Operator = NewObject<UOperator>();

			FPrimitiveTask& CheckBridge = Domain.PrimitiveTask(TEXT("CheckBridge"));
			CheckBridge.Operator = NewObject<UOperator>();

			FCompoundTask& BeTrunkThumper = Domain.CompoundTask(TEXT("BeTrunkThumper"));
			FMethod WhenEnemyVisible;
			UEqualCondition* Eq1 = NewObject<UEqualCondition>();
			Eq1->Init(TEXT("CanSeeEnemy"), TEXT("True"));
			WhenEnemyVisible.Conditions.Add(Eq1);
			WhenEnemyVisible.Subtasks.Push(TEXT("SprintToEnemy"));
			WhenEnemyVisible.Subtasks.Push(TEXT("DoTrunkSlam"));
			BeTrunkThumper.Methods.Push(WhenEnemyVisible);

			FMethod WhenEnemyMissing;
			WhenEnemyMissing.Subtasks.Push(TEXT("ChooseBridgeToCheck"));
			WhenEnemyMissing.Subtasks.Push(TEXT("WalkToBridge"));
			WhenEnemyMissing.Subtasks.Push(TEXT("CheckBridge"));
			BeTrunkThumper.Methods.Push(WhenEnemyMissing);

			UHTaskNetworkPlanner* Planner = NewObject<UHTaskNetworkPlanner>();

			TArray<FName> Plan;
			FWorldState State;
			bool FoundPlan = Planner->CreatePlan(Domain, State, Plan);

			TestTrue("Found A Plan", FoundPlan);
		});
	});
}