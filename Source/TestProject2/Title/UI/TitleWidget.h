// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

/**
 * 
 */

struct OrderInfo
{
	class UImage* OrderImage = nullptr;
	FVector2D Position = {0.0f, 0.0f};
	bool bExistOrder = false;
};

UCLASS()
class TESTPROJECT2_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Test")
	void MoveWidget();

	UFUNCTION(BlueprintCallable, Category = "Test")
	void OrderComplete();

	UFUNCTION(BlueprintCallable, Category = "Test")
	void NewOrder();

	UFUNCTION(BlueprintCallable, Category = "Test")
	void AddInitialOrder();


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Test")
	class UImage* OrderImage;

private:
	FTimerHandle MoveTimerHandle; 
	FVector2D TargetOffset = FVector2D(50.0f, 0.0f);
	float MoveTimeElapsed = 10.0f;

	FVector2D CurPosition = FVector2D(0.0f, 0.0f);
	FVector2D CurScale = FVector2D(0.0f, 0.0f);


	FTimerHandle OpacityTimerHandle;
	float OpacityTimeElapsed = 10.0f;
	float OpacityOffset = 0.05f;


	void UpdateWidgetPosition();
	void UpdateWidgetOpacity();

	TArray<OrderInfo> Orders;
};
