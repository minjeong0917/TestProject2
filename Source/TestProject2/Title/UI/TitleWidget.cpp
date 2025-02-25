// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject2.h"
#include "Title/UI/TitleWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"


void UTitleWidget::MoveWidget()
{
    if (OrderImage)
    {
        FVector2D CurrentPosition = OrderImage->RenderTransform.Translation;
        FVector2D Offset = FVector2D(10.0f, 0.0f); 
        OrderImage->SetRenderTranslation(CurrentPosition + Offset);
    }
}


void UTitleWidget::OrderComplete()
{
    if (OrderImage)
    {
        FVector2D CurrentPosition = OrderImage->RenderTransform.Translation;
        FVector2D Offset = FVector2D(10.0f, 0.0f);
        OrderImage->SetRenderTranslation(CurrentPosition + Offset);
    }
}


