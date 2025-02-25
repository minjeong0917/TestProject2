// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Test")
	void MoveWidget();

	UFUNCTION(BlueprintCallable, Category = "Test")
	void OrderComplete();
	

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Test")
	class UImage* OrderImage;

};
