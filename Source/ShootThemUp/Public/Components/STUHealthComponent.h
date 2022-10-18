// Shoot Them Up

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHeathChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

	float GetHeath() const { return Health;}

	UFUNCTION(BlueprintCallable)
    bool IsDead() const
    {
        return FMath::IsNearlyZero(Health);
    }

	FOnDeath OnDeath;
    FOnHeathChanged OnHeathChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHeath = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 5.0f;

private:


	float Health = 0.0f;

	FTimerHandle HealTimeHandle;

	UFUNCTION()
    void OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                               class AController *InstigatedBy, AActor *DamageCauser);

	void HealUpdate();

	void SetHealth(float NewHealth);
};
